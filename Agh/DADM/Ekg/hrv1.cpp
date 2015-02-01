#include <hrv1.h> //plik nag³ówkowy
#include <iostream> //biblioteka do operacji wejœcia/wyjœcia
#include <numeric> //biblioteka z której u¿yta jest funkcja accumulate
#include <cmath> //biblioteka zawieraj¹ca potrzebne funkcje matematyczne (pierwiastek,potêga,zaokr¹glanie w górê lub dó³)
#include <map> //biblioteka zawiraj¹ca operacje, które mo¿na wykonywaæ na mapach
#include <iostream> //biblioteka operacji wejœcia-wyjœcia
#include <string> //biblioteka do operacji na stringach (kluczach w mapie)

using namespace std;

const double PI_const = 3.14;

/* STRUKTURA DO SPRAWDZANIA POPRAWNOŒCI LICZENIA
struct Output {
	map<string, double> timeParameters;
	map<string, double> freqParameters;
	vector<double> power;
	vector<double> frequency;
};*/
struct Lomb_param {
		vector<double> power;
		vector<double> frequency;
};


class HRV1: public AbstractModule<HRV1Result> {

public:
/* RZECZY DO SPRAWDZANIA POPRAWNOŒCI DZIA£ANIA 
 //STRUKTURY DO SPRAWDZANIA
    map<string, double> timeParameter;
	map<string, double> freqParameter;

			
	Output time_freq_compute(vector < double > &temp_vec, int fp){
	Output out_data;
	vector<double> i_rr= inter_RR(temp_vec, fp);
	//vector<double> i_rr= temp_vec;
	out_data.timeParameters["RR_mean"]= RR_mean(i_rr);
	out_data.timeParameters["SDNN"]= SDNN(i_rr);
	out_data.timeParameters["RMSSD"]= RMSSD(i_rr);
	out_data.timeParameters["NN50"]= NN50(i_rr);
	out_data.timeParameters["pNN50"]= pNN50(i_rr);
	out_data.timeParameters["SDANN"]= SDANN(i_rr);
	out_data.timeParameters["SDANN_index"]= SDANN_index(i_rr);
	out_data.timeParameters["SDSD"]= SDSD(i_rr);

	vector<double> i_rrt = inter_RRt(temp_vec, fp);
	//Lomb_param struct1 = Lomb_Scargle(i_rrt); //struktura Lomb_param, która zawiera pary moc czêstotliwoœæ
	Lomb_param struct1 = lomb(i_rrt);
	out_data.power = struct1.power;
	out_data.frequency = struct1.frequency;

	out_data.freqParameters["TP"] = TP_Power(struct1.power, struct1.frequency);
	out_data.freqParameters["HF"] = HF_Power(struct1.power, struct1.frequency);
	out_data.freqParameters["LF"] = LF_Power(struct1.power, struct1.frequency);
	out_data.freqParameters["VLF"] = VLF_Power(struct1.power, struct1.frequency);
	out_data.freqParameters["ULF"] = ULF_Power(struct1.power, struct1.frequency);
	out_data.freqParameters["LFHF"] = LFHF_Power(struct1.power, struct1.frequency);

	return out_data;
	}

/* //FUNKCJA DO WCZYTYWANIA z PLIKU TXT
	vector<double> read_from_file(string filepath){ //funkcja do wczytywania danych z pliku
    
		 string line;
		 size_t st;
		 double line_double;
		 vector<double> data_input;
		 ifstream data_in;
		 data_in.open(filepath);
		 if (data_in.is_open())
		 {
		   while (getline(data_in,line))
		   { 
			line_double = stod(line, &st);
			data_input.push_back(line_double);   
			}
		  data_in.close();
		 }
		 else 
		  cout << "Unable to open file" << endl; 
 
		return data_input;
	}

	Lomb_param computeFreq(vector < double > tab){ //mapa parametrów czêstotliwoœciowych
		vector<double> i_rrt = inter_RRt(tab, 1);
		//Lomb_param struct1 = Lomb_Scargle(i_rrt); //Lomb_param
		Lomb_param struct1 = lomb(i_rrt);
		/*freqParameter["TP"] = TP_Power(struct1.power, struct1.frequency);
		freqParameter["HF"] = HF_Power(struct1.power, struct1.frequency);
		freqParameter["LF"] = LF_Power(struct1.power, struct1.frequency);
		freqParameter["VLF"] = VLF_Power(struct1.power, struct1.frequency);
		freqParameter["ULF"] = ULF_Power(struct1.power, struct1.frequency);
		freqParameter["LFHF"] = LFHF_Power(struct1.power, struct1.frequency);
		return struct1;
	}*/

	vector<double> type_change(vector <unsigned int> &temp_vec){
	//Zmiana wektora wartoœci typu unsigned int na wektor wartoœciu double.
		vector<double> new_vec(temp_vec.size());
		new_vec.clear();
		for (unsigned int i = 0; i<temp_vec.size(); i++){
			new_vec.push_back((double)temp_vec[i]); //dodawanie zrzutowanego na double elementu na koniec wektora
		}
		return new_vec;
	}

	vector<double> inter_RR(vector<double> &temp_vec, double fp){ 
	/*Zmiana wektora próbek na wektor interwa³ów RR - koniecznoœæ podzielenia przez czêstotliwoœæ próbkowania
	w zwi¹zku z tym, ¿e potrzebujemy interwa³y w dziedzinie czasu.
	Niniejsza operacja jest konieczne do dalszego wyliczania parametrów.*/
		vector<double> inter_rr(temp_vec.size()-1);

		for (unsigned i = 1; i<temp_vec.size(); i++){
            inter_rr[i-1] = (temp_vec[i] - temp_vec[i-1])*1000/fp;
		}

		return inter_rr;
	}

	vector<double> inter_RRt(vector<double> &temp_vec, double fp){
	/*Zmiana wektora próbek na wektor interwa³ów RR przy czym tutaj interwa³y s¹ liczone wzglêdem pierwszego interwa³u.
	Tego typu wektor przyda siê podczas obliczania parametrów czêstotliwoœciowych metod¹ periodogramu.*/
		double suma;
		vector<double> inter_rrt(temp_vec.size()-1);

		suma = temp_vec[0]/fp;
		for (unsigned i = 0; i<temp_vec.size()-1; i++){
			inter_rrt[i] = suma;
			suma +=(temp_vec[i+1] - temp_vec[i]) /fp;
		}

		return inter_rrt;
	}

	double round(double value){
	//funkcja zaokr¹glaj¹ca
		double round;

		if (value<0)
            round = ceil(value-0.5);
		else
             round = floor(value+0.5);

		return round;
	}


//******************************     OBLICZANIE PARAMETRÓW CZASOWYCH     ******************************


	double RR_mean(vector<double> &temp_vec){
	//Obliczanie parametru RR_mean, czyli wartoœci œredniej interwa³ów RR
		double sum;
		double rr_mean;

		sum = accumulate(temp_vec.begin(),temp_vec.end(),0.0); //zliczenie sumy wszystkich elementów wektora
		rr_mean = sum/temp_vec.size(); //wyliczenie œredniej

		return rr_mean;
	}

	double SDNN(vector<double> &temp_vec){
	//Obliczenie parametru SDNN, czyli odchylenia standardowego interwa³ów RR
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
   //Obliczenie parametru RMSSD, czyli pierwiastka kwadratowego ze œredniej kwadratów ró¿nic pomiêdzy dwoma kolejnymi interwa³ami
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
	//Obliczenie parametru NN50 - liczba interwa³ów RR, których d³ugoœæ przekracza 50ms
		int nn50;

		nn50 = 0;
		for (unsigned i = 1; i<temp_vec.size(); i++){
			if ((temp_vec[i]-temp_vec[i-1]) > 50)
            nn50 = nn50 + 1;
		}

		return nn50;
	}

	double pNN50(vector<double> &temp_vec){
	//Wyznaczenie parametru pNN50 - odsetek ró¿nic pomiêdzy interwa³ami RR, które przekraczaj¹ 50ms
		double pnn50;

		pnn50 = NN50(temp_vec)/(temp_vec.size()-1);

		return pnn50;
	}

	vector<int> index_300(vector<double> &temp_vec){
	//Wektor indeksów 5 minutowych (przedzia³y 300sekund)
		int N;  //liczba przedzialow 5 minutowych
		int i; //indeks calego wektora
		double sum;
		vector<int> index(N+1); //wektor indeksów przedzia³ów 5 minutowych (300s)

		sum = 0;
		i = 0;
		N = int(floor((accumulate(temp_vec.begin(),temp_vec.end(),0.0))/300));
		index.clear();
		index.push_back(0); //poczatek pierwszego przedzialu to pierwsza probka
		for (int j = 0; j <	N; j++){ //iteracja tylko po pe³nych przedzia³ach
			sum = 0;
			while ( (sum<300) && (i<temp_vec.size())){
            sum = sum + temp_vec[i];
            i = i + 1;
			}
			index.push_back(i-1); //nale¿y tutaj odj¹æ -1 od i, gdy¿ w ostatniej iteracji wylecieliœmy na nastepn¹ próbkê
		} 

		return index;
	}

	double SDANN(vector<double> &temp_vec){
	/*Obliczenie parametru SDANN - œrednie odchylenie ze wszystkich œrednich interwa³ów RR w 5 minutowych segmentach 
	ca³ego zapisu*/
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
	/*Wyznaczenie wspó³czynnika SDANN_index - œrednia z odchyleñ standardowych interwa³ów RR w 5 minutowych segmentach
	czasowych ca³ego zapisu*/
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
	//Wyznaczenie wspó³czynnika SDSD - odchylenie standardowe róznic pomiêdzy s¹siaduj¹cymi interwa³ami RR
		double sdsd;
		vector<double> a;

		for (unsigned i = 1; i<temp_vec.size(); i++){
			a.push_back(temp_vec[i] - temp_vec[i-1]);
		}
		sdsd = SDNN(a);
		a.clear();

		return sdsd;
	}


//******************************     OBLICZANIE PARAMETRÓW CZÊSTOTLIWOŒCIOWYCH     ******************************
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
	for(int i=0;i<length*2;++i)
	{
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

/* STARY LOMB !
	Lomb_param Lomb_Scargle(vector<double> &temp_vec){
	//Wyznaczenie parametrów czêstotliwoœciowych meotd¹ Lomba-Scargle'a
		int over_samp; //parametr nadpróbkowania czêstotliwoœci
		int hifac;
		int time_n; //rozmiar wektora temp_vec
		double period; //d³ugoœæ-1-time[0]
		double mean;
		double var;
		double f0;
		double num_freq; //by³ int, bo hifac 4, wiêc nie potrzebny double
		double fd; //normalizacja wektora czêstotliwoœci do 0,5
		vector<double> time(temp_vec.size()); //tworzenie wektora czasu
		vector<double> frequency(num_freq); //wektor czêstotliwoœci
		vector<double> omega(num_freq); //wektor omega
		vector<double> tau(num_freq); //wektor tau
		vector<double> Power_w(num_freq); //power(w)
		vector<double> Power(num_freq/2);
		vector<double> frequency2(num_freq/2);

		over_samp = 1;
		hifac = 4;
		time.clear();
		time.push_back(temp_vec[0]);
		for (unsigned i = 1; i<temp_vec.size(); i++){
			time.push_back(time[i-1] + temp_vec[i]);
		} 
		time_n = temp_vec.size();
		period = time[temp_vec.size()-1] - time[0];
		mean = RR_mean(temp_vec); //obliczenie œredniej
		var = SDNN(temp_vec); //obliczenie odchylenia standardowego - konieczne dla policzenia wariancji
		var = var * var; //obliczenie wariancji
		f0 = 1 / (period * over_samp); //f0
		//double step = f0;	
		num_freq = (over_samp * hifac * time_n) / 2;
		frequency.clear();
		frequency.push_back(f0); //empty() true if empty
		omega.clear();
		omega.push_back(frequency[0] * PI_const * 2); //w = 2*PI_const*f;  PI_const = PI_const
		for (int i = 1; i<num_freq; i++){
			frequency.push_back(frequency[i-1] + f0 ); //wektor czêstotliwoœci o wymiarze num_freq //normalizowane !!!!f0
			omega.push_back(frequency[i] * PI_const * 2); //wektor omega o wymiarze num_freq
		}
		tau.clear();
		for (int i = 0; i < num_freq; i++){  //po omegach w
			double sinu = 0; //temp sin
			double cosi = 0; //temp
			double sum1 = 0; //temp
			double sum2 = 0; //temp
			for (int j = 0; j < time_n; j++){ //po czasach t
				sinu = sin(2 * omega[i] * time[j]);
				sum1 = sinu + sum1;
				cosi = cos(2 * omega[i] * time[j]);
				sum2 = cosi + sum2;
			}
			tau.push_back(atan2(sum1,sum2));
			tau[i] = tau[i]/(2*omega[i]);
		}
		Power_w.clear();
		for (int i = 0; i < num_freq; i++){
			double temp; //temp
			double cosi; //temp
			double sinu; //temp
			double sum_licznik1 = 0; //temp
			double sum_licznik2 = 0; //temp
			double sum_mianownik1 = 0; //temp
			double sum_mianownik2 = 0; //temp		
			for(int j = 0; j < time_n; j++){	
				temp = omega[i] * time[j] - omega[i] * tau[i]; //temp w*ti - w*tau
				cosi = cos(temp);
				sum_mianownik2 = cosi * cosi + sum_mianownik2;
				sinu = sin(temp);
				sum_mianownik1 = sinu * sinu + sum_mianownik1;
				sum_licznik1 = sinu * (temp_vec[j] - mean) + sum_licznik1;
				sum_licznik2 = cosi * (temp_vec[j] - mean) + sum_licznik2;
			}
			Power_w.push_back(((sum_licznik1 * sum_licznik1)/sum_mianownik1 + (sum_licznik2 * sum_licznik2)/sum_mianownik2)/(2*var));
		}
		Power.assign(Power_w.begin(), Power_w.end()-(num_freq/2));
		frequency2.assign(frequency.begin(), frequency.end()-(num_freq/2));
		fd= 2*(num_freq/2) * f0; //Normalizacja wektora czêstotliwoœci do 0.5
		for(int i = 0; i  <frequency2.size(); i++){ 
			frequency2[i] = frequency2[i] / fd;
		}
		Lomb_param out;
		out.power = Power;
		out.frequency = frequency2;

		return out;
	}
*/
	double TP_Power(vector<double> &temp_vec, vector<double> &f){
	//Wyznaczenie ca³kowitej mocy widma  (zakres poni¿ej 0,4Hz)
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
	//Obliczenie mocy widma w zakresie wysokich czêstotliwoœci (0,15-0,4Hz)
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
	//Wyznaczenie mocy widma w zakresie niskich czêstotliwoœci (0,04-0,15Hz)
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
	//Obliczenie mocy widma w zakresie bardzo niskich czêstotliwoœci (0,003-0,04Hz)
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
	//Wyznaczenie mocy widma w zakresie ultra niskich czêstotliwoœci (poni¿ej 0,003Hz)
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
	//Obliczenie stosunku mocy widm niskich czêstotliwoœci do mocy widm wysokich czêstotliwoœci
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

	 HRV1Result* HRV1 :: compute(ResultKeeper* rkp) const{
		R_peaks_in = *rkp->rpeaks; // vector r pików
        fp= *rkp->freq; // Czêstotliwoœæ próbkowania
		vector<double> inter_rr(R_peaks_in.size()-1);
		inter_rr = inter_RR(R_peaks_in,fp);
		double rr_mean, sdnn, rmssd, nn50, pnn50, ind, sdann, sdann_index, sdsd;
		double tp, hf, lf, vlf, ulf, lfhf;
		rr_mean = RR_mean(inter_rr);
		sdnn = SDNN(inter_rr);
		rmssd = RMSSD(inter_rr);
		nn50 = NN50(inter_rr);
		pnn50 = pNN50(inter_rr);
		ind = index_300(inter_rr);
		sdann = SDANN(inter_rr);
		sdann_index = SDANN_index(inter_rr);
		sdsd = SDSD(inter_rr);
		//TUTAJ TO JA JU¯ SIE POGUBI£EM CO I JAK...
	 }
};