#include"Waves.h"

WavesResult* Waves::compute(ResultKeeper *rkp)const {

	vector<double> *ECGBaselineData;
	vector<double> *RPeaksData;
	
	ECGBaselineData = rkp.GetResultECGBaseline.GetECGBaselineData(); /// Przypisanie danych ECGBaseline na ktorych beda wykonywane obliczenia
	RPeaksData = rkp.GetResultRPeaks.GetRPeaksData(); /// Przypisanie danych RPeaks na ktorych beda wykonywane obliczenia
	

	WavesResult  ResultHolder = WavesResult();///stworz obiekt rezultatu
	ResultHolder.SetWavesResultData(WavesData);////Przypisz dane z klasy liczacej do danych klasy z klasy rezultatu

	return ResultHolder.getResult();// Zwroc odpowiedni wskaünik
}

double Waves::get_vector_median(vector<double> v) {
	sort(v.begin(), v.end());
	if (v.size() % 2 == 0) {
		return (v[v.size()/2-1] + v[v.size()/2])/2;
	} else {
		return v[v.size()-1];
	}
}

void Waves::ustaw_qrs_onset(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency){
	vector<double> ECGBaselineDataTP;
	// to jest wektor zawieracjacy indexy punktow qrs_onset w ecgBaselineData
	vector<int> ResultIndexVector;
	double Rv=0.001;

	// 1. transformacja wskazowa przy Rv=0.001 calego przefiltrowanego sygnalu, czyli wszystkich elementow wektora ECGBaselineData
	for (int i=0; i<ECGBaselineData.size(); ++i){
		ECGBaselineDataTP.push_back(atan(ECGBaselineData.at(i)/Rv));
	}
	//	Pt.push_back(atan(window_signal.at(j)/Rv));
		//	M.push_back(sqrt(pow(Rv,2)+ pow(window_signal.at(j),2)));
	

	// 2. poszukiwanie na lewo od kazdego piku R NA PRZETRANSFORMOWANYM SYGNALE punktu takiego, ze fi[n] < 0.25*pi
	//    kolejne probki wektora RPeaksData wskazuja na miejsce w wektorze ECGBaselineData, od ktorego trzeba szukac, cofajac sie
	//    szukac trzeba nie na ECGBaselineData, tylko na wektorze stworzonym w punkcie 1.
	//    dostajemy w wyniku dzialania wektor qrs_lewo numerow probek
	for (int i=RPeaksData.size()-1; i>=0; --i){
		double amp = 1;
		int index = 0;
		while (amp<=0.25*3.1415){
			for (int j = i; j>=0; --j){
				amp = ECGBaselineDataTP.at(j);
				index = j;
			}
		}
		vector<double> SortedMeasures;
		vector<double> Measures;
		// 3. 35 ms okno na lewo wzgledem probek o numerach wzietych z wektora qrs_lewo
	//    fs = 360 Hz --> ile probek przypada na 35 ms??
	//    czyli bierzemy pod uwage 13 probek, tzn. TransformedECGBaseline(qrs_lewo-13) : TransformedECGBaseline(qrs_lewo-1)
	//    TO ZAWSZE BEDZIE TAKIE SAMO OKNO
		for (int j=13; j>0; --j){
			while (index-j>0){
				SortedMeasures.push_back(ECGBaselineData.at(index-j));
				Measures.push_back(ECGBaselineData.at(index-j));
			}
		}
		// 4. w tym zakresie (13 probek) na ORYGINALNYM ECGBaselineData robimy po kolei:
	//    a) liczymy mediane WARTOSCI tych 13 probek ECGBaselineData 
	//    b) odejmujemy mediane od sygnalu
	//    c) liczymy wartosc bezwzgledna tego sygnalu ktory dostalismy w b) --> abs(costam(costam))
	//    d) robimy PT przy Rv = 0.005
	//    e) w kaødym oknie szukamy minimum i to sa punkty QRS_ONSET i je trzeba wspisac do wektora (jako numery probek im odpowiadajacych)
		sort(SortedMeasures.begin(), SortedMeasures.end());
		double median = SortedMeasures.at(6);
		double min = 4;
		int min_index = 0;
		for (int j=0; j<Measures.size(); ++j) {
			Measures[j] = atan(abs(Measures[j]-median)/0.005);
			if (Measures[j] < min) {
				min = Measures[j];
				min_index = j;
			}
		}
		ResultIndexVector.push_back(min_index);
	}
	qrs_onset_index_vector = ResultIndexVector;
}

void Waves::ustaw_qrs_end(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency){
	vector<double> ECGBaselineDataTP;
	// to jest wektor zawieracjacy indexy punktow qrs_onset w ecgBaselineData
	vector<int> ResultIndexVector;
	double Rv=0.001;

	// 1. transformacja wskazowa przy Rv=0.001 calego przefiltrowanego sygnalu, czyli wszystkich elementow wektora ECGBaselineData
	for (int i=0; i<ECGBaselineData.size(); ++i){
		ECGBaselineDataTP.push_back(atan(ECGBaselineData.at(i)/Rv));
	}
		
	for (int i=RPeaksData.size()-1; i>=0; --i){ // tak bylo dla qrs_onset, ale chyba przeszukiwanie od konca nie szkodzi
	//for (int i=0; i<=(RPeaksData.size()-1); ++i){ // i to jest za kaødym razem element RPeaksData, czyli nr piku R!!
		double amp = 1;
		int index = 0;
		while (amp<=0.25*3.1415){
			for (int j = i; j>=0; ++j){ // zmiana z --j, poniewaz idziemy w prawo od piku R
				amp = ECGBaselineDataTP.at(j);  // wpisujemy amplitude tego punktu (qrs+) do EBDTP w miejsce j.
				index = j;
			}
		}
		vector<double> SortedMeasures;
		vector<double> Measures;
		// 3. 35 ms okno na lewo wzgledem probek o numerach wzietych z wektora qrs_lewo
		//    czyli bierzemy pod uwage 13 probek, tzn. TransformedECGBaseline(qrs_lewo-13) : TransformedECGBaseline(qrs_lewo-1)
		// TERAZ TRZEBA NA PRAWO SZUKAC
		// for (int j=13; j>0; --j){
		for (int j=0; j<13; ++j){
			//while (index-j>0){ // tak bylo dla qrs_onset
			while (index+j<RPeaksData.size()){ // ZABEZPIECZENIE !!
				SortedMeasures.push_back(ECGBaselineData.at(index+j)); // bylo -j
				Measures.push_back(ECGBaselineData.at(index+j)); //bylo -j
			}
		}
		// 4. w tym zakresie (13 probek) na ORYGINALNYM ECGBaselineData robimy po kolei:
	//    a) liczymy mediane WARTOSCI tych 13 probek ECGBaselineData 
	//    b) odejmujemy mediane od sygnalu
	//    c) liczymy wartosc bezwzgledna tego sygnalu ktory dostalismy w b) --> abs(costam(costam))
	//    d) robimy PT przy Rv = 0.005
	//    e) w kaødym oknie szukamy minimum i to sa punkty QRS_ONSET i je trzeba wspisac do wektora (jako numery probek im odpowiadajacych)
		sort(SortedMeasures.begin(), SortedMeasures.end());
		double median = SortedMeasures.at(6);
		double min = 4;
		int min_index = 0;
		for (int j=0; j<Measures.size(); ++j) { // znowu mozemy uzyc j
			Measures[j] = atan(abs(Measures[j]-median)/0.005);
			if (Measures[j] < min) {
				min = Measures[j];
				min_index = j;
			}
		}
		ResultIndexVector.push_back(min_index);
	}
	qrs_end_index_vector = ResultIndexVector;
}

double Waves::get_derivative(vector<double> d){
	sort(d.begin(), d.end());
	if (d.size() % 2 == 0) {
		return (d[d.size()/2-1] + d[d.size()/2])/2;
	} else {
		return d[d.size()-1];
	}
}

void Waves::ustaw_p_onset(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency){
	vector<int> p_onset_index;
	for (int i=qrs_onset_index_vector.size()-1; i>=0; --i){
		int first_right_peak_index, immiediate_left_peak_index;
		int j=0;
		// idziemy od poczatku RPeaksData dopoki nie dojdziemy do konca (pierwszy warunek) lub
		// nie znajdziemy pierwszego elementu (indexu) ktory jest wiekszy od danego qrs_onset punktu
		while (j<RPeaksData.size() || RPeaksData[j] < qrs_onset_index_vector[i])
			++j;
		first_right_peak_index = RPeaksData[j];
		immiediate_left_peak_index = RPeaksData[j-1]; // ZMIANA!!!!!    nie bylo zadeklarowane, ale czy moze byc j-1??
		int windows_width = ceil(0.25*(first_right_peak_index-immiediate_left_peak_index));
		vector<double> window_signal(ECGBaselineData.begin() + (qrs_onset_index_vector[i]-windows_width), ECGBaselineData.begin() - qrs_onset_index_vector[i]);
		double median = get_vector_median(window_signal);
		double max = -4;
		int max_index = 0;
		for (int j=0;j<window_signal.size();++j) {
			window_signal[j] = atan((window_signal[j]-median)/0.003);
			if (max < window_signal[j]){
				max = window_signal[j];
				max_index = j;
			}
		}
		vector<double> left_window_in_a_window (window_signal.begin() + max_index - 6, window_signal.begin() + max_index);
		int index = left_window_in_a_window.size()-1; 
		
		//while (j>=0) {
			// tu policz pochodna z left_window_in_a_window[j]
			//double derivative = 1.231;
			//if (derivative < 0)
			//	break;
		//}

		double derivative = get_derivative(left_window_in_a_window);
		double dt = 4;
		int dt_index = 0;
		for (int j=0; j<left_window_in_a_window.size(); ++j) {
			left_window_in_a_window[j] = atan(abs(left_window_in_a_window[j]-derivative)/0.005);
			if (left_window_in_a_window[j] < dt) {
				dt = left_window_in_a_window[j];
				dt_index = j;
			}
		}

		p_onset_index.push_back(dt_index); // EWENTUALNIE: p_onset_index.push_back(j); !!!
	}
	p_onset_index_vector = p_onset_index;
}

void Waves::ustaw_p_end(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency){
	vector<int> p_end_index;
	for (int i=qrs_onset_index_vector.size()-1; i>=0; --i){
		int first_right_peak_index, immiediate_left_peak_index;
		int j=0;
		while (j<RPeaksData.size() || RPeaksData[j] < qrs_onset_index_vector[i])
			++j;
		first_right_peak_index = RPeaksData[j];
		immiediate_left_peak_index = RPeaksData[j-1];
		int windows_width = ceil(0.25*(first_right_peak_index-immiediate_left_peak_index));
		vector<double> window_signal(ECGBaselineData.begin() + (qrs_onset_index_vector[i]-windows_width), ECGBaselineData.begin() - qrs_onset_index_vector[i]);
		double median = get_vector_median(window_signal);
		double max = -4;
		int max_index = 0;
		for (int j=0;j<window_signal.size();++j) {
			window_signal[j] = atan((window_signal[j]-median)/0.003);
			if (max < window_signal[j]){
				max = window_signal[j];
				max_index = j;
			}
		}

		vector<double> right_window_in_a_window (window_signal.begin() + max_index, window_signal.begin() + max_index + 6);
		int index = right_window_in_a_window.size()-1;
		double derivative = get_derivative(right_window_in_a_window);
		double dt = 4;
		int dt_index = 0;
		for (int j=0; j<right_window_in_a_window.size(); ++j) {
			right_window_in_a_window[j] = atan(abs(right_window_in_a_window[j]-derivative)/0.005);
			if (right_window_in_a_window[j] < dt) {
				dt = right_window_in_a_window[j];
				dt_index = j;
			}
		}
		p_end_index.push_back(dt_index);
	}
	p_end_index_vector = p_end_index;
}

