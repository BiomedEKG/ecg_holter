//#define _USE_MATH_DEFINES

#include "hrv1.h"
#include <numeric> //biblioteka z której u¿yta jest funkcja accumulate
#include <cmath> //biblioteka zawieraj¹ca potrzebne funkcje matematyczne (pierwiastek,potêga,zaokr¹glanie w górê lub dó³)
#include <map> //biblioteka zawiraj¹ca operacje, które mo¿na wykonywaæ na mapach
#include <iostream> //biblioteka operacji wejœcia-wyjœcia
#include <string> //biblioteka do operacji na stringach (kluczach w mapie)
#include <fstream>
#include <string>

using namespace std;

const double PI_const = 3.14;

struct Output {
	map<string, double> timeParameters;
	map<string, double> freqParameters;
	vector<double> power;
	vector<double> frequency;
};

class HRV1 {

public:
	map<string, double> timeParameter;
	map<string, double> freqParameter;
	struct Lomb_pair {
		vector<double> power;
		vector<double> frequency;
	};
			
	Output time_freq_compute(vector < double > &temp_vec, int fp){
	Output out_data;
	vector<double> i_rr= inter_RR(temp_vec, fp);
	out_data.timeParameters["RR_mean"]= RR_mean(i_rr);
	out_data.timeParameters["SDNN"]= SDNN(i_rr);
	out_data.timeParameters["RMSSD"]= RMSSD(i_rr);
	out_data.timeParameters["NN50"]= NN50(i_rr);
	out_data.timeParameters["pNN50"]= pNN50(i_rr);
	out_data.timeParameters["SDANN"]= SDANN(i_rr);
	out_data.timeParameters["SDANN_index"]= SDANN_index(i_rr);
	out_data.timeParameters["SDSD"]= SDSD(i_rr);

	vector<double> i_rrt = inter_RRt(temp_vec, fp);
	Lomb_pair struct1 = Lomb(i_rrt); //Lomb_pair
	out_data.power = struct1.power;
	out_data.frequency = struct1.frequency;

	out_data.freqParameters["TP"] = TP_Power(struct1.power, struct1.frequency);
	out_data.freqParameters["HF"] = HF_Power(struct1.power, struct1.frequency);
	out_data.freqParameters["LF"] = LF_Power(struct1.power, struct1.frequency);
	out_data.freqParameters["VLF"] = VLF_Power(struct1.power, struct1.frequency);
	out_data.freqParameters["ULF"] = ULF_Power(struct1.power, struct1.frequency);
	out_data.freqParameters["LFHF"] = LowHigh(struct1.power, struct1.frequency);

	return out_data;
	}

		vector<double> read_from_file(string filepath){
    
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
	map<string, double> compute (vector <double> &temp_vec){
		timeParameter["RR_mean"]= RR_mean(temp_vec);
		timeParameter["SDNN"]= SDNN(temp_vec);
		timeParameter["RMSSD"]= RMSSD(temp_vec);
		timeParameter["NN50"]= NN50(temp_vec);
		timeParameter["pNN50"]= pNN50(temp_vec);
		timeParameter["SDANN"]= SDANN(temp_vec);
		timeParameter["SDANN_index"]= SDANN_index(temp_vec);
		timeParameter["SDSD"]= SDSD(temp_vec);
		return timeParameter;
	}

	map<string, double> computeFreq(vector < double > tab){
		Lomb_pair struct1 = Lomb(tab); //Lomb_pair
		freqParameter["TP"] = TP_Power(struct1.power, struct1.frequency);
		freqParameter["HF"] = HF_Power(struct1.power, struct1.frequency);
		freqParameter["LF"] = LF_Power(struct1.power, struct1.frequency);
		freqParameter["VLF"] = VLF_Power(struct1.power, struct1.frequency);
		freqParameter["ULF"] = ULF_Power(struct1.power, struct1.frequency);
		freqParameter["LFHF"] = LowHigh(struct1.power, struct1.frequency);
		return freqParameter;
	}

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
            inter_rr[i-1] = (temp_vec[i] - temp_vec[i-1])/fp;
		}
		return inter_rr;
	}

	vector<double> inter_RRt(vector<double> &temp_vec, double fp){
	/*Zmiana wektora próbek na wektor interwa³ów RR przy czym tutaj interwa³y s¹ liczone wzglêdem pierwszego interwa³u.
	Tego typu wektor przyda siê podczas obliczania parametrów czêstotliwoœciowych metod¹ periodogramu.*/
		vector<double> inter_rrt(temp_vec.size()-1);
		double suma = temp_vec[0]/fp;
		for (unsigned i = 0; i<temp_vec.size()-1; i++){
			inter_rrt[i] = suma;
			suma +=(temp_vec[i+1] - temp_vec[i]) /fp;
		}
		return inter_rrt;
	}

	double round(double value){

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
		double mean;

		sum = accumulate(temp_vec.begin(),temp_vec.end(),0.0); //zliczenie sumy wszystkich elementów wektora
		mean = sum/temp_vec.size(); //wyliczenie œredniej

		return mean;
	}

	double SDNN(vector<double> &temp_vec){
	//Obliczenie parametru SDNN, czyli odchylenia standardowego interwa³ów RR
		double mean;
		vector<double> temp(temp_vec.size());
		double sdnn;

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
		vector<double> temp(temp_vec.size());
		double rmssd;

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
			if ((temp_vec[i]-temp_vec[i-1]) > 0.05)
            nn50 = nn50 +1;
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
		int N;  //liczba przedzialow 300-sekundoych
		int i; //indeks calego wektora
		vector<int> index(N+1); //wektor na indeksy przedzialow co 300 s
		double sum;

		sum = 0;
		i = 0;
		N = int(floor((accumulate(temp_vec.begin(),temp_vec.end(),0.0))/300));
		index.clear();
		index.push_back(0); //poczatek pierwszego przedzialu to pierwsza probka
		//int k = 1; //indeks tablicy przedzialow
		for (int j = 0; j <	N; j++){
			while ( (sum<300) && (i<temp_vec.size())){ //czy tu nie trzeba dodac lub i<vec.size? nie. bo petla j tylko po pelnych przedzialach.
            sum = sum + temp_vec[i];
            i = i + 1;
			}
			index.push_back(i-1); //-1 bo zwiêkszylismy przy ostatniej iteracji na nastepna probke
			//k = k + 1;
		} 

		return index;
	}

	double SDANN(vector<double> &temp_vec){
	/*Obliczenie parametru SDANN - œrednie odchylenie ze wszystkich œrednich interwa³ów RR w 5 minutowych segmentach 
	ca³ego zapisu*/
		vector<int> tab = index_300(temp_vec);
		vector<double> srednia;
		double sdann;

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
		double od;
		double sdanni;
		vector <double> odchylenia;
		vector<double> temp;
		vector<int> tab = index_300(temp_vec);

		N = tab.size();
		for (int i = 1; i<N; i++){
			temp.assign(temp_vec.begin()+tab[i-1],temp_vec.begin()+tab[i]); //skopiowanie do temp przedzialu 300 s
			od = SDNN(temp); //policzenie odchylenia standardowego z przedzialu 300 s
			odchylenia.push_back(od);
		}
		sdanni = RR_mean(odchylenia); //srednia z odchylen
		tab.clear();
		temp.clear();
		odchylenia.clear();

		return sdanni;
	}

	double SDSD(vector<double> &temp_vec){
		vector<double> a;
		double sdsd;

		for (unsigned i = 1; i<temp_vec.size(); i++){
			a.push_back(temp_vec[i] - temp_vec[i-1]);
		}
		sdsd = SDNN(a);
		a.clear();

		return sdsd;
	}


//******************************     OBLICZANIE PARAMETRÓW CZÊSTOTLIWOŒCIOWYCH     ******************************


	Lomb_pair Lomb(vector<double> &vec){
		vector<double> time(vec.size()); //tworzenie wektora czasu
		int ofac = 1; //parametr nadpróbkowania czêstotliwoœci
		int hifac = 4;
		time.clear();
		time.push_back(vec[0]);
		for (unsigned i = 1; i<vec.size(); i++){
        time.push_back(time[i-1] + vec[i]); //wektor czasu o wymiarze length
		} 
		int time_n = vec.size(); //time.size();
		double period = time[vec.size()-1] - time[0]; //length-1-time[0]
		double mean = RR_mean(vec); //œrednia
		double var = SDNN(vec);
		var = var * var; //wariancja
		double f0 = 1 / (period * ofac); //f0
		double step = f0;	
		int num_freq = (ofac * hifac * time_n) / 2; //number of frequencies int bo hifac=4
		vector<double> frequency(num_freq); //wektor czêstotliwoœci
		vector<double> omega(num_freq);
		frequency.clear();
		frequency.push_back(f0); //empty() true if empty
		omega.clear();
		omega.push_back(frequency[0] * PI_const * 2); //w = 2*PI_const*f;  PI_const = PI_const
		for (int i = 1; i<num_freq; i++){
        frequency.push_back(frequency[i-1] + step ); //wektor czêstotliwoœci o wymiarze num_freq //normalizowane
        omega.push_back(frequency[i] * PI_const * 2); //wektor omega o wymiarze num_freq
		}
		vector<double> tau(num_freq);
		tau.clear();
		for (int i = 0; i < num_freq; i++){  //po omegach w
			double sinu = 0; //temp
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
		vector<double> Power_w(num_freq); //power(w)
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
				sum_licznik1 = sinu * (vec[j] - mean) + sum_licznik1;
				sum_licznik2 = cosi * (vec[j] - mean) + sum_licznik2;
			}
			Power_w.push_back(((sum_licznik1 * sum_licznik1)/sum_mianownik1 + (sum_licznik2 * sum_licznik2)/sum_mianownik2)/(2*var));
		}
		vector<double> Power(num_freq/2);
		Power.assign(Power_w.begin(), Power_w.end()-(num_freq/2));
		vector<double> frequency2(num_freq/2);
		frequency2.assign(frequency.begin(), frequency.end()-(num_freq/2));
		double fd= 2*(num_freq/2) * f0; //Normalizacja wektora czêstotliwoœci do 0.5
		for(int i = 0; i  <frequency2.size(); i++){ 
			frequency2[i] = frequency2[i] / fd;
		}
		Lomb_pair out;
		out.power = Power;
		out.frequency = frequency2;
		return out;
	}

	double TP_Power(vector<double> &vec, vector<double> &f){
		double sumTP = 0;
		for(int i = 0; i < f.size(); i++){
			if (f[i] < 0.4){
				sumTP = vec[i] + sumTP;
			}
		}
		return (sumTP);
	}
	double HF_Power(vector<double> &vec, vector<double> &f){
		double sumHF = 0;
		for(int i = 0; i < f.size(); i++){
			if(f[i] >= 0.15 && f[i] < 0.4){
				sumHF = vec[i] + sumHF;
			}
		}
		return (sumHF);
	}

	double LF_Power(vector<double> &vec, vector<double> &f){
		double sumLF = 0;
		for(int i = 0; i < f.size(); i++){
			if (f[i] > 0.04 && f[i] < 0.15){
				sumLF = vec[i] + sumLF;
			}
		}
		return (sumLF);
	}

	double VLF_Power(vector<double> &vec, vector<double> &f){
		double sumVLF = 0;
		for(int i = 0; i < f.size(); i++){
			if (f[i] > 0.003 && f[i] < 0.04){
				sumVLF = vec[i] + sumVLF;
			}
		}
		return (sumVLF);
	}

	double ULF_Power(vector<double> &vec, vector<double> &f){	
		double sumULF = 0;
		for(int i = 0; i < f.size(); i++){
			if (f[i] <= 0.003){
				sumULF = vec[i] + sumULF;
			}
		}
		return (sumULF);
	}

	double LowHigh(vector<double> &vec, vector<double> &f){
		double sumLF = 0;
		double sumHF = 0;
		for(int i = 0; i < f.size(); i++){
			if (f[i] > 0.04 && f[i] < 0.15){
				sumLF = vec[i] + sumLF;
			}
			else if(f[i] >= 0.15 && f[i] < 0.4){
				sumHF = vec[i] + sumHF;
			}
		}
		return (sumLF/sumHF);
	}
};
