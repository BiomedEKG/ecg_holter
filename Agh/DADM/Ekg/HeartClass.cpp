#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>
#include "HeartClass.h"
#include "HeartClassResult.h"

using namespace std;


// Mo¿e nie umiem pisaæ kodu, ale Visual nie rozpoznaje funkcji round. Dlatego mamy swoj¹
double round( double fValue )
{
    return fValue < 0 ? ceil( fValue - 0.5 )
        : floor( fValue + 0.5 );
}


// Liczenie pola QRSa
double HeartClass::ComplexArea(vector<double>* tempArea){

	double area = 0;
	
	for(unsigned int j = 0; j < tempArea->size(); j++){
		
		if(j > 1){
			
			area = area + abs(tempArea->at(j) - tempArea->at(j-1));
		}
	}		
    return area;
}


// Wpisanie wyników z ECG i Waves do osobnych zmiennych
HeartClass::HeartClass(ResultKeeper* rkp){

	// Tutaj tylko wsadzamy to co da³ Waves i ECG do zmiennych. Nic wiêcej z nimi nie robimy. Dopiero póŸniej pracujemy na tych zmiennych
	map <string, vector<int>> wavesData = rkp->getWaves()->GetWavesResultData();
	this->qrsEnd = wavesData["QRS_END"];
	this->qrsOnset = wavesData["QRS_ONSET"];
	this->signalFromEcg = rkp->getECGBaseline()->getFilteredSignal()

	vector<double> tempVector (this->qrsEnd.size(), 0);
	this->artifactsClass = tempVector;
}


// Utworzenie mapy, w której kluczem jest numer QRSa, a wartoœciami wektory amplitud zespo³ów
// Ca³oœæ jest przekomplikowana z powodu pustych wartoœci wektorów i qrsEnd, które wystêpuj¹ wczeœniej ni¿ qrsOnset -.-
// No i dochodzi jeszcze fakt, ¿e musimy mieæ QRSy po kolei, czyli te z³e te¿ musimy uznawaæ za wyniki wrrrrr
void HeartClass::InputPrepare(){

	unsigned int signalBegin = 0;
	unsigned int signalEnd = 0; 
	unsigned int tempSignalEnd;
	vector<double>::iterator itArtifacts;
	for(unsigned int i = 0; i < this->qrsEnd.size(); i++){
		
		signalBegin = (unsigned int) this->qrsOnset.at(i);
		signalEnd = (unsigned int) this->qrsEnd.at(i);

		// Pozbycie siê QRSów reprezentowanych przez mniej ni¿ 8 próbek, pustych i gdy End jest przed Onset....
		if(((signalEnd - signalBegin) < 9) || (this->qrsOnset.at(i) == NULL) || (signalEnd < signalBegin)){

			// Bezsensowne wyniki zerujemy. Nie mo¿emy usuwaæ, bo zmienialibyœmy numery QRSów (kolejnoœæ ich wyst¹pienia, co znowu
			// bruŸdzi³o by innym modu³om ni¿ej... Trzeba zerowaæ. Oprócz tego zapisujemy te z³e QRSy jako artefakty, do wektorów, które
			// bêd¹ do³¹czone do wyników
			itArtifacts = this->artifactsClass.begin() + i;
			this->artifactsClass.insert(itArtifacts, 3);
			this->artifactsClass.erase(this->artifactsClass.begin() + i + 1);
			this->artifactsForClassification.push_back(this->qrsOnset.at(i));
			this->artifactsForClassification.push_back(this->qrsEnd.at(i));
			this->qrsEnd.at(i) = 0;
			this->qrsOnset.at(i) = 0;
		} else{

			// Trzeba utworzyæ dodatkow¹ zmienna, która bêdzie zapisywaæ numery dobrych QRSów
			this->goodQrsNumber.push_back(i);
		}
		
		// Jeœli qrsEnd wystêpuje wczeœniej ni¿ qrsOnset, to musimy zamieniæ wartoœci miejscami, inaczej póŸniej zapisuj¹c próbki
		// ka¿dego qrsa w mapie signalMap, mapa by³aby krótsza, poniewa¿ nie wy³apywa³aby tych qrsów, w których w³asnie qrsEnd
		// jest wczeœniej ni¿ Onset. Wszystko sprowadza siê do tego, ¿e musimy przejœæ przez wszystkie QRSy. Gdybyœmy je pomijali
		// to mówi¹c o QRSie nr 30 moglibyœmy mówiæ tak naprawdê o QRSie np. 78
		if(signalBegin > signalEnd){

			tempSignalEnd = signalEnd;
			signalEnd = signalBegin;
			signalBegin = tempSignalEnd;
		}

		// Tutaj zapisujemy do naszej mapy, gdzie kluczem jest numer QRSa, a wartoœciami wektory amplitud próbek, które go opisuj¹.
		// Dziêki wczeœniejszym operacjom, nasza mapa nie ma kluczy po kolei, czyli nie ma 1, 2, 3, 4, a tylko takie, które odpowiadaj¹
		// dobrym QRSom, czyli kolejne klucze mog¹ wygl¹daæ tak: 5, 18, 29, 45 itd.
		for(unsigned int j = 0; signalBegin < signalEnd+1; signalBegin++){
			
			if((this->qrsOnset.at(i) != 0) && (this->qrsEnd.at(i) != 0)){

				this->signalMap[i].push_back(this->signalFromEcg.at(signalBegin));
			} 
		}
	}
}


// Wyliczanie wartoœci i numeru próbki max i min dla danego QRSa, z czego min wystêpuje zawsze po max
void HeartClass::Amplitudes(){

	vector<double> temp;
	map<int, vector<double>>::iterator itMap;
	vector<double>::iterator itArtifacts;

	// Idziemy tylko po dobrych QRSach. Ich numery zapisane s¹ w goodQrsNumber
	for(unsigned int i = 0; i < this->goodQrsNumber.size(); i++){
		
		// Tu do tempa wpisujemy wartoœci z mapy, czyli amplitudy wszystkich próbek, przypadaj¹cych na dany QRS
		temp = this->signalMap[this->goodQrsNumber.at(i)];	
		
		vector<double>::iterator it = max_element(temp.begin(), temp.end());
		double maxAmplitude = *it;
		unsigned int maxAmplitudeSample = distance(temp.begin(), it);

		//Wyszukiwanie minimum ktore jest zawsze po maksimum
		vector<double>::iterator itMin = min_element(it, temp.end());
		double minAmplitude = *itMin;
		unsigned int  minAmplitudeSample =  maxAmplitudeSample + distance(it, itMin);

		// QRSy, których minimum jest oddalone o mniej ni¿ 2 próbki od max i QRSy, których ostatni¹ próbk¹ jest 
		// znalezione minimum oraz te, które z lewej strony max maj¹ 0 próbek, równie¿ s¹ artefaktami. Znów musimy 
		// wpisaæ te z³e QRSy do dopowiednich elementów i dodatkowo usun¹æ te QRSy z mapy. Dziêki temu mamy teraz 
		// w mapie tylko poprawnie wykryte QRSy.
		// Co prawda QRSy zapisane w artifactsClass i artifactsForClassification nie s¹ po kolei, ale mo¿na je posortowaæ póŸniej
		if((maxAmplitudeSample + 3 > minAmplitudeSample) || (temp.size() < minAmplitudeSample + 2) || (maxAmplitudeSample < 2)){

			itArtifacts = this->artifactsClass.begin() + this->goodQrsNumber.at(i);
			this->artifactsClass.insert(itArtifacts, 3);
			this->artifactsClass.erase(this->artifactsClass.begin() + this->goodQrsNumber.at(i) + 1);
			this->artifactsForClassification.push_back(this->qrsOnset.at(goodQrsNumber.at(i)));
			this->artifactsForClassification.push_back(this->qrsEnd.at(goodQrsNumber.at(i)));
			itMap = this->signalMap.find(goodQrsNumber.at(i));
			this->signalMap.erase(itMap);
			this->goodQrsNumber.erase(goodQrsNumber.begin() + i); 

			// usuwaj¹c dan¹ próbkê np. nr 7, próbka nr 8 wskakuje na jej miejsce, musimy wiêc wykonaæ odejmowanie i-- ¿eby
			// przy kolejnym przejœciu pêtli trafiæ na nasz¹ 8
			i--;
		} else{

			this->qrsMaxAmplitudes.push_back(maxAmplitude);
			this->qrsMinAmplitudes.push_back(minAmplitude);

			// iteratory s¹ "pikne" ale robi¹ niestety syf. Nie interesuje nas tutaj numer próbki w mapie, na któr¹ przypada
			// max/min, a numer próbki w ca³ym sygnale. Dlatego dodajemy do obliczonych wartoœci numery próbek, odpowiadaj¹ce
			// pocz¹tkom wyliczanych aktualnie QRSów
			this->qrsMaxAmplitudesSamples.push_back(maxAmplitudeSample + this->qrsOnset.at(this->goodQrsNumber.at(i)));
			this->qrsMinAmplitudesSamples.push_back(minAmplitudeSample + this->qrsOnset.at(this->goodQrsNumber.at(i)));
		}
	}
}


// Obliczenie œredniej z max i min. Tutaj cudów nie ma
void HeartClass::MeanAmplitude(){

	double meanMaxTemp = 0;
	double meanMinTemp = 0;
	
	for(unsigned int i = 0; i < this->qrsMaxAmplitudes.size(); i++){
		
		meanMaxTemp = meanMaxTemp + this->qrsMaxAmplitudes.at(i);
		meanMinTemp = meanMinTemp + this->qrsMinAmplitudes.at(i);
	}
	
	meanMaxTemp = meanMaxTemp/this->qrsMaxAmplitudes.size();
	meanMinTemp = (meanMinTemp/this->qrsMinAmplitudes.size())*(-1);
	this->meanMaxAmplitude = meanMaxTemp;
	this->meanMinAmplitude = meanMinTemp;
}

// Szukanie 30% wartoœci max i min, z lewej i z prawej strony. ¯eby znaleŸæ próbki najbli¿sze tym wartoœciom, trzeba
// od sygna³u odj¹æ te wartoœci, sygna³ odwróciæ wzglêdem OX i znaleŸæ minimum, w danym przedziale
void HeartClass::FrameLocator(){

	unsigned int leftMaxSample;
	unsigned int rightMaxSample;
	unsigned int leftMinSample;
	unsigned int rightMinSample;
	
	vector<double> leftMaxAmplitudeSamples;
	vector<double> rightMaxAmplitudeSamples;
	vector<double> leftMinAmplitudeSamples;
	vector<double> rightMinAmplitudeSamples;

	// Chryste... Ok. Najpierw patrzymy ile mamy dobrych QRSów - czyli rozmiar qrsMaxAmplitudesSamples, bo wsadzaliœmy tutaj wartoœci
	// tylko dla dobrych QRSów
	for(unsigned int i = 0; i < this->signalMap.size(); i++){

		// Dla ka¿dego QRSa wpisujemy od nowa wartoœci do poni¿szych wektorów, dlatego na pocz¹tku ka¿dego obiegu
		// czyœcimy wektory
		leftMaxAmplitudeSamples.clear();
		rightMaxAmplitudeSamples.clear();
		leftMinAmplitudeSamples.clear();
		rightMinAmplitudeSamples.clear();
	


//Szukanie 30% wartoœci max z lewej strony	
			
		// ¯eby by³o proœciej, to bierzemy z naszej mapy wszystkie próbki od pocz¹tku dobrego QRSa do jego maximum (czyli z lewej strony)
		// i ³adujemy do leftMaxAmplitudeSamples, odejmuj¹c wczeœniej 30% wartoœci max. Nastêpnie Odwracanie sygna³u, czyli 
		// przejœcie po wszystkich próbkach i przemno¿enie przez -1 tylko tych ujemnych

		for(unsigned int p = 0; p < this->qrsMaxAmplitudesSamples.at(i) - this->qrsOnset.at(goodQrsNumber.at(i)); p++){

			leftMaxAmplitudeSamples.push_back(this->signalMap[goodQrsNumber.at(i)].at(p) - 0.3*this->qrsMaxAmplitudes.at(i));
			if(leftMaxAmplitudeSamples.at(p) < 0){
				
				leftMaxAmplitudeSamples.at(p) = leftMaxAmplitudeSamples.at(p)*(-1);
			}	
		}

		// Szukanie minimum tak jak w Amplitudes(). Wa¿ne s¹ zakresy. Na koñcu trzeba tak jak w Amplitudes() dodaæ
		// do otrzymanego numeru próbki, numer próbki okreœlaj¹cej pocz¹tek danego QRSa. Dziêki czemu otrzymujemy
		// wartoœæ leftMaxSample (czyli numer próbki z lewej strony max) w formie globalnej (dla ca³ego sygna³u)
		vector<double>::iterator itLeftMax = min_element(leftMaxAmplitudeSamples.begin(), leftMaxAmplitudeSamples.end());
		double leftMaxValue = *itLeftMax;
		leftMaxSample = distance(leftMaxAmplitudeSamples.begin(), itLeftMax) + this->qrsOnset.at(goodQrsNumber.at(i));
		


//Szukanie 30% wartoœci max z prawej strony
		
		// Tutaj ju¿ nie ma tak ³atwo, poniewa¿ poszukujê 30% max z prawej strony pomiêdzy max, a minimum QRSa. 
		// Na iteratorach wygl¹da to fatalnie, ale dzia³a

		// Tak jak poprzednio wspiujemy do rightMaxAmplitudeSamples próbki od maximum do minimum (dlatego, ¿e szukamu 30%
		// wartoœci max z prawej strony)
		for(unsigned int z = 0; z < this->qrsMinAmplitudesSamples.at(i) - this->qrsMaxAmplitudesSamples.at(i) - 1; z++){

			// Trochê zamieszania. W mapie znajdujemy dobry QRS i od próbki, w której mamy maksimum odejmujemy
			// numer próbki okreœlaj¹cy pocz¹tek QRSa. Robimy to, bo pomimo tego, ¿e próbka, w której wystêpuje max
			// mo¿e mieæ numer np. 950, to mapa zawieraj¹ca próbki dla danego QRSa, ma wielkoœæ okreœlon¹ przez iloœæ próbek,
			// czyli np. 10. Nie mo¿emy wiêc szukaæ próbki o numerze 950. Tutaj zamieniamy to tak (uwa¿aj¹c przy tym na 
			// to, ¿e wektor maj¹cy 10 próbek, ma indeksy z zakresu 0-9.
			rightMaxAmplitudeSamples.push_back(this->signalMap[goodQrsNumber.at(i)].at(this->qrsMaxAmplitudesSamples.at(i) - 
				this->qrsOnset.at(goodQrsNumber.at(i)) + z + 1) - 0.3*this->qrsMaxAmplitudes.at(i));

			if(rightMaxAmplitudeSamples.at(z) < 0){
				
				rightMaxAmplitudeSamples.at(z) = rightMaxAmplitudeSamples.at(z)*(-1);
			}
		}

		// Szukamy numeru próbki w mapie, dla których wystêpuje min i max
		double tempMinSample = this->qrsMinAmplitudesSamples.at(i) - this->qrsOnset.at(goodQrsNumber.at(i));
		double tempMaxSample = this->qrsMaxAmplitudesSamples.at(i) - this->qrsOnset.at(goodQrsNumber.at(i));
		tempMinSample = tempMinSample - tempMaxSample - 1;

		// szukamy w jakim zakresie bêdziemy szukaæ 30% max, czyli jeœli max wystêpuje w mapie w 5 próbce, a min w 11
		// to szukanym zakresem jest od 6 do 10. Tutaj szukamy minimum po odjêciu 30% wartoœci max od sygna³u.
		// Problem jest taki, ¿e w naszym wektorze rightMaxAmplitudeSamples próbki zapisane s¹ znowu z indeksami od 0 do iluœ tam,
		// tak¿e do umeru próbki, w którym jest 30% max, musimy dodaæ numer próbki, w mapie, w której wystêpuje maximum
		vector<double>::iterator itRightMax = min_element(rightMaxAmplitudeSamples.begin() + 1, rightMaxAmplitudeSamples.begin() + tempMinSample);
		double rightMaxValue = *itRightMax;

		// Tutaj zamieniamy znaleziony numer znów na numer próbki w sygnale. Tutaj mamy tylko w mapie, czyli
		// np. znaleŸliœmy 30% max z prawej strony w próbce nr 7 (w mapie). W ca³ym sygnale jednak, rzeczywisty numer próbki
		// to np. 989. Tutaj w³aœnie to zamieniamy
		rightMaxSample = distance(rightMaxAmplitudeSamples.begin(), itRightMax) + 1;
		rightMaxSample = rightMaxSample + this->qrsMaxAmplitudesSamples.at(i);
	


//Szukanie 30% wartoœci min z lewej strony
		
		// Analogicznie jak wy¿ej
		for(unsigned int z = 0; z < this->qrsMinAmplitudesSamples.at(i) - this->qrsMaxAmplitudesSamples.at(i) - 1; z++){
		
			leftMinAmplitudeSamples.push_back(this->signalMap[goodQrsNumber.at(i)].at(this->qrsMaxAmplitudesSamples.at(i) - 
				this->qrsOnset.at(goodQrsNumber.at(i)) + z + 1) - 0.3*this->qrsMinAmplitudes.at(i));

			if(leftMinAmplitudeSamples.at(z) < 0){
				
				leftMinAmplitudeSamples.at(z) = leftMinAmplitudeSamples.at(z)*(-1);
			}
		}

		// Poniewa¿ szukanie 30% max z prawej odbywa siê na tych samych próbkach co min z lewej, mo¿emy wykorzystaæ
		// wczeœniej utworzony kod. Dlatego tempMinSample bierzemy z poprzedniego szukania 30% wartoœci max
		vector<double>::iterator itLeftMin = min_element(leftMinAmplitudeSamples.begin(), leftMinAmplitudeSamples.begin() + tempMinSample);
		double leftMinValue = *itLeftMin;
		leftMinSample = distance(leftMinAmplitudeSamples.begin(), itLeftMin) + 1;
		leftMinSample = leftMinSample + this->qrsMaxAmplitudesSamples.at(i);
		//cout << leftMinSample << endl;



//Szukanie 30% wartoœci min z prawej strony

		// Analogicznie
		for(unsigned int z = 0; z < this->qrsEnd.at(goodQrsNumber.at(i)) - this->qrsMinAmplitudesSamples.at(i); z++){
			
			rightMinAmplitudeSamples.push_back(this->signalMap[goodQrsNumber.at(i)].at(this->qrsMinAmplitudesSamples.at(i) -
			this->qrsOnset.at(goodQrsNumber.at(i)) + 1 + z) - 0.3*this->qrsMinAmplitudes.at(i));;

			if(rightMinAmplitudeSamples.at(z) < 0){
				
				rightMinAmplitudeSamples.at(z) = rightMinAmplitudeSamples.at(z)*(-1);
			}	
		}

		vector<double>::iterator itRightMin = min_element(rightMinAmplitudeSamples.begin(), rightMinAmplitudeSamples.end());
		double rightMinValue = *itRightMin;
		rightMinSample = distance(rightMinAmplitudeSamples.begin(), itRightMin) + 1;
		rightMinSample = rightMinSample + this->qrsMinAmplitudesSamples.at(i);

		// Wpisujemy do mapy nasze próbki. Teraz mamy mapê, w której kluczem jest numer QRSa (dobrego QRSa, o numerze
		// wzglêdem ca³oœci sygna³u, czyli nie mo¿emy sobie wpisaæ od i, bo mielibyœmy 0, 1, 2, 3, podczas gdy dobre QRSy
		// to np. 76, 345, 456 itd.), a wartoœci¹ mapy s¹ 4 numery próbek, okreœlaj¹ce odpowiednio:
		// 30% max z lewej i prawej oraz 30% min z lewej i prawej
		this->yQRS[goodQrsNumber.at(i)].push_back(leftMaxSample);
		this->yQRS[goodQrsNumber.at(i)].push_back(rightMaxSample);
		this->yQRS[goodQrsNumber.at(i)].push_back(leftMinSample);
		this->yQRS[goodQrsNumber.at(i)].push_back(rightMinSample);
	}
}


void HeartClass::SamplesBetween(){
    
	double TempMeanMaxSamplesBetween = 0;
	double TempMeanMinSamplesBetween = 0;
	
	// Liczymy liczbê próbek pomiêdzy 30% z lewej i z prawej strony max, i to samo dla min
	// Dodatkowo obliczamy œredni¹ liczbê
    for(unsigned int z = 0; z < this->qrsMaxAmplitudes.size(); z++){

		this->maxSamplesBetween.push_back(this->yQRS[goodQrsNumber.at(z)].at(1) - this->yQRS[goodQrsNumber.at(z)].at(0) + 1);
		this->minSamplesBetween.push_back(this->yQRS[goodQrsNumber.at(z)].at(3) - this->yQRS[goodQrsNumber.at(z)].at(2) + 1);
		
		TempMeanMaxSamplesBetween = TempMeanMaxSamplesBetween + this->maxSamplesBetween.at(z);
		TempMeanMinSamplesBetween = TempMeanMinSamplesBetween + this->minSamplesBetween.at(z);
	}

	TempMeanMaxSamplesBetween = TempMeanMaxSamplesBetween/this->signalMap.size();
	TempMeanMinSamplesBetween = TempMeanMinSamplesBetween/this->signalMap.size();
	
	this->meanSamplesBetweenMax = TempMeanMaxSamplesBetween;
	this->meanSamplesBetweenMin = TempMeanMinSamplesBetween;
	
    for(unsigned int z = 0; z < this->signalMap.size(); z++){
    	
		for(unsigned int k = this->yQRS[goodQrsNumber.at(z)].at(0) - this->qrsOnset.at(goodQrsNumber.at(z)); 
			k < this->yQRS[goodQrsNumber.at(z)].at(1) - this->qrsOnset.at(goodQrsNumber.at(z)) + 1; k++){
			
			this->samplesBetweenMax[goodQrsNumber.at(z)].push_back(this->signalMap[goodQrsNumber.at(z)].at(k));
		}
    }

	double tempMeanMaxArea = 0;

	// Obliczanie pola od 30% max z lewej do 30% max z prawej (tylko dla max)
    for(unsigned int z = 0; z < this->signalMap.size(); z++){
    
		this->maxArea.push_back(ComplexArea(&this->samplesBetweenMax[goodQrsNumber.at(z)]));
		tempMeanMaxArea = this->maxArea.at(z) + tempMeanMaxArea;
    }
    
    tempMeanMaxArea = tempMeanMaxArea/this->signalMap.size();
    this->meanMaxArea = tempMeanMaxArea;
}


void HeartClass::Conditioning(HeartClassResult& heartClassResults){

	heartClassResults.qrsClass = this->artifactsClass;

	vector<double>::iterator itArtifacts;

	bool firstCondition = false;
	bool secondCondition = false;
	bool thirdCondition = false;
	bool fourthCondition = false;
	bool fifthCondition = false;
	bool sixthCondition = false;
	bool seventhCondition = false;
	
	for(unsigned int z = 0; z < this->signalMap.size(); z++){
		
		firstCondition = false;
		secondCondition = false;
		thirdCondition = false;
		fourthCondition = false;
		fifthCondition = false;
		sixthCondition = false;
		seventhCondition = false;
			
		if(this->qrsMaxAmplitudes.at(z) >= 2.5*this->meanMaxAmplitude){
			
			firstCondition = true;
		}
	
		if(this->meanMinAmplitude < 0){

			if(((this->qrsMinAmplitudes.at(z))*(-1)) >= -2.5*this->meanMinAmplitude){
			
				secondCondition = true;
			}
		}else{

			if((this->qrsMinAmplitudes.at(z)) >= 2.5*this->meanMinAmplitude){
			
				secondCondition = true;
			}
		}
		
		if(this->maxSamplesBetween.at(z) >= 2*this->meanSamplesBetweenMax){
			
			thirdCondition = true;
		}

		if(this->minSamplesBetween.at(z) >= 2*this->meanSamplesBetweenMin){
			
			fourthCondition = true;
		}
		
		if(this->maxArea.at(z) >= 1.8*this->meanMaxArea){
			
			fifthCondition = true;
		}
		
//!!! TUTAJ W OBU IFACH ZAMIAST 100 POWINNA BYC CZESTOTLIWOSC SYGNALU czyli frequency

		if((1000*this->signalMap[goodQrsNumber.at(z)].size()/100) > 130){
			
			sixthCondition = true;
		}
		
		if(round(1000*this->signalMap[goodQrsNumber.at(z)].size()/100) > 100){
			
			seventhCondition = true;
		}

		/*cout << firstCondition << " ";
		cout << secondCondition << " ";
		cout << thirdCondition << " ";
		cout << fourthCondition << " ";
		cout << fifthCondition << " ";
		cout << sixthCondition << " ";
		cout << seventhCondition << endl;*/
			
		if((firstCondition == true) || (secondCondition == true) || (thirdCondition == true) || (fourthCondition == true) || (fifthCondition == true)){
			
			if(sixthCondition == true){
				
				itArtifacts = heartClassResults.qrsClass.begin() + this->goodQrsNumber.at(z);
				heartClassResults.qrsClass.insert(itArtifacts, 2);
				heartClassResults.qrsClass.erase(heartClassResults.qrsClass.begin() + this->goodQrsNumber.at(z) + 1);
				heartClassResults.qrsClassificationMap["VQRS"].push_back(this->qrsOnset.at(this->goodQrsNumber.at(z)));
				heartClassResults.qrsClassificationMap["VQRS"].push_back(this->qrsEnd.at(this->goodQrsNumber.at(z)));
			}
			else{
				
				itArtifacts = heartClassResults.qrsClass.begin() + this->goodQrsNumber.at(z);
				heartClassResults.qrsClass.insert(itArtifacts, 3);
				heartClassResults.qrsClass.erase(heartClassResults.qrsClass.begin() + this->goodQrsNumber.at(z) + 1);
				heartClassResults.qrsClassificationMap["Artifacts"].push_back(this->qrsOnset.at(this->goodQrsNumber.at(z)));
				heartClassResults.qrsClassificationMap["Artifacts"].push_back(this->qrsEnd.at(this->goodQrsNumber.at(z)));
			}
		}
		else{
			
			if(seventhCondition == true){
				
				itArtifacts = heartClassResults.qrsClass.begin() + this->goodQrsNumber.at(z);
				heartClassResults.qrsClass.insert(itArtifacts, 3);
				heartClassResults.qrsClass.erase(heartClassResults.qrsClass.begin() + this->goodQrsNumber.at(z) + 1);
				heartClassResults.qrsClassificationMap["Artifacts"].push_back(this->qrsOnset.at(this->goodQrsNumber.at(z)));
				heartClassResults.qrsClassificationMap["Artifacts"].push_back(this->qrsEnd.at(this->goodQrsNumber.at(z)));
			}
			else{
				
				itArtifacts = heartClassResults.qrsClass.begin() + this->goodQrsNumber.at(z);
				heartClassResults.qrsClass.insert(itArtifacts, 1);
				heartClassResults.qrsClass.erase(heartClassResults.qrsClass.begin() + this->goodQrsNumber.at(z) + 1);
				heartClassResults.qrsClassificationMap["NormalQRS"].push_back(this->qrsOnset.at(this->goodQrsNumber.at(z)));
				heartClassResults.qrsClassificationMap["NormalQRS"].push_back(this->qrsEnd.at(this->goodQrsNumber.at(z)));
			}
		}
	}	
	/*for(unsigned int i = 0; i < heartClassResults.qrsClass.size(); i++){
		
		cout << "QRS numer " << i << " nalezy do klasy numer: " << heartClassResults.qrsClass.at(i) << endl;
	}*/
	
	//Zwracanie parametrów
	heartClassResults.qrsParameters.insert(pair<string, double>("Mean maximum amplitude", this->meanMaxAmplitude));
	heartClassResults.qrsParameters.insert(pair<string, double>("Mean minimum amplitude", this->meanMinAmplitude));
	heartClassResults.qrsParameters.insert(pair<string, double>("Mean area", this->meanMaxArea));
	heartClassResults.qrsParameters.insert(pair<string, double>("Mean length of maximum", this->meanSamplesBetweenMax));
	heartClassResults.qrsParameters.insert(pair<string, double>("Mean length of minimum", this->meanSamplesBetweenMin));
	heartClassResults.qrsParameters.insert(pair<string, double>("Number of ventricular QRS", heartClassResults.qrsClassificationMap["VQRS"].size()/2));
	heartClassResults.qrsParameters.insert(pair<string, double>("Number of artifacts", heartClassResults.qrsClassificationMap["Artifacts"].size()/2));
	//Jednostki 
	heartClassResults.qrsUnits[0] = "mV";
	heartClassResults.qrsUnits[1] = "mV";
	heartClassResults.qrsUnits[2] = "mv^2";
	heartClassResults.qrsUnits[3] = "-";
	heartClassResults.qrsUnits[4] = "-";
	heartClassResults.qrsUnits[5] = "-";
	heartClassResults.qrsUnits[6] = "-";
	heartClassResults.qrsUnits[7] = "-";
}

HeartClassResult* HeartClass::compute(ResultKeeper* rkp){

	this->InputPrepare();
	this->Amplitudes();
	this->MeanAmplitude();
	this->FrameLocator();
	this->SamplesBetween();

	HeartClassResult heartResults;
	this->Conditioning(heartResults);
	
	return heartResults.getResult();
}



















