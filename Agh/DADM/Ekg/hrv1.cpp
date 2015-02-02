#include <hrv1.h> //plik nag��wkowy
#include <iostream> //biblioteka do operacji wej�cia/wyj�cia
#include <numeric> //biblioteka z kt�rej u�yta jest funkcja accumulate
#include <cmath> //biblioteka zawieraj�ca potrzebne funkcje matematyczne (pierwiastek,pot�ga,zaokr�glanie w g�r� lub d�)
#include <map> //biblioteka zawiraj�ca operacje, kt�re mo�na wykonywa� na mapach
#include <iostream> //biblioteka operacji wej�cia-wyj�cia
#include <string> //biblioteka do operacji na stringach (kluczach w mapie)

using namespace std;

const double PI_const = 3.14;

struct Lomb_param {
		vector<double> power;
		vector<double> frequency;
};


class HRV1: public AbstractModule<HRV1Result> {

public:

	vector<double> type_change(vector <unsigned int> &temp_vec){
	//Zmiana wektora warto�ci typu unsigned int na wektor warto�ciu double.
		vector<double> new_vec(temp_vec.size());
		new_vec.clear();
		for (unsigned int i = 0; i<temp_vec.size(); i++){
			new_vec.push_back((double)temp_vec[i]); //dodawanie zrzutowanego na double elementu na koniec wektora
		}
		return new_vec;
	}

	vector<double> inter_RR(vector<double> &temp_vec, double fp){ 
	/*Zmiana wektora pr�bek na wektor interwa��w RR - konieczno�� podzielenia przez cz�stotliwo�� pr�bkowania
	w zwi�zku z tym, �e potrzebujemy interwa�y w dziedzinie czasu.
	Niniejsza operacja jest konieczne do dalszego wyliczania parametr�w.*/
		vector<double> inter_rr(temp_vec.size()-1);

		for (unsigned i = 1; i<temp_vec.size(); i++){
            inter_rr[i-1] = (temp_vec[i] - temp_vec[i-1])/fp;
		}

		return inter_rr;
	}

	vector<double> inter_RRt(vector<double> &temp_vec, double fp){
	/*Zmiana wektora pr�bek na wektor interwa��w RR przy czym tutaj interwa�y s� liczone wzgl�dem pierwszego interwa�u.
	Tego typu wektor przyda si� podczas obliczania parametr�w cz�stotliwo�ciowych metod� periodogramu.*/
		double suma;
		vector<double> inter_rrt(temp_vec.size()-1);

		suma = temp_vec[0]/fp;
		for (unsigned i = 0; i<temp_vec.size()-1; i++){
			inter_rrt[i] = suma;
			suma +=(temp_vec[i+1] - temp_vec[i]) /fp;
		}

		return inter_rrt;
	}

//******************************     OBLICZANIE PARAMETR�W CZASOWYCH     ******************************


	double RR_mean(vector<double> &temp_vec){
	//Obliczanie parametru RR_mean, czyli warto�ci �redniej interwa��w RR
		double sum;
		double rr_mean;

		sum = accumulate(temp_vec.begin(),temp_vec.end(),0.0); //zliczenie sumy wszystkich element�w wektora
		rr_mean = sum/temp_vec.size(); //wyliczenie �redniej

		return rr_mean;
	}

	double SDNN(vector<double> &temp_vec){
	//Obliczenie parametru SDNN, czyli odchylenia standardowego interwa��w RR
		double mean;
		double sdnn;
		vector<double> temp(temp_vec.size());

		mean = RR_mean(temp_vec);
		for (unsigned i = 0; i<temp_vec.size(); i++){
			temp[i] = pow((temp_vec[i] - mean),2);
		}
		sdnn = sqrt((accumulate(temp.begin(),temp.end(),0.0))/temp.size());
		temp.clear();
			
		return sdnn;
	}

	double RMSSD(vector<double> &temp_vec){
   //Obliczenie parametru RMSSD, czyli pierwiastka kwadratowego ze �redniej kwadrat�w r�nic pomi�dzy dwoma kolejnymi interwa�ami
		double rmssd;
		vector<double> temp(temp_vec.size());

		for (unsigned i = 0; i<(temp_vec.size()-1); i++){
			temp[i] = pow(temp_vec[i+1] - temp_vec[i],2);
		}
		rmssd = sqrt((std::accumulate(temp.begin(),temp.end(),0.0))/temp.size());
		temp.clear();

		return rmssd;
	}

	double NN50(vector<double> &temp_vec){
	//Obliczenie parametru NN50 - liczba interwa��w RR, kt�rych d�ugo�� przekracza 50ms
		int nn50;

		nn50 = 0;
		for (unsigned i = 1; i<temp_vec.size(); i++){
			if ((temp_vec[i]-temp_vec[i-1]) > 0.05)
            nn50 = nn50 + 1;
		}

		return nn50;
	}

	double pNN50(vector<double> &temp_vec){
	//Wyznaczenie parametru pNN50 - odsetek r�nic pomi�dzy interwa�ami RR, kt�re przekraczaj� 50ms
		double pnn50;

		pnn50 = NN50(temp_vec)/(temp_vec.size()-1);

		return pnn50;
	}

	vector<int> index_300(vector<double> &temp_vec){
	//Wektor indeks�w 5 minutowych (przedzia�y 300sekund)
		int N;  //liczba przedzialow 5 minutowych
		int i; //indeks calego wektora
		double sum;
		vector<int> index(N+1); //wektor indeks�w przedzia��w 5 minutowych (300s)

		sum = 0;
		i = 0;
		N = int(floor((accumulate(temp_vec.begin(),temp_vec.end(),0.0))/300));
		index.clear();
		index.push_back(0); //poczatek pierwszego przedzialu to pierwsza probka
		for (int j = 0; j <	N; j++){ //iteracja tylko po pe�nych przedzia�ach
			sum = 0;
			while ( (sum<300) && (i<temp_vec.size())){
            sum = sum + temp_vec[i];
            i = i + 1;
			}
			index.push_back(i-1); //nale�y tutaj odj�� -1 od i, gdy� w ostatniej iteracji wylecieli�my na nastepn� pr�bk�
		} 

		return index;
	}

	double SDANN(vector<double> &temp_vec){
	/*Obliczenie parametru SDANN - �rednie odchylenie ze wszystkich �rednich interwa��w RR w 5 minutowych segmentach 
	ca�ego zapisu*/
		double sdann;
		vector<int> tab = index_300(temp_vec);
		vector<double> srednia;

		for (unsigned int i = 1; i < tab.size() ; i++){
        srednia.push_back((accumulate(temp_vec.begin()+tab[i-1],temp_vec.begin()+tab[i],0.0))/(tab[i-1]-tab[i]));
		}
		sdann = SDNN(srednia);
		tab.clear();
		srednia.clear();

		return sdann;
	}

	double SDANN_index(vector<double> &temp_vec){
	/*Wyznaczenie wsp�czynnika SDANN_index - �rednia z odchyle� standardowych interwa��w RR w 5 minutowych segmentach
	czasowych ca�ego zapisu*/
		int N;
		double odchyl;
		double sdanni;
		vector <double> odchylenia;
		vector<double> temp;
		vector<int> tab = index_300(temp_vec);

		N = tab.size();
		for (int i = 1; i<N; i++){
			temp.assign(temp_vec.begin()+tab[i-1],temp_vec.begin()+tab[i]); //kopiowanie do wektora temp_vec zakresu 300s (5minut)
			odchyl = SDNN(temp); //obliczenie odchylenia standardowego dla przedzialu 5 minut (300s)
			odchylenia.push_back(odchyl);
		}
		sdanni = RR_mean(odchylenia); //srednia z odchylen
		tab.clear();
		temp.clear();
		odchylenia.clear();

		return sdanni;
	}

	double SDSD(vector<double> &temp_vec){
	//Wyznaczenie wsp�czynnika SDSD - odchylenie standardowe r�znic pomi�dzy s�siaduj�cymi interwa�ami RR
		double sdsd;
		vector<double> a;

		for (unsigned i = 1; i<temp_vec.size(); i++){
			a.push_back(temp_vec[i] - temp_vec[i-1]);
		}
		sdsd = SDNN(a);
		a.clear();

		return sdsd;
	}


//******************************     OBLICZANIE PARAMETR�W CZ�STOTLIWO�CIOWYCH     ******************************
	Lomb_param lomb(vector<double> intervals){
	vector<double> freqs;
	vector<double> int_time;
	vector<double> tau;
	vector<double> PSD;

	double average = RR_mean(intervals);
	double stddev = SDNN(intervals);
	double variance=stddev*stddev;
	int_time.push_back(0);
	for(int i=0;i<intervals.size()-1;++i)
		int_time.push_back(int_time[i]+intervals[i]/1000);
	int length=intervals.size();
	double timespan=int_time[length-1];
	freqs.push_back(2*PI_const/timespan);
	for(int i=1;i<length*2;++i)
		freqs.push_back((i+1)*2*PI_const/timespan);
	for(int i=0;i<length*2;++i){
		double sin_sum=0;
		double cos_sum=0;
		for(int n=0;n<length;++n)
			sin_sum+=sin(2*freqs[i]*int_time[n]);
		for(int n=0;n<length;++n)
			cos_sum+=cos(2*freqs[i]*int_time[n]);
		tau.push_back(atan2(sin_sum, cos_sum)/(2*freqs[i]));
	}
	for(int i=0;i<length*2;++i){
		double stddevcos=0;
		double cossqr=0;
		double stddevsin=0;
		double sinsqr=0;
		for(int n=0;n<length;++n)
			stddevcos+=(intervals[n]-average)*cos(freqs[i]*(int_time[n]-tau[i]));
		stddevcos*=stddevcos;
		for(int n=0;n<length;++n)
			stddevsin+=(intervals[n]-average)*sin(freqs[i]*(int_time[n]-tau[i]));
		stddevsin*=stddevsin;
		for(int n=0;n<length;++n)
			cossqr+=cos(freqs[i]*(int_time[n]-tau[i]))*cos(freqs[i]*(int_time[n]-tau[i]));
		for(int n=0;n<length;++n)
			sinsqr+=sin(freqs[i]*(int_time[n]-tau[i]))*sin(freqs[i]*(int_time[n]-tau[i]));
		PSD.push_back((stddevcos/cossqr+stddevsin/sinsqr)/(2*variance));
	}
	for(int i=0;i<freqs.size();++i){
		freqs[i]/=(2*PI_const);
		freqs[i]/=(10000);
	}

	Lomb_param out;
		out.power = PSD;
		out.frequency = freqs;

	return out;

}
	double TP_Power(vector<double> &temp_vec, vector<double> &f){
	//Wyznaczenie ca�kowitej mocy widma  (zakres poni�ej 0,4Hz)
		double TP;

		TP = 0;
		for(int i = 0; i < f.size(); i++){
			if (f[i] < 0.4){
				TP = temp_vec[i] + TP;
			}
		}

		return (TP);
	}
	double HF_Power(vector<double> &temp_vec, vector<double> &f){
	//Obliczenie mocy widma w zakresie wysokich cz�stotliwo�ci (0,15-0,4Hz)
		double HF;

		HF = 0;
		for(int i = 0; i < f.size(); i++){
			if(f[i] >= 0.15 && f[i] < 0.4){
				HF = temp_vec[i] + HF;
			}
		}
		return (HF);
	}

	double LF_Power(vector<double> &temp_vec, vector<double> &f){
	//Wyznaczenie mocy widma w zakresie niskich cz�stotliwo�ci (0,04-0,15Hz)
		double LF;

		LF = 0;
		for(int i = 0; i < f.size(); i++){
			if (f[i] > 0.04 && f[i] < 0.15){
				LF = temp_vec[i] + LF;
			}
		}
		return (LF);
	}

	double VLF_Power(vector<double> &temp_vec, vector<double> &f){
	//Obliczenie mocy widma w zakresie bardzo niskich cz�stotliwo�ci (0,003-0,04Hz)
		double VLF;

		VLF = 0;
		for(int i = 0; i < f.size(); i++){
			if (f[i] > 0.003 && f[i] < 0.04){
				VLF = temp_vec[i] + VLF;
			}
		}
		return (VLF);
	}

	double ULF_Power(vector<double> &temp_vec, vector<double> &f){	
	//Wyznaczenie mocy widma w zakresie ultra niskich cz�stotliwo�ci (poni�ej 0,003Hz)
		double ULF = 0;

		ULF = 0;
		for(int i = 0; i < f.size(); i++){
			if (f[i] <= 0.003){
				ULF = temp_vec[i] + ULF;
			}
		}
		return (ULF);
	}

	double LFHF_Power(vector<double> &temp_vec, vector<double> &f){
	//Obliczenie stosunku mocy widm niskich cz�stotliwo�ci do mocy widm wysokich cz�stotliwo�ci
		double LF;
		double HF;

		LF = 0;
		HF = 0;
		for(int i = 0; i < f.size(); i++){
			if (f[i] > 0.04 && f[i] < 0.15){
				LF = temp_vec[i] + LF;
			}
			else if(f[i] >= 0.15 && f[i] < 0.4){
				HF = temp_vec[i] + HF;
			}
		}

		return (LF/HF);
	}

		//FUNKCJA COMPUTE !

	 HRV1Result* HRV1 :: compute(ResultKeeper* rkp) {
		
		HRV1Result result = HRV1Result();
		R_peaks_in = *rkp->rpeaks; // vector r pik�w
        fp= *rkp->freq; // Cz�stotliwo�� pr�bkowania
		vector<double> inter_rr(R_peaks_in.size()-1);
		inter_rr = inter_RR(R_peaks_in,fp);
		map<string, double> timeParam;
		map<string, double> freqParam;
		//mno�ymy razy 100 bo zamiana z sekund na ms !
		timeParam["RR_mean"] = RR_mean(inter_rr)*1000;
		timeParam["SDNN"] = SDNN(inter_rr)*1000;
		timeParam["RMSSD"]= RMSSD(inter_rr)*1000;
		timeParam["NN50"]= NN50(inter_rr);
		timeParam["pNN50"]= pNN50(inter_rr);
		timeParam["SDANN"]= SDANN(inter_rr)*1000;
		timeParam["SDANN_index"]= SDANN_index(inter_rr)*1000;
		timeParam["SDSD"]= SDSD(inter_rr)*1000;
		
		vector<double> inter_rrt(R_peaks_in.size()-1);
		vector<double> power;
		vector<double> freq;
		inter_rrt = inter_RRt(R_peaks_in, fp);
		Lomb_param struct1 = lomb(inter_rrt);
		freqParam["TP"] = TP_Power(struct1.power, struct1.frequency);
		freqParam["HF"] = HF_Power(struct1.power, struct1.frequency);
		freqParam["LF"] = LF_Power(struct1.power, struct1.frequency);
		freqParam["VLF"] = VLF_Power(struct1.power, struct1.frequency);
		freqParam["ULF"] = ULF_Power(struct1.power, struct1.frequency);
		freqParam["LFHF"] = LFHF_Power(struct1.power, struct1.frequency);
		power = struct1.power;
		freq = struct1.frequency;

		result.setHRV1Result(timeParam, freqParam, );

		return result.getResult();

	 }
};