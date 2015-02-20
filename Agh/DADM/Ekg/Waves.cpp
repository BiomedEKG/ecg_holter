#include <Waves.h>
#include <cmath>
#include <algorithm>
#define PI 3.14
WavesResult* Waves::compute(ResultKeeper *rkp) {

	vector<double> ECGBaselineData;
	vector<unsigned int> RPeaksData;

	ECGBaselineData = rkp->getECGBaseline()->getFilteredSignal(); /// Przypisanie danych ECGBaseline na ktorych beda wykonywane obliczenia
	RPeaksData = rkp->getRPeaks()->getRPeaks();/// Przypisanie danych RPeaks na ktorych beda wykonywane obliczenia
	int sampling_frequency = 360;
	//ustaw_qrs_onset(ECGBaselineData, RPeaksData, sampling_frequency);
	ustaw_qrs_end(ECGBaselineData, RPeaksData, sampling_frequency);
	ustaw_p_onset(ECGBaselineData, RPeaksData, sampling_frequency);
	ustaw_p_end(ECGBaselineData, RPeaksData, sampling_frequency);
	ustaw_t_onset(ECGBaselineData, RPeaksData, sampling_frequency);
	ustaw_t_end(ECGBaselineData, RPeaksData, sampling_frequency);
	//double get_vector_median(vector<double> v); // skoro jest wywolywane w dalszych metodach, to tutaj chyba nie musi
	//double get_derivative(vector<double> d); 

	WavesResult  ResultHolder = WavesResult();///stworz obiekt rezultatu
	ResultHolder.SetWavesResultData(WavesData);////Przypisz dane z klasy liczacej do danych klasy z klasy rezultatu

	return ResultHolder.getResult();// Zwroc odpowiedni wska?nik
}

double Waves::get_vector_median(vector<double> v) {
	sort(v.begin(), v.end());
	if (v.size() % 2 == 0) {
		return (v[v.size()/2-1] + v[v.size()/2])/2;
	} else {
		return v[(v.size()-1)/2];
	}
}
void Waves::ustaw_qrs_onset(vector<double> ECGBaselineData, vector<unsigned int> RPeaksData, int sampling_frequency){
	vector<double> ECGBaselineDataTP;
	//double Rv = 00.1; ZMIANA
	double Rv = 0.001;
	vector<int> qrsLeft;
	vector< int> qrsOnSet;

	for (int i=0, size = ECGBaselineData.size()-1; i<size; ++i){
		ECGBaselineDataTP.push_back(atan(ECGBaselineData.at(i)/Rv));
	}

	for(int i = 0; i < RPeaksData.size()-1; i++) { // tu moze byc cos zle
		int starIndex = RPeaksData[i];
		for(int j = starIndex; j >= 0; j--) {
			if(ECGBaselineDataTP[j] < (0.125*PI)) { // ZMIANA by³o 0.25*PI, powinno byc 0.125*PI
				qrsLeft.push_back(j);
				break;
			}
		}

	}

	//int windowSize = (sampling_frequency*0.035); ZMIANA
	int windowSize = ceil(sampling_frequency*0.035);

	for(int i = 0, size = qrsLeft.size()-1; i < size; i++) {
		vector<double> window;
		int startIndex = qrsLeft[i];
		if(startIndex - windowSize >= 0){
			for(int j = startIndex; j >= startIndex-windowSize; j--) {
				window.push_back(j);
			}
		}
		vector<double>partOfSignal;
		for(int i = window.size()-1; i >= 0; i--) { //czy mozna tutaj wykorzystac i?
			partOfSignal.push_back(ECGBaselineData[window[i]]);
		}

		double median = get_vector_median(partOfSignal);
		vector<double> afterMedian;
		for(int i = 0, size = ECGBaselineData.size(); i < size; i++){
			afterMedian.push_back(ECGBaselineData[i] - median);
		}

		for(int i = 0, size = afterMedian.size()-1; i < size; i++) {
			afterMedian[i] = abs(afterMedian[i]);
		}

		//int Rv2 = 0.05; ZMIANA
		double Rv2 = 0.005;
		vector<double> resultVector;
		for (int i=0, size = afterMedian.size()-1; i < size; ++i){
			resultVector.push_back(atan(afterMedian.at(i)/Rv2));
		}

		//double val = std::min_element(resultVector[startIndex-windowSize], resultVector[startIndex]);
		int temp;
		//Iscie murzynskie poszukiwanie iteratora o najmniejszej wartosci próbki ;p
		for(int i = startIndex-windowSize; i < startIndex; i++) {
			if(resultVector[i] < resultVector[i+1]) {
				temp = i;
			}else {
				temp = i+1;
			}

		}
		qrsOnSet.push_back(temp);
	}

	WavesData["QRS_ONSET"] = qrsOnSet;

}


void Waves::ustaw_qrs_end(vector<double> ECGBaselineData, vector<unsigned int> RPeaksData, int sampling_frequency) {
	vector<double> ECGBaselineDataTP;
	double Rv = 0.001;
	vector<int> qrsRight;
	vector< int> qrsEnd;

	for (int i=0, size = ECGBaselineData.size()-1; i<size; ++i){
		ECGBaselineDataTP.push_back(atan(ECGBaselineData.at(i)/Rv));
	}

	for(int i = 0, size = RPeaksData.size()-1; i < size; i++) {
		int starIndex = RPeaksData[i];
		for(int j = starIndex, size2 = ECGBaselineDataTP.size(); j < size2; j++) {
			if(ECGBaselineDataTP[j] < (0.125*PI)) { //ZMIANA bylo 0.25*PI
				qrsRight.push_back(j);
				break;
			}
		}
	}
	//int windowSize = (sampling_frequency*0.035); ZMIANA
	int windowSize = ceil(sampling_frequency*0.035);
	for(int ix = 0, size = qrsRight.size()-1; ix < size; ix++) {
		vector<double> window;
		int startIndex = qrsRight[ix];

		for(int j = startIndex; j <= startIndex+windowSize; j++) {
			window.push_back(j);

		}
		vector<double>partOfSignal;
		for(int i = 0; i < windowSize; i++) {
			partOfSignal.push_back(ECGBaselineData[window[i]]);
		}

		double median = get_vector_median(partOfSignal);
		vector<double> afterMedian;
		for(int i = 0, size = ECGBaselineData.size()-1; i < size; i++){
			afterMedian.push_back(ECGBaselineData[i] - median);
		}

		for(int i = 0, size = afterMedian.size()-1; i < size; i++) {
			afterMedian[i] = abs(afterMedian[i]);
		}

		int Rv2 = 0.005;
		vector<double> resultVector;
		for (int i=0, size = afterMedian.size()-1; i < size; ++i){
			resultVector.push_back(atan(afterMedian.at(i)/Rv2));
		}

		//double val = std::min_element(resultVector[startIndex-windowSize], resultVector[startIndex]);
		int temp;
		//Iscie murzynskie poszukiwanie iteratora o najmniejszej wartosci próbki ;p
		for(int i = startIndex-windowSize; i < startIndex-1; i++) {
			if(resultVector[i] < resultVector[i+1]) {
				temp = i;
			}else {
				temp = i+1;
			}

		}
		qrsEnd.push_back(temp);
	}

	WavesData["QRS_END"] = qrsEnd;

}



double Waves::get_derivative(vector<double> d){
	sort(d.begin(), d.end());
	if (d.size() % 2 == 0) {
		return (d[d.size()/2-1] + d[d.size()/2])/2;
	} else {
		return d[d.size()-1];
	}
}

void Waves::ustaw_p_onset(vector<double> ECGBaselineData, vector<unsigned int> RPeaksData, int sampling_frequency) {
	float Rv = 0.003;
	vector<int>pOnSet;
	vector<int>qrsOnSet = WavesData["QRS_ONSET"];
	for(int i = 0; i < qrsOnSet.size(); i++) {
		int mainLoopIterator  = i;
		vector<double> Mainwindow;
		int MainlocalMax ;
		int MainsmallWindowSize;
		vector<double>MainderivativeVector;
		int MainmaxValIndex;
		//int MainMaxVal; //dalej uwazam, ze powinno byc double
		double MainMaxVal;
		for(int j = 0; j < RPeaksData.size()-2; j++) {

			vector<double> window;
			int localMax ;
			int smallWindowSize;
			vector<double>derivativeVector;
			int maxValIndex;

			int windowSize = (RPeaksData[j+1] - RPeaksData[j])/4;
			//vector<double> window;
			if(windowSize > qrsOnSet[i]) {
				windowSize = qrsOnSet[i];
			}
			for(int k = qrsOnSet[i]; k > qrsOnSet[i] - windowSize; k--){
				window.push_back(ECGBaselineData[k]);
			}

			std::reverse(window.begin(),window.end());
			double median = get_vector_median(window);
			vector<double> afterMedian;

			for(int j = 0; j < window.size()-1; j++) {
				afterMedian.push_back(window[j] - median);
			}

			for (int i=0, size = window.size()-1; i<size; ++i){
				window.push_back(atan(window.at(i)/Rv));
			}

			localMax = 0;
			for(int i = 0; i < window.size()-2; i++) {
				if(window[i] > window[i+1]) {
					localMax = i;
				}
			}

			smallWindowSize = sampling_frequency * 0.06;
			vector<double> smallWindow;
			for(int j = 0; j < smallWindowSize; j++) {
				smallWindow.push_back(ECGBaselineData[localMax - j]);
			}

			median = get_vector_median(smallWindow);
			vector<double>smallWindowAfterMedian;
			for(int j = 0; j < smallWindowSize; j++) {
				smallWindowAfterMedian.push_back(smallWindow[j] - median);
			}
			double Rv2 = 0.005;
			for(int i=0; i<smallWindowSize; i++) {
				smallWindowAfterMedian[i] = (atan(smallWindowAfterMedian[i]/Rv2));
			}

			for (int i = 0; i < smallWindowSize-1 ; i++){
				derivativeVector.push_back(smallWindowAfterMedian[i+1]-smallWindowAfterMedian[i]);
			}

			//int maxVal = derivativeVector[0]; // naprawde uwazam ze lepiej dac double...
			double maxVal = derivativeVector[0];
			for(int i = 0; i < derivativeVector.size()-2; i++) {
				if(derivativeVector[i] > maxVal) {
					maxVal = derivativeVector[i]; // dodalem ta linijke
					maxValIndex = i;
				}
			}
			//bez paniki, to tylko bardzo brzydki sposob na wyciagniecie zmiennych do zewnetrzengo scopa
			Mainwindow = window;
			MainlocalMax = localMax ;
			MainsmallWindowSize = smallWindowSize;
			MainderivativeVector = derivativeVector;
			MainmaxValIndex = maxValIndex;
			MainMaxVal = maxVal;

		}

		for(int j = MainmaxValIndex; j >= 0; j--) {
			//int index = qrsOnSet[mainLoopIterator]-Mainwindow.size()+MainlocalMax-MainsmallWindowSize+MainMaxVal-j;
			int index = qrsOnSet[mainLoopIterator]-Mainwindow.size()+MainlocalMax-MainsmallWindowSize+MainmaxValIndex-j; // chyba powinno byc MainmaxvalIndex zamiast MainMaxVal
			if(MainderivativeVector[j] < 0 && (index >= 0)){
				//pOnSet.push_back(qrsOnSet[mainLoopIterator]-Mainwindow.size()+MainlocalMax-MainsmallWindowSize+MainMaxVal-j);
				pOnSet.push_back(qrsOnSet[mainLoopIterator]-Mainwindow.size()+MainlocalMax-MainsmallWindowSize+MainmaxValIndex-j); //MainMaxVal --> MainmaxValIndex
				break;
			}
		}

	}
	WavesData["P_ONSET"] = pOnSet;
}