void Waves::ustaw_t_onset(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency){
	vector<int> t_onset_index;
	//for (int i=qrs_onset_index_vector.size()-1; i>=0; --i){ // zmienic na qrs end
		for (int i=qrs_end_index_vector.size()-1; i>=0; --i){
		int first_right_peak_index, immiediate_left_peak_index; // Pierwszy R peak jaki znajdujemy przeszukujπc
																// oraz poprzedzajacy --> zmienic na nastepny
		int j=0;
		// idziemy od poczatku RPeaksData dopoki nie dojdziemy do konca (pierwszy warunek) lub
		// nie znajdziemy pierwszego elementu (indexu) ktory jest wiekszy od danego qrs_end punktu
		while (j<RPeaksData.size() || RPeaksData[j] < qrs_end_index_vector[i])
			++j;
		first_right_peak_index = RPeaksData[j+1]; //zmiana z [j] w stosunku do set_p_onset
		immiediate_left_peak_index = RPeaksData[j];
		int windows_width = ceil(0.25*(first_right_peak_index-immiediate_left_peak_index));
		vector<double> window_signal(ECGBaselineData.begin() + (qrs_end_index_vector[i]), ECGBaselineData.begin() + qrs_end_index_vector[i] + windows_width);
		double median = get_vector_median(window_signal);
		double max = -4;
		int max_index = 0;
		for (int j=0;j<window_signal.size();++j) { // ZNAJDUJEMY INDEX MAKSIMUM
			window_signal[j] = atan((window_signal[j]-median)/0.1); // tu wystarczy 0.1
			if (max < window_signal[j]){
				max = window_signal[j];
				max_index = j;
			}
		}
		// ODTAD SZUKAMY W NOWYM OKNIE

		vector<double> left_window_in_a_window (window_signal.begin() + max_index - 9, window_signal.begin() + max_index); // szerokosc 9 probek
		int index = left_window_in_a_window.size()-1;
		double derivative = get_derivative(left_window_in_a_window);
		double dt = 4;
		int dt_index = 0;
		for (int j=0; j<left_window_in_a_window.size(); ++j) {
			left_window_in_a_window[j] = atan(abs(left_window_in_a_window[j]-derivative)/0.1);
			if (left_window_in_a_window[j] < dt) {
				dt = left_window_in_a_window[j];
				dt_index = j;
			}
		}
		t_onset_index.push_back(dt_index);
	}
	t_onset_index_vector = t_onset_index;
}

void Waves::ustaw_t_end(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency){
	vector<int> t_end_index;
	//for (int i=qrs_onset_index_vector.size()-1; i>=0; --i){ // zmienic na qrs end
		for (int i=qrs_end_index_vector.size()-1; i>=0; --i){
		int first_right_peak_index, immiediate_left_peak_index; // Pierwszy R peak jaki znajdujemy przeszukujπc
																// oraz poprzedzajacy --> zmienic na nastepny
		int j=0;
		// idziemy od poczatku RPeaksData dopoki nie dojdziemy do konca (pierwszy warunek) lub
		// nie znajdziemy pierwszego elementu (indexu) ktory jest wiekszy od danego qrs_end punktu
		while (j<RPeaksData.size() || RPeaksData[j] < qrs_end_index_vector[i])
			++j;
		first_right_peak_index = RPeaksData[j+1]; //zmiana z [j] w stosunku do set_p_onset
		immiediate_left_peak_index = RPeaksData[j];
		int windows_width = ceil(0.25*(first_right_peak_index-immiediate_left_peak_index));
		vector<double> window_signal(ECGBaselineData.begin() + (qrs_end_index_vector[i]), ECGBaselineData.begin() + qrs_end_index_vector[i] + windows_width);
		double median = get_vector_median(window_signal);
		double max = -4;
		int max_index = 0;
		for (int j=0;j<window_signal.size();++j) { // ZNAJDUJEMY INDEX MAKSIMUM
			window_signal[j] = atan((window_signal[j]-median)/0.1); // tu wystarczy 0.1
			if (max < window_signal[j]){
				max = window_signal[j];
				max_index = j;
			}
		}

		vector<double> right_window_in_a_window (window_signal.begin() + max_index, window_signal.begin() + max_index + 9);
		int index = right_window_in_a_window.size()-1;
		
		double derivative = get_derivative(right_window_in_a_window);
		double dt = 4;
		int dt_index = 0;
		for (int j=0; j<right_window_in_a_window.size(); ++j) {
			right_window_in_a_window[j] = atan(abs(right_window_in_a_window[j]-derivative)/0.1);
			if (right_window_in_a_window[j] < dt) {
				dt = right_window_in_a_window[j];
				dt_index = j;
			}
		}

		t_end_index.push_back(dt_index);
	}
	t_end_index_vector = t_end_index;
}