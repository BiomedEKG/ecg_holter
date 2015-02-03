#include "Hrv2.h"
#include <iostream>
#include <string>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;



//konstruktor
    Hrv2::Hrv2(){
       
		//jednostki zwracanych parametrów
		paramsUnits[0]="-"; //apen
		paramsUnits[1]="-"; //samen
		paramsUnits[2]="ms"; //tinn
		paramsUnits[3]="-"; //triRR
		paramsUnits[4]="ms"; //sd1
		paramsUnits[5]="ms"; //sd2
		//jednostki histogramu
		histUnits[0]="ms"; //oœ x
		histUnits[1]="-"; //oœ y
		//jednostki wykresy Poincare
		poincareUnits[0]="ms"; //oœ x
		poincareUnits[1]="ms"; //oœ y
    }

	void Hrv2::setValues(vector<double> x, unsigned int y){
		r_peaks = x;
        freq= y;
        N = r_peaks.size() -1;
	}



//tworzenie interwa³ów RR z pików R
    vector<double> Hrv2::create_RR_intervals(){
		
        vector<double> RR;   
        double t=(1/(double)freq)*1000;
        for(int i=0; i<N; i++){
           RR.push_back((fabs(r_peaks[i+1]-r_peaks[i])*t));
        }
        return RR;
    }



//odchylenie standardowe
    double Hrv2::stDeviation2 (vector<double> z){
        double mean_result=0;
        double sd=0;
        double std2=0;

        for(int i=0; i<z.size(); i++){
            mean_result+=z[i];
            }
        mean_result=mean_result/(z.size()-1);
        for(int i=0; i< z.size(); i++){
            sd+=pow((z[i]-mean_result),2);
            }
        std2 = sqrt(sd/(z.size()-1));
        return std2;

    }


// suma wszystkich elementów wektora
    double Hrv2::sum(vector<double> elem){
        double suma =0;
        for( int i=0; i<elem.size(); i++) suma+= elem[i];
        return suma;
    }


// obliczanie entropii aproksymacji
    double Hrv2::calculateApen(vector<double> val, double s, int dim){
        
        double Cm[2]= {0,0};
        double r = 0.2 * s;
        int m=2;
        int sum, n_r;
        double* pm = new double[m]; // wektor pm o dlugosci m
        double cm_r;

        //obliczanie cm i cm+1
        for(int i=0;i<2;i++){
            m=dim+i; //wyznaczenie d³ugosci wzorca
            cm_r=0;
            for(int j=0; j<(N-m+1); j++){
                n_r=0;
                //tworzenie worca pm(i) o d³ugosci m
                for(int k=0;k<m;k++){
                    pm[k]=val[j+k];
                }
                //spr podobienstw
                for(int kk=0; kk<(N-m+1);kk++){
                    sum=0;
                    for(int k=0;k<m;k++){
                        if((fabs(pm[k]-val[kk+k])) <= r)    sum++;
                        else break;
                     }   
                     if(sum==m)    n_r++;
                }
            cm_r += (double)n_r/(double)(N-m+1);   
            }
            Cm[i]=cm_r/(N-m+1);
       
        }
		if(Cm[0]==0 || Cm[1]==0){
			return fabs(log((N-dim)/(N-dim-1))); //wyznaczanie entropii
			}
		else{
			return fabs(log(Cm[0]/Cm[1])); //wyznaczanie entropii
			}
    }




//obliczanie entropii próby
    double Hrv2::calculateSamen(vector<double> val, double s, int dim){
        
        double Cm_s[2]= {0,0};
        int m=2;
        int sum, n_r;
        double r= 0.2 * s;
        double* pm = new double[m]; // wektor pm o dlugosci m
        double cm_r;

        //obliczanie cm i cm+1
        for(int i=0;i<2;i++){
            m=dim+i; //wyznaczenie d³ugosci wzorca
            cm_r=0;
            for(int j=0; j<(N-m); j++){
                n_r=0;
                //tworzenie worca pm(i) o d³ugosci m
                for(int k=0;k<m;k++){
                    pm[k]=val[j+k];
                }
                //sprawdzanie podobienstw
                for(int kk=0; kk<(N-m);kk++){
                    if (kk == j) continue;
                    else{
                        sum=0;
                        for(int k=0;k<m;k++){
                            if((fabs(pm[k]-val[kk+k])) <= r)    sum++;
                            else break;
                         }   
                         if(sum==m)    n_r++;   
                    }
               
                }
            cm_r += (double)n_r/(double)(N-m);   
            }
            Cm_s[i]=cm_r/(N-m);
       
        }
		if(Cm_s[0]==0 || Cm_s[1]==0){
			return fabs(log((N-dim)/(N-dim-1))); //wyznaczanie entropii
		}
		else{
			return fabs(log(Cm_s[0]/Cm_s[1])); //wyznaczanie entropii
		}
        
    

    }



 //poincare- wektory
    map<string, vector<double>> Hrv2::poincareVectors (vector<double> val){

		vector<double> usun, tabplus, tabminus ;
		double a=300, b=2000;
		/*
        for( int i = 0; i < val.size(); i++ ){
            if (val[i]<a || val[i]>b){
                if((i>0) && !(usun.back() == (i-1)))    usun.push_back(i-1);
				usun.push_back(i);
				}
			}
			*/
		//tworzenie wektora plus
		for( int i = 0; i < val.size() - 1; i++ ){
            tabplus.push_back( val[i] );
			}
        //tworzenie wektora minus
        for( int i = 1; i < val.size(); i++ ){
            tabminus.push_back( val[i] );
			}

        int s=usun.size();
		for (int i=s-1; i>=0; i--){
            tabplus.erase(tabplus.begin() + usun[i]);
			}
		x1_x2["x1"]=tabplus;

		for (int i=s-1; i>=0; i--){
             tabminus.erase(tabminus.begin() + usun[i]);
			}
        x1_x2["x2"]=tabminus;

        return x1_x2;
    }

//wyznaczanie parametrów sd1, sd2
	 map<string, double> Hrv2::poincareParams(map<string,vector<double>> x1_x2){
        
		//obliczanie variancji
        vector <double> x1, x2;
        vector <double> tabplus, tabminus;
        map<string, double> poinParams;

        tabplus = x1_x2["x1"];
        tabminus = x1_x2["x2"];

         for( int i = 0; i <tabplus.size(); i++ ){
            x1.push_back ((tabplus[ i ] - tabminus[ i ])/sqrt(2));
			}

         for( int i = 0; i <tabplus.size(); i++ ){
            x2.push_back ((tabplus[ i ] + tabminus[ i ])/sqrt(2));
			}

        double SD2=stDeviation2(x2);
        double SD1=stDeviation2(x1);
        poinParams["sd1"] = SD1;
        poinParams["sd2"] = SD2;

        return poinParams;
    }



// generowanie histogramu
    map<string, vector<double>> Hrv2::createHist(vector<double> val, double s){
       
        double minimum = val[0];
		double maksimum = val[0];

        for(int i=1;i<val.size();i++)  
			if(minimum>val[i])	minimum = val[i];
		for(int i=1;i<val.size();i++)    
			if(maksimum<val[i])  maksimum = val[i];

        double roz=maksimum - minimum;
		double siz= val.size();
		double pot= -0.2;
		double power= pow(siz, pot);
		double C=ceil((1.06*s* pow(siz, pot)-0.5));
        double m= ceil((roz/C)-0.5);
        double cp=minimum;
        double ck=cp+C;

        vector<double> hist;
		double k;

         for( int i = 0; i < m; i++ ){
            k=0;

            for( int j = 0; j < val.size(); j++ ){
				if((val[j]>=cp) && (val[j]<ck))	k=k+1;
				}

            hist.push_back(k);
            cp=cp+C;
            ck=ck+C;
			}

        histValues["values"]=hist;
		vector <double>czas_p;
		k=minimum;

        for( int i=0; i < hist.size(); i++ ){    
			czas_p.push_back(k);
			k=k+C;
			}

        histValues["start_time"]=czas_p;
        vector <double>czas_k;

        for( int i=0; i < hist.size(); i++ ){
			k=czas_p[i]+C;
			czas_k.push_back(k);
			}

        histValues["end_time"]=czas_k;
		return histValues;
    }



 //index trójk¹tny
    double Hrv2::triangleRR(map<string,vector<double>> histValues, int a, int b){
        
        double triRR;
        vector <double> hist= histValues["values"];
        double suma=0;
        for( int i=a; i < b; i++ ){
			suma=suma+ hist[i];
			}

        double maksimumhist = hist[0];

        for(int i=a;i<b;i++){
            if(maksimumhist<hist[i])
            maksimumhist = hist[i];
			}

        return triRR=suma/maksimumhist;
        }



 //TINN
    double Hrv2:: tinn(map<string,vector<double>> histValues, int a, int b){
		
		vector<double>::iterator nrprobka;
		vector <double> hist = histValues["values"];
		vector <double> czas = histValues["start_time"];

		nrprobka = (max_element(hist.begin(), hist.end()));
		auto probka= distance(hist.begin(), nrprobka);
		vector <double> lewewartosci;
		vector <double> leweczas;
		vector <double> prawewartosci;
		vector <double> praweczas;
		double TINN;

		for(int i=a;i<=probka;i++) {
			lewewartosci.push_back(hist[i]);
			leweczas.push_back(czas[i]);
			}

		for(int i = probka;i < b;i++) {
			prawewartosci.push_back(hist[i]);
			praweczas.push_back(czas[i]);
			}

		double b1_lewe, b2_lewe, b1_prawe, b2_prawe;
		double n=lewewartosci.size();
		double n1=prawewartosci.size();
		vector <double> lewe_xiy;
		
		for(int i=0; i<n; i++){
			lewe_xiy.push_back((lewewartosci[i] * leweczas[i]));
			}

		vector <double> lewe_xix;

		for(int i=0; i<n; i++){
			lewe_xix.push_back((leweczas[i] * leweczas[i]));
			}

		double sum_x_lewe, sum_y_lewe, sum_xy_lewe, sum_x2_lewe;

		sum_x_lewe=sum(leweczas);
		sum_y_lewe=sum(lewewartosci);
		sum_xy_lewe=sum(lewe_xiy);
		sum_x2_lewe=sum(lewe_xix);

		b1_lewe=(n*sum_xy_lewe - sum_x_lewe*sum_y_lewe)/(n*sum_x2_lewe-pow(sum_x_lewe, 2));
		b2_lewe=(sum_y_lewe-b1_lewe*sum_x_lewe)/n;

		vector <double> prawe_xiy;

		for(int i=0; i<n1; i++){
			prawe_xiy.push_back((prawewartosci[i] * praweczas[i]));
			}

		vector <double> prawe_xix;
		
		for(int i=0; i<n1; i++){
			prawe_xix.push_back((praweczas[i] * praweczas[i]));
			}

		double sum_x_prawe, sum_y_prawe, sum_xy_prawe, sum_x2_prawe;

		sum_x_prawe=sum(praweczas);
		sum_y_prawe=sum(prawewartosci);
		sum_xy_prawe=sum(prawe_xiy);
		sum_x2_prawe=sum(prawe_xix);

		b1_prawe=(n1*sum_xy_prawe - sum_x_prawe*sum_y_prawe)/(n1*sum_x2_prawe-pow(sum_x_prawe, 2));
		b2_prawe=(sum_y_prawe-b1_prawe*sum_x_prawe)/n1;

		double x0_lewe, x0_prawe;

		x0_lewe=(-b2_lewe/b1_lewe);
		x0_prawe=(-b2_prawe/b1_prawe);

		TINN=x0_prawe - x0_lewe;

		return TINN;
    }



// funkcja zwracaj¹ca parametry geometryczne sd1, sd2, tinn, inteks trójk¹tny, entropie aproksymacji i próby
	Hrv2Result* Hrv2 :: compute(ResultKeeper* rkp) const{

		r_peaks = *rkp->rpeaks;// vector r pików
        freq= *rkp->freq; // czestotliwosc próbkowania
        N = r_peaks.size() -1; 
		vector<double> RR;
		double std, sd1,sd2;
		RR=create_RR_intervals();
		std=stDeviation2(RR);
		this->histValues=createHist(RR,std);
		vector <double> h=histValues["values"];
		int start, koniec;
		start = 0; //wartoœæ domyœlna pocz¹tkowego punktu histogramu potrzebny do wyznaczenia parameterów tinn i trianRR
		koniec = h.size(); //wartoœæ domyœlna koñcowego punktu histogramu potrzebny do wyznaczenia parameterów tinn i trianRR
		this->x1_x2=poincareVectors(RR);
		double apen, samen, triRR, tinnP;
		map<string,double> sd1_sd2;
		map<string,double> hrv2p;
		apen=calculateApen(RR,std);
		samen=calculateSamen(RR,std);
		tinnP= tinn(histValues, start, koniec);
		triRR= triangleRR(histValues,start,koniec);
		sd1_sd2 = poincareParams(x1_x2);
		sd1=sd1_sd2["sd1"];
		sd2=sd1_sd2["sd2"];
		
		hrv2p["apen"]=apen;
		hrv2p["samen"]=samen;
		hrv2p["tinn"]=tinnP;
		hrv2p["tri"]=triRR;
		hrv2p["sd1"]=sd1;
		hrv2p["sd2"]=sd2;

		Hrv2Result res = Hrv2Result();
		res.setHrv2Result(hrv2p, histValues, x1_x2);
		return res.getResult();

	}

	


// zmiana wartoœci parametrów Tinn i triangle RR po zadaniu wartoœci granicznych

	/*nie wiem co tutaj ... u¿ytkownik po wyœwietleniu histogramu, czyli jak ju¿ 
	sie pokaz¹ wykresy i parametry ma opcje zmiany granicznych punktór histogramu, wg których 
	obliczy sie tinn i triangle index (na pocz¹tku oblicza siê dla domœlnych wartoœci)*/

	map<string,double> Hrv2::updateHistParams(double f, double l, vector<double> x, unsigned int y){

		int a,b;
		double c;
		map<string, double> updatedValues;
		setValues(x,y);
		if(histValues.empty()){
			vector<double> RR;
			double std;
			RR=create_RR_intervals();
			std=stDeviation2(RR);
			this->histValues=createHist(RR,std);

		}
		
		vector<double> v, t;
		v=histValues["values"];
		t=histValues["start_time"];
		sort(v.begin(), v.end());
		double max_v=t[0];
		int s_v=v.size();
		for (int i = 0; i < s_v; ++i){
			if(histValues["values"][i]==v[s_v-1]) max_v=t[i];
			}

		if(f>t[0] && f<max_v &&  l<t[s_v-1] && l>max_v){
			c=ceil(histValues["end_time"][0]-histValues["start_time"][0]-0.5);
			a=(int)(f-histValues["start_time"][0])/(int)c;
			b=(int)(l-histValues["start_time"][0])/(int)c;
			}
		else{
			a=0;
			b=s_v;
			}


		updatedValues["tinn"]= tinn(histValues, a, b);
		updatedValues["tri"]= triangleRR(histValues,a,b);

		return updatedValues;
	}