void Waves::ustaw_p_end(vector<double> ECGBaselineData, vector<unsigned int> RPeaksData, int sampling_frequency) {
	float Rv = 0.003;
	vector<int>pEnd;
	vector<int>pOnset = WavesData["P_ONSET"];
	for(int i = 0; i < pOnset.size(); i++) {
		int mainLoopIterator  = i;
		vector<double> Mainwindow;
		int MainlocalMax ;
		int MainsmallWindowSize;
		vector<double>MainderivativeVector;
		int MainminValIndex;
		double MainMinVal; //zmiana z int na double
		for(int j = 0; j < RPeaksData.size()-2; j++) {
			//window.erase(window.begin(), window.end());
			//derivativeVector.erase(window.begin(), window.end());
			vector<double> window;
			int localMax ; //zostaje
			int smallWindowSize;
			vector<double>derivativeVector;
			int minValIndex; //zmiana

			int windowSize = (RPeaksData[j+1] - RPeaksData[j])/4;
			//vector<double> window;
			if(windowSize > pOnset[i]) {
				windowSize = pOnset[i];
			}
			for(int k = pOnset[i]; k > pOnset[i] - windowSize; k--){
				window.push_back(ECGBaselineData[k]);
			}

			std::reverse(window.begin(),window.end());
			double median = get_vector_median(window);
			vector<double> afterMedian;

			for(int j = 0; j < window.size()-1; j++) {
				afterMedian.push_back(window[j] - median);
			}

			for (int i=0, size = window.size()-1; i<size; ++i){
				window.push_back(atan(window.at(i)/Rv));
			}

			localMax = 0;
			for(int i = 0; i < window.size()-2; i++) {
				if(window[i] > window[i+1]) {
					localMax = i;
				}
			}

			smallWindowSize = sampling_frequency * 0.06;
			vector<double> smallWindow;
			for(int j = 0; j < smallWindowSize; j++) {
				smallWindow.push_back(ECGBaselineData[localMax + j]); // ZMIANA z -j bo teraz ustawiamy okno na prawo od maksimum
			}

			median = get_vector_median(smallWindow);
			vector<double>smallWindowAfterMedian;
			for(int j = 0; j < smallWindowSize; j++) {
				smallWindowAfterMedian.push_back(smallWindow[j] - median);
			}
			double Rv2 = 0.005;
			for(int i=0; i<smallWindowSize; i++) {
				smallWindowAfterMedian[i] = (atan(smallWindowAfterMedian[i]/Rv2));
			}

			for (int i = 0; i < smallWindowSize-1 ; i++){
				derivativeVector.push_back(smallWindowAfterMedian[i+1]-smallWindowAfterMedian[i]);
			}

			double minVal = derivativeVector[0]; //zmiana z maxVal i z int na double
			for(int i = 0; i < derivativeVector.size()-2; i++) {
				if(derivativeVector[i] < minVal) { //zmiana kierunku nierownosci
					minValIndex = i;
				}
			}
			//bez paniki, to tylko bardzo brzydki sposob na wyciagniecie zmiennych do zewnetrzengo scopa
			Mainwindow = window;
			MainlocalMax = localMax ;
			MainsmallWindowSize = smallWindowSize;
			MainderivativeVector = derivativeVector;
			MainminValIndex = minValIndex;
			MainMinVal = minVal;

		}

		//for(int j = MainmaxValIndex; j >= 0; j--) { //mielismy maksimum to sie cofalismy teraz szukamy posuwajac sie w prawo
		for(int j = MainminValIndex; j <= MainderivativeVector.size(); j++) {
			int index = pOnset[mainLoopIterator]-Mainwindow.size()+MainlocalMax+j;
			if(MainderivativeVector[j] > 0 && (index <= ECGBaselineData.size())){ // sprawdz prosze czy te warunki maja sens
				pEnd.push_back(pOnset[mainLoopIterator]-Mainwindow.size()+MainlocalMax+j);
				break;
			}
		}

	}
	WavesData["P_END"] = pEnd;
}


void Waves::ustaw_t_onset(vector<double> ECGBaselineData, vector<unsigned int> RPeaksData, int sampling_frequency) {
        float Rv = 0.1;
        vector<int>tOnSet;
        vector<int>qrsEnd = WavesData["QRS_END"];
        for(int i = 0; i < qrsEnd.size(); i++) {
                int mainLoopIterator  = i;
                vector<double> Mainwindow;
                int MainlocalMax ;
                int MainsmallWindowSize;
                vector<double>MainderivativeVector;
                int MainmaxValIndex;
                //int MainMaxVal; //dalej uwazam, ze powinno byc double
                double MainMaxVal;
 
                for(int j = 0; j < RPeaksData.size()-2; j++) {
                        //window.erase(window.begin(), window.end());
                        //derivativeVector.erase(window.begin(), window.end());
                        vector<double> window;
						 vector<double> window2;
                        int localMax ;
                        int smallWindowSize;
                        vector<double>derivativeVector;
                        int maxValIndex;
     
                                int windowSize = (RPeaksData[j+1] - RPeaksData[j])/4;
                                //if(qrsEnd[i] + windowSize > ECGBaselineData.size()){ //chyba o takie zabezpieczenie chodzi
                                //        windowSize = ECGBaselineData.size()-1 - qrsEnd[i];
                                //}
								if (windowSize > qrsEnd[i])
								{
									windowSize = qrsEnd[i];
								}

                                for(int k = qrsEnd[i]; k < qrsEnd[i] + windowSize; k++){ // dobrze iteruje?
                                        window.push_back(ECGBaselineData[k]);
                                }
     
                                //std::reverse(window.begin(),window.end()); // tu nie trzeba odwracac chyba
                                double median = get_vector_median(window);
                                vector<double> afterMedian;
     
                                for(int j = 0; j < window.size()-1; j++) {
                                        afterMedian.push_back(window[j] - median);
                                }
     
                                for (int i=0, size = window.size()-1; i<size; ++i){
                                        window2.push_back(atan(afterMedian[i]/Rv));
                                }
     
                                localMax = 0;
                                for(int i = 0; i < window.size()-2; i++) {
                                        if(window2[i] > window2[i+1]) {
                                                localMax = i;
                                        }
                                }
 
                                smallWindowSize = sampling_frequency * 0.1;
                                vector<double> smallWindow;
                                for(int j = 0; j < smallWindowSize ; j++) {
									if(j >= localMax) break;
                                        smallWindow.push_back(ECGBaselineData[localMax - j]); //push_front??
                                }
                                std::reverse(smallWindow.begin(),smallWindow.end()); // to sobie ja dopisalem

								if(smallWindow.size() != smallWindowSize){   //takie szpachlowanie niezgodnosci rozmiarów 8) 
									smallWindowSize = smallWindow.size() ;
								} 
 
                                median = get_vector_median(smallWindow);
                                vector<double>smallWindowAfterMedian;
                                for(int j = 0; j < smallWindowSize; j++) {

                                        smallWindowAfterMedian.push_back(smallWindow[j] - median);
                                }
                                double Rv2 = 0.1;
                                for(int i=0; i<smallWindowSize; i++) {
                                        smallWindowAfterMedian[i] = (atan(smallWindowAfterMedian[i]/Rv2));
                                }
                           
                                for (int i = 0; i < smallWindowSize-1 ; i++){
                                        derivativeVector.push_back(smallWindowAfterMedian[i+1]-smallWindowAfterMedian[i]);
                                }
     
                                //int maxVal = derivativeVector[0]; // naprawde uwazam ze lepiej dac double...
                                int maxVal = derivativeVector[0];
                                for(int i = 0; i < derivativeVector.size()-2; i++) {
                                        if(derivativeVector[i] > maxVal) {
                                                maxVal = derivativeVector[i]; // dodalem ta linijke
                                                maxValIndex = i;
                                        }
                                }
                                //bez paniki, to tylko bardzo brzydki sposob na wyciagniecie zmiennych do zewnetrzengo scopa
                                Mainwindow = window;
                                MainlocalMax = localMax ;
                                MainsmallWindowSize = smallWindowSize;
                                MainderivativeVector = derivativeVector;
                                MainmaxValIndex = maxValIndex;
                                MainMaxVal = maxVal;
     
                        }
     
                        for(int j = MainmaxValIndex; j >= 0; j--) {
                                //int index = qrsOnSet[mainLoopIterator]-Mainwindow.size()+MainlocalMax-MainsmallWindowSize+MainmaxValIndex-j; // chyba powinno byc MainmaxvalIndex zamiast MainMaxVal
                                int index = qrsEnd[mainLoopIterator]+MainlocalMax-MainsmallWindowSize+j;
                                if(MainderivativeVector[j] < 0 && (index >= 0)){
                                        tOnSet.push_back(qrsEnd[mainLoopIterator]+MainlocalMax-MainsmallWindowSize+j); //tak mi wynika z rysunku
                                        break;
                                }
                        }
     
                }
                WavesData["T_ONSET"] = tOnSet;
        }


void Waves::ustaw_t_end(vector<double> ECGBaselineData, vector<unsigned int> RPeaksData, int sampling_frequency) {
        float Rv = 0.1;
        vector<int>tEnd;
        vector<int>tPeak;
        vector<int>qrsEnd = WavesData["T_ONSET"]; // znow zmienilem swatkowi bo wredny jestem ;p
        for(int i = 0; i < qrsEnd.size(); i++) {
                int mainLoopIterator  = i;
                vector<double> Mainwindow;
                int MainlocalMax;
                int MainsmallWindowSize;
                vector<double>MainderivativeVector;
                int MainminValIndex;
                //double MainMaxVal;
   
                for(int j = 0; j < RPeaksData.size()-2; j++) {
                        //window.erase(window.begin(), window.end());
                        //derivativeVector.erase(window.begin(), window.end());
                        vector<double> window;
                        vector<double> window2;
                        int localMax ;
                        int smallWindowSize;
                        vector<double>derivativeVector;
                        int maxValIndex;
       
                        int windowSize = (RPeaksData[j+1] - RPeaksData[j])/4;
 
                        if (windowSize > qrsEnd[i]){ //(tak samo jest w ustaw_t_onset, w razie czego tam tez trzeba zmienic)
                                windowSize = qrsEnd[i];  //ten warunek nie ma sensu, bo okno zaczepiamy ZA qrsEnd[i]
                        }                                                        //trzeba raczej sprawdzic, czy nie pobiera danych spoza gornego zakresu
   
                        //PODAJE MOJ WARUNEK:
                        if(qrsEnd[i] + windowSize > ECGBaselineData.size()){
                                windowSize = ECGBaselineData.size()-1 - qrsEnd[i];
                        }
 
                        for(int k = qrsEnd[i]; k < qrsEnd[i] + windowSize; k++){
                                window.push_back(ECGBaselineData[k]);
                        }
       
                        double median = get_vector_median(window);
                        vector<double> afterMedian;
       
                        for(int k = 0; k < window.size()-1; k++) {
                                afterMedian.push_back(window[k] - median);
                        }
       
                        for (int k=0, size = window.size()-1; k<size; ++k){
                                window2.push_back(atan(afterMedian[k]/Rv));
                        }
       
                        //localMax = 0;  
                        //for(int k = 0; k < window.size()-2; k++) { // czy to na pewno dobrze szuka maksimum??
                        //      if(window2[k] > window2[k+1]) { //sygnal rosnie a pozniej opada, tam gdzie opada praktycznie wszedzie bedzie spelniony warunek
                        //              localMax = k; //bo probka i+1 bedzie z reguly mniejsza niz poprzednia (i) (bo sygnal opada)
                        //      } //i tym sposobem bedzie oznaczal jako maksimum probke z prawego konca okna, tak mi sie wydaje
                        //} //zmienilem na k dla porzadku ale problem pozostal
                        localMax = 0;  
                        for(int k = 0; k < window.size()-1; k++) { // co myslisz o takim szukaniu maksimum??
                                if(window2[localMax] < window2[k]) {
                                        localMax = k;
                                }
                        }
   
                        smallWindowSize = sampling_frequency * 0.1;
                        vector<double> smallWindow;
 
                        //for(int k = 0; k < smallWindowSize ; k++) {
                        //      if(k >= localMax) break;
                        //      smallWindow.push_back(ECGBaselineData[localMax - k]); //nie mozna tak zrobic... w kazdej iteracji bedzie tu wchodzic ten sam fragment sygnalu...
                        //} // ani localMax ani k nie zawieraja informacji o polozeniu w sygnale tylko wewnatrz window (localMax) i smallWindow (k)
                       
                        for(int k = localMax; k < localMax+smallWindowSize; k++) { //teraz powonno byc OK
                                smallWindow.push_back(ECGBaselineData[qrsEnd[i]+k]);
                        }
                       
                        //std::reverse(smallWindow.begin(),smallWindow.end()); //teraz nie trzeba obracac
                        if(smallWindow.size() != smallWindowSize){   //takie szpachlowanie niezgodnosci rozmiarów 8)
                                smallWindowSize = smallWindow.size() ;
                        }
   
                        median = get_vector_median(smallWindow);
                        vector<double>smallWindowAfterMedian;
                        for(int k = 0; k < smallWindowSize; k++) {
                                smallWindowAfterMedian.push_back(smallWindow[k] - median);
                        }
                        double Rv2 = 0.1;
                        for(int k=0; k<smallWindowSize; k++) {
                                smallWindowAfterMedian[k] = (atan(smallWindowAfterMedian[k]/Rv2));
                        }
                             
                        for (int k = 0; k < smallWindowSize-1 ; k++){
                                derivativeVector.push_back(smallWindowAfterMedian[k+1]-smallWindowAfterMedian[k]);
                        }
                        //UWAGA TERAZ TRZEBA SZUKAC MINIMUM
 
                        //int maxVal = derivativeVector[0]; // naprawde uwazam ze lepiej dac double...
                        //int maxVal = derivativeVector[0];
                        //for(int i = 0; i < derivativeVector.size()-2; i++) {
                        //      if(derivativeVector[i] > maxVal) {
                        //              maxVal = derivativeVector[i]; // dodalem ta linijke
                        //              maxValIndex = i;
                        //      }
                        //}
                       
                        // O TAK TO ROZWIAZALEM:
                        int minValIndex = 0;  
                        for(int k = 0; k < derivativeVector.size()-1; k++) { // gdyby sie wypierdalalo tu to mozna sprobowac zmienic -1 na -2
                                if(derivativeVector[minValIndex] > derivativeVector[k]) {
                                        minValIndex = k;
                                }
                        }
 
                        //bez paniki, to tylko bardzo brzydki sposob na wyciagniecie zmiennych do zewnetrzengo scopa
                        Mainwindow = window;
                        MainlocalMax = localMax; // nie ma info o polozeniu w sygnale
                        MainsmallWindowSize = smallWindowSize;
                        MainderivativeVector = derivativeVector;
                        MainminValIndex = minValIndex; //nie ma info o polozeniu w sygnale
                        //MainMaxVal = maxVal;
                }
                               
                for(int j = MainminValIndex; j <= MainderivativeVector.size(); j++) {
                        int index = qrsEnd[mainLoopIterator]+MainlocalMax+MainminValIndex+j;
                        if(MainderivativeVector[j] > 0 && (index <= ECGBaselineData.size())){
                                tEnd.push_back(qrsEnd[mainLoopIterator]+MainlocalMax+MainminValIndex+j);
                                break;
 
                        }
                }
                tPeak.push_back(qrsEnd[mainLoopIterator]+MainlocalMax);
        }
        WavesData["T_END"] = tEnd;
        WavesData["T_PEAK"] = tPeak;
}