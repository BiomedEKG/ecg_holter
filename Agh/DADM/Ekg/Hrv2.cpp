#include "Hrv2.h"
#include <iostream>
#include <string>
#include <cmath>
#include <string>
#include <algorithm>
#include "ResultKeeper.h"
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



//œrednia arytmetyczna
double Hrv2::mean2(vector<double> z){
	double mean_result=0;

		for(int i=0; i<z.size(); i++){
            mean_result+=z[i];
            }
        mean_result=mean_result/(z.size()-1);

		return mean_result;
}

//odchylenie standardowe
    double Hrv2::stDeviation2 (vector<double> z){
      
        double sd=0;
        double std2=0;
		double mean_result = mean2(z);
        
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


// wspolczynniki prostej obliczone metod¹ najmniejszych kwadratów
	map<string,double> Hrv2:: getCoff(vector<double> war, vector<double> c){
		vector <double> xiy;
		vector <double> xix;
		double n,sum_x, sum_y, sum_xy, sum_x2, varb1, varb2;
		map<string, double> coff;
		n=c.size();
			
			for(int i=0; i<n; i++){
				xiy.push_back((war[i] * c[i]));
				}

			for(int i=0; i<n; i++){
				xix.push_back((c[i] * c[i]));
				}

			sum_x=sum(c);
			sum_y=sum(war);
			sum_xy=sum(xiy);
			sum_x2=sum(xix);

			varb1=(n*sum_xy- sum_x*sum_y)/(n*sum_x2-pow(sum_x, 2));
			varb2=(sum_y-varb1*sum_x)/n;
			coff["b1"]=varb1;
			coff["b2"]=varb2;
			xiy.clear();
			xix.clear();

			return coff;
	}


//obliczanie korelacji
	double Hrv2:: getCorrelation(double varb1, double varb2, vector<double> war, vector<double> c){
		vector <double> ziL;
		vector <double> ziz;
		vector <double> LiL;
		vector <double> sygnal;
			
		double sum_z_L, sum_L, sum_z, sum_z_z, sum_L_L,nz1;
		int n=c.size();

			for(int i=0; i<n; i++){
				sygnal.push_back((c[i]*varb1)+varb2);
				}
			
			for(int i=0; i<n; i++){
				ziL.push_back((sygnal[i] * war[i]));
				}

			for(int i=0; i<n; i++){
				ziz.push_back((sygnal[i] * sygnal[i]));
				}

			for(int i=0; i<n; i++){
				LiL.push_back((war[i] * war[i]));
				}

			nz1=sygnal.size();

			sum_z_L=sum(ziL);
			sum_L=sum(war);
			sum_z=sum(sygnal);
			sum_z_z=sum(ziz);
			sum_L_L=sum(LiL);
			ziL.clear();
			ziz.clear();
			LiL.clear();
			sygnal.clear();

			return ((nz1*sum_z_L-sum_L*sum_z)/(sqrt(nz1*sum_z_z-(sum_z*sum_z))*sqrt(nz1*sum_L_L-pow(sum_L, 2))));	
		}

//znajdywanie indeksu wartosci max
	double Hrv2:: maxIndex(vector<double> v){
			vector<double> v2;
			v2=v;
			sort(v.begin(), v.end());
			double max_v;
			int s_v=v.size();
			for (int i = 0; i < s_v; i++){
				if(v2[i]==v[s_v-1]) max_v=i;
			}
			return max_v;

	}



// dopasowanie
    map<string, double> Hrv2 :: fit(map<string,vector<double>> histValues){
        vector<double>::iterator nrprobka;
		vector<double>::iterator nrprobka_lewe;
		vector<double>::iterator nrprobka_prawe;
		vector <double> hist = histValues["values"];
		vector <double> czas = histValues["start_time"];
		vector <double> lewewartosci;
		vector <double> leweczas;
		vector <double> prawewartosci;
		vector <double> praweczas;
		map<string, double> coff, coff2;
		vector<double> b1_lewe;
		vector<double> b2_lewe;
		vector<double> b1_prawe;
		vector<double> b2_prawe; 
		double b1,b2, wsp, b11, b22, wsp2;
		vector <double> wspPL, wspPP;
		
		nrprobka = (max_element(hist.begin(), hist.end())); //wartosc max
		auto probka= distance(hist.begin(), nrprobka); //index wartosci max

		for(int k=0; k<probka-2; k++){ 
			//wyznaczanie kolenych punktow dla ktorych ma byc dopasowanie (1,2...,maksimum),(2,3,..., maksimum) i a¿ zostan¹ 3 probki
			for(int j=k;j<=probka;j++) {
				lewewartosci.push_back(hist[j]);
				leweczas.push_back(czas[j]);
			}
			coff=getCoff(lewewartosci, leweczas);
			b1=coff["b1"];
			b2=coff["b2"];
			b1_lewe.push_back(b1);
			b2_lewe.push_back(b2);

			wsp=getCorrelation(b1,b2,lewewartosci, leweczas);
			wspPL.push_back(wsp);
			lewewartosci.clear();
			leweczas.clear();

		}

		nrprobka_lewe = (max_element(wspPL.begin(), wspPL.end()));
		auto probka_lewe= distance(wspPL.begin(), nrprobka_lewe);
		double x0_lewe=(-b2_lewe[probka_lewe]/b1_lewe[probka_lewe]);

		for(int k=probka+2; k<hist.size(); k++){
			for(int j=probka;j<=k;j++) {
				prawewartosci.push_back(hist[j]);
				praweczas.push_back(czas[j]);
			}
			coff2=getCoff(prawewartosci, praweczas);
			b11=coff2["b1"];
			b22=coff2["b2"];
			b1_prawe.push_back(b11);
			b2_prawe.push_back(b22);

			wsp2=getCorrelation(b11,b22,prawewartosci, praweczas);
			wspPP.push_back(wsp2);
			prawewartosci.clear();
			praweczas.clear();

		}	

		nrprobka_prawe = (max_element(wspPP.begin(), wspPP.end()));
		auto probka_prawe= distance(wspPP.begin(), nrprobka_prawe);
		double x0_prawe=(-b2_prawe[probka_prawe]/b1_prawe[probka_prawe]);
		
		// wpisywanie do mapy wartosci wpsolczynnikow, ktore stanowia najlepsze dopasownie
		map<string, double> fitValues;
		fitValues["x0_lewe"]=x0_lewe; 
		fitValues["x0_prawe"]=x0_prawe;
		
        return fitValues;
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

		for( int i = 0; i < val.size(); i++ ){
			if (val[i]<a || val[i]>b){
				if(i>0)    usun.push_back(i-1);
				usun.push_back(i);
				}
			}

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

 //wyznaczanie  wspolrzednych osi sd1 i sd2 na wykresie Poincere
	map<string, vector<double>> Hrv2::sdPoints(map<string,vector<double>> x1_x2 ){
		vector <double> tabplus;
		map<string,double> poinParams=poincareParams(x1_x2);
        map<string, vector<double>> sdPoint;
		double SD1, SD2, centroid;
		vector<double> X1, Y1, X2, Y2;

		tabplus = x1_x2["x1"];
		SD1 = poinParams["sd1"];
		SD2 = poinParams["sd2"];
		centroid=mean2(tabplus);

		X1.push_back(centroid-((sqrt(2)/2)*SD1));
		X1.push_back(centroid);
		Y1.push_back(centroid+((sqrt(2)/2)*SD1));
		Y1.push_back(centroid);
		X2.push_back(centroid);
		X2.push_back(centroid+((sqrt(2)/2)*SD2));
		Y2.push_back(centroid);
		Y2.push_back(centroid+((sqrt(2)/2)*SD2));
	
		sdPoint["sd1_x"] = X1;
		sdPoint["sd1_y"] = Y1;
		sdPoint["sd2_x"] = X2;
		sdPoint["sd2_y"] = Y2;

		return sdPoint;

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
      double Hrv2::triangleRR(map<string,vector<double>>histValues){
        map<string, double> fitValues= fit(histValues);
		vector <double> start= histValues["start_time"];
		vector <double> kon= histValues["end_time"];
		vector <double> hist= histValues["values"];
		double x0_lewe, x0_prawe;
		x0_lewe= fitValues["x0_lewe"];
		x0_prawe= fitValues["x0_prawe"];
		
        double triRR;
		double c=kon[0]-start[0];
		int a= ceil((x0_lewe-start[0])/c); 
		int b= ceil((x0_prawe-start[0])/c); 
        
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
    double Hrv2:: tinn(map<string,vector<double>> histValues){
        
		map<string, double> fitValues= fit(histValues);
		double x0_lewe, x0_prawe, TINN;
		x0_lewe= fitValues["x0_lewe"];
		x0_prawe= fitValues["x0_prawe"];

		TINN=x0_prawe - x0_lewe;
		
		return TINN;
    }



// funkcja zwracaj¹ca parametry geometryczne sd1, sd2, tinn, inteks trójk¹tny, entropie aproksymacji i próby
	Hrv2Result* Hrv2 :: compute(ResultKeeper* rkp) {
		vector<unsigned int> vectorIntow = rkp->getRPeaks()->getRPeaks();
		int size = vectorIntow.size();
		for (int i = 0; i<size-1; i++ )
		{
			r_peaks.push_back(vectorIntow.at(i));
		}


		//r_peaks = rkp->getRPeaks()->getRPeaks();//(?) pobieranie vectora r_peaków (do poprawienia)
		freq= 360;//(?) pobieranie czestotliwosci próbkowania (do poprawienia)
        N = r_peaks.size() -1; 
		vector<double> RR;
		double std, sd1,sd2;
		RR=create_RR_intervals();
		std=stDeviation2(RR);
		this->histValues=createHist(RR,std);
		this->x1_x2=poincareVectors(RR);
		double apen, samen, triRR, tinnP;
		map<string,double> sd1_sd2;
		map<string,double> hrv2p;
		map<string,vector<double>> sdPoint;
		apen=calculateApen(RR,std);
		samen=calculateSamen(RR,std);
		tinnP= tinn(histValues);
		triRR= triangleRR(histValues);
		sd1_sd2 = poincareParams(x1_x2);
		sdPoint=sdPoints(x1_x2);
		sd1=sd1_sd2["sd1"];
		sd2=sd1_sd2["sd2"];
		
		hrv2p["apen"]=apen;
		hrv2p["samen"]=samen;
		hrv2p["tinn"]=tinnP;
		hrv2p["tri"]=triRR;
		hrv2p["sd1"]=sd1;
		hrv2p["sd2"]=sd2;

		Hrv2Result b = Hrv2Result(); 
		b.setHrv2Result(hrv2p, histValues, x1_x2,sdPoint);
		return b.getResult();

	

	}

