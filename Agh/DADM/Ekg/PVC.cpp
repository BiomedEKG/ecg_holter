#include <vector>
#include <iostream>
#include "PVC.h"

#define PVCclass 1
#define RR_max 2000
#define RR_min 300



void PVC::show(){
	std::vector<double>::iterator it, it1, it2, it3;
	it = this->qqq.indeks.PVCindex.begin();
	

	for(int i=0; i<this->qqq.indeks.PVCindex.size(); i++){
		std::cout << "PVC: "; std::cout << *(it+i) << std::endl;
	}



	for(int i=0; i<this->qqq.signal.size(); i++){
		std::cout << "QRS indexes around PVC: "; std::cout<<std::endl;
		for(int j=0; j<this->qqq.signal[i].size(); j++){
			 
			 std::cout << this->qqq.signal[i][j] << std::endl;
		}
		std::cout << "QRSclasses: "; std::cout<<std::endl;
		for(int j=0; j<this->qqq.signal[i].size(); j++){
			 
			 std::cout << this->qqq.QRSclass[i][j] << std::endl;
		}
	}

	for(int i=0; i<this->qqq.tachogram.size(); i++){
		std::cout << "tachograms: "; std::cout<<std::endl;
		for(int j=0; j<this->qqq.tachogram[i].size(); j++){
			 std::cout << this->qqq.tachogram[i][j] << std::endl;
		}
	}

	
	
}

void PVC::findPVC(std::vector<double> R_peaks, std::vector<double> R_class){
	//zwraca numery próbek w których wyst¹pi³y za³amki R w sygnale EKG oraz indeksy tych próbek w wektorze wejœciowym

	size_t length = R_peaks.size();
	double i = 0;
	std::vector<double>::iterator it;
	std::vector<double>::iterator R_it = R_class.begin();

	for(it=R_peaks.begin(); it!=R_peaks.end(); it++, R_it++, i++){
		if(*R_it == PVCclass){
			
			this->qqq.indeks.PVCindex.push_back(*it);
			this->qqq.indeks.sampleIndex.push_back(i);
		}
	}

}


void PVC::isolatePVC(std::vector<double> sampnumb, std::vector<double> R_peaks, std::vector<double> R_class, double fs){

	
	
	std::vector<double> row, row1, row2;
	
	
	double i=0;
	std::vector<double>::iterator it;
	std::vector<double>::iterator R_it;
	std::vector<double>::iterator C_it;
	std::vector<double>::iterator T_it;

	for(it=sampnumb.begin(); it!=sampnumb.end(); it++, i++){
		R_it=R_peaks.begin()+(*it);
		C_it=R_class.begin()+(*it);
		std::vector<double> row, row1, row2;
		std::vector<double>::iterator it1=row.begin();
		std::vector<double>::iterator it2=row1.begin();
		row.insert(it1, R_it-(this->before), R_it+(this->after));
		row1.insert(it2, C_it-(this->before), C_it+(this->after));
		for(T_it=row.begin()+1; T_it!=row.end(); T_it++){
			row2.push_back(((*T_it) - (*(T_it-1)))/fs);
		}

		this->qqq.signal.push_back(row);
		this->qqq.QRSclass.push_back(row1);
		this->qqq.tachogram.push_back(row2);
	}

	for(i=0; i<this->qqq.tachogram[0].size(); i++)
			this->www.meanTachogram.push_back(this->qqq.tachogram[0][i]);

}
	


void PVC::ArtefactsRemover(std::vector<std::vector<double>> QRSc, std::vector<std::vector<double>> tach){


	std::vector<double>::iterator qrs_it;
	std::vector<double>::iterator tach_it;
	std::vector<double>::iterator prze_it;
	std::vector<double>::iterator mean_ite;
	std::vector<double> SUMvek;    //pusty wektor -> bêdzie przechowywa³ info o tym, ile wynosi suma klas pobudzeñ w danym wektorze - jeœli jest wiêcje ni¿ 1, to wektor siê nie nadaje do u¿ytku
	std::vector<double>::iterator sum_it = SUMvek.begin();
	
	int i = 0;
	double sum=0.0;
	// sprawdzenie czy sš tylko nadkomorowe pod warunkiem oznaczeñ 0,1,2
	for(int j=0; j<QRSc.size(); j++){
		for (qrs_it = QRSc[j].begin(); qrs_it != QRSc[j].end(); qrs_it++){
			 sum += *qrs_it;
		}
		SUMvek.push_back(sum);
		sum=0.0;
	}
	i=0;
	std::vector<bool> inRRrange;
	// sprawdzenie 300ms < RR < 2000ms 
		for(i=0; i < tach.size(); i++){
			inRRrange.push_back(true);
			std::cout<<tach.size()<<std::endl;
			for(tach_it=tach[i].begin()+((this->before)+1); tach_it<tach[i].end(); tach_it++){
				std::cout<<*(tach_it)<<std::endl;

				  if(*tach_it < RR_min || *tach_it > RR_max){
					  inRRrange[i] = false;
					  break;
				  }
			}
		}
		i=0;
		
		std::vector<double> RR_mean;
		sum=0.0;

	for(i=0; i<tach.size(); i++){
		for(mean_ite = tach[i].begin(); mean_ite != tach[i].begin()+((this->before)-1); mean_ite++){
			sum += *mean_ite;
		}
		RR_mean.push_back(sum/((this->before)-1));
		sum=0.0;
	}

	std::vector<bool> inMeanRange;
	i=0;
	double val;

	for(i = 0; i < tach.size(); i++){
		inMeanRange.push_back(true);
		for(tach_it = tach[i].begin()+((this->before)+2); tach_it < tach[i].end(); tach_it++){
			val = *tach_it - RR_mean[i];
			if(val<0)
				val=val*(-1);
			if(val < 0.2*RR_mean[i] || val > 1.2*RR_mean[i]){
				  inMeanRange[i] = false;
				  break;
			}
		}
	}

	int z=0, x=0;
	//przekazujemy wszystkie tachogramy które spe³niaj¹ powy¿szy warunek do 
	for(i=0; i<tach.size(); i++){
		for(tach_it = tach[i].begin(); tach_it != tach[i].end(); tach_it++, i++){
			if(SUMvek[i]>1 || inRRrange[i]==false || inMeanRange[i]==false){
				std::cout<< "rejected!!!";
				this->www.rejected.push_back(std::vector<double>());
				this->www.rejected[i].insert(this->www.rejected[i].begin(), tach_it, tach[i].end()-1);
			}
			else{
				this->www.accepted.push_back(std::vector<double>());
				this->www.accepted.insert(this->www.accepted.begin(),tach_it, tach[i].end()-1);
			}
		}
	}

	i=0;
	std::vector<double> meanTach;

	for(i=0; i<this->www.accepted.size(); i++){
		this->www.meanTachogram.push_back(0);
		for(int j=0; j<www.accepted[i].size(); j++){
			this->www.meanTachogram[j] = this->www.meanTachogram[j] + this->www.accepted[i][j];
		}
	}
	std::vector<double>::iterator it = this->www.meanTachogram.begin();
	for(it=it; it!=this->www.meanTachogram.end(); it++){
		*it=*it/this->www.accepted.size();
	}
}