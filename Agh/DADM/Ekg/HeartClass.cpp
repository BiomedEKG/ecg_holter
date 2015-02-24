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


// Mo�e nie umiem pisa� kodu, ale Visual nie rozpoznaje funkcji round. Dlatego mamy swoj�
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


// Wpisanie wynik�w z ECG i Waves do osobnych zmiennych
HeartClass::HeartClass(ResultKeeper* rkp){

	// Tutaj tylko wsadzamy to co da� Waves i ECG do zmiennych. Nic wi�cej z nimi nie robimy. Dopiero p�niej pracujemy na tych zmiennych
	map <string, vector<int>> wavesData = rkp->getWaves()->GetWavesResultData();
	this->qrsEnd = wavesData["QRS_END"];
	this->qrsOnset = wavesData["QRS_ONSET"];
	this->signalFromEcg = rkp->getECGBaseline()->getFilteredSignal()

	vector<double> tempVector (this->qrsEnd.size(), 0);
	this->artifactsClass = tempVector;
}


// Utworzenie mapy, w kt�rej kluczem jest numer QRSa, a warto�ciami wektory amplitud zespo��w
// Ca�o�� jest przekomplikowana z powodu pustych warto�ci wektor�w i qrsEnd, kt�re wyst�puj� wcze�niej ni� qrsOnset -.-
// No i dochodzi jeszcze fakt, �e musimy mie� QRSy po kolei, czyli te z�e te� musimy uznawa� za wyniki wrrrrr
void HeartClass::InputPrepare(){

	unsigned int signalBegin = 0;
	unsigned int signalEnd = 0; 
	unsigned int tempSignalEnd;
	vector<double>::iterator itArtifacts;
	for(unsigned int i = 0; i < this->qrsEnd.size(); i++){
		
		signalBegin = (unsigned int) this->qrsOnset.at(i);
		signalEnd = (unsigned int) this->qrsEnd.at(i);

		// Pozbycie si� QRS�w reprezentowanych przez mniej ni� 8 pr�bek, pustych i gdy End jest przed Onset....
		if(((signalEnd - signalBegin) < 9) || (this->qrsOnset.at(i) == NULL) || (signalEnd < signalBegin)){

			// Bezsensowne wyniki zerujemy. Nie mo�emy usuwa�, bo zmienialiby�my numery QRS�w (kolejno�� ich wyst�pienia, co znowu
			// bru�dzi�o by innym modu�om ni�ej... Trzeba zerowa�. Opr�cz tego zapisujemy te z�e QRSy jako artefakty, do wektor�w, kt�re
			// b�d� do��czone do wynik�w
			itArtifacts = this->artifactsClass.begin() + i;
			this->artifactsClass.insert(itArtifacts, 3);
			this->artifactsClass.erase(this->artifactsClass.begin() + i + 1);
			this->artifactsForClassification.push_back(this->qrsOnset.at(i));
			this->artifactsForClassification.push_back(this->qrsEnd.at(i));
			this->qrsEnd.at(i) = 0;
			this->qrsOnset.at(i) = 0;
		} else{

			// Trzeba utworzy� dodatkow� zmienna, kt�ra b�dzie zapisywa� numery dobrych QRS�w
			this->goodQrsNumber.push_back(i);
		}
		
		// Je�li qrsEnd wyst�puje wcze�niej ni� qrsOnset, to musimy zamieni� warto�ci miejscami, inaczej p�niej zapisuj�c pr�bki
		// ka�dego qrsa w mapie signalMap, mapa by�aby kr�tsza, poniewa� nie wy�apywa�aby tych qrs�w, w kt�rych w�asnie qrsEnd
		// jest wcze�niej ni� Onset. Wszystko sprowadza si� do tego, �e musimy przej�� przez wszystkie QRSy. Gdyby�my je pomijali
		// to m�wi�c o QRSie nr 30 mogliby�my m�wi� tak naprawd� o QRSie np. 78
		if(signalBegin > signalEnd){

			tempSignalEnd = signalEnd;
			signalEnd = signalBegin;
			signalBegin = tempSignalEnd;
		}

		// Tutaj zapisujemy do naszej mapy, gdzie kluczem jest numer QRSa, a warto�ciami wektory amplitud pr�bek, kt�re go opisuj�.
		// Dzi�ki wcze�niejszym operacjom, nasza mapa nie ma kluczy po kolei, czyli nie ma 1, 2, 3, 4, a tylko takie, kt�re odpowiadaj�
		// dobrym QRSom, czyli kolejne klucze mog� wygl�da� tak: 5, 18, 29, 45 itd.
		for(unsigned int j = 0; signalBegin < signalEnd+1; signalBegin++){
			
			if((this->qrsOnset.at(i) != 0) && (this->qrsEnd.at(i) != 0)){

				this->signalMap[i].push_back(this->signalFromEcg.at(signalBegin));
			} 
		}
	}
}


// Wyliczanie warto�ci i numeru pr�bki max i min dla danego QRSa, z czego min wyst�puje zawsze po max
void HeartClass::Amplitudes(){

	vector<double> temp;
	map<int, vector<double>>::iterator itMap;
	vector<double>::iterator itArtifacts;

	// Idziemy tylko po dobrych QRSach. Ich numery zapisane s� w goodQrsNumber
	for(unsigned int i = 0; i < this->goodQrsNumber.size(); i++){
		
		// Tu do tempa wpisujemy warto�ci z mapy, czyli amplitudy wszystkich pr�bek, przypadaj�cych na dany QRS
		temp = this->signalMap[this->goodQrsNumber.at(i)];	
		
		vector<double>::iterator it = max_element(temp.begin(), temp.end());
		double maxAmplitude = *it;
		unsigned int maxAmplitudeSample = distance(temp.begin(), it);

		//Wyszukiwanie minimum ktore jest zawsze po maksimum
		vector<double>::iterator itMin = min_element(it, temp.end());
		double minAmplitude = *itMin;
		unsigned int  minAmplitudeSample =  maxAmplitudeSample + distance(it, itMin);

		// QRSy, kt�rych minimum jest oddalone o mniej ni� 2 pr�bki od max i QRSy, kt�rych ostatni� pr�bk� jest 
		// znalezione minimum oraz te, kt�re z lewej strony max maj� 0 pr�bek, r�wnie� s� artefaktami. Zn�w musimy 
		// wpisa� te z�e QRSy do dopowiednich element�w i dodatkowo usun�� te QRSy z mapy. Dzi�ki temu mamy teraz 
		// w mapie tylko poprawnie wykryte QRSy.
		// Co prawda QRSy zapisane w artifactsClass i artifactsForClassification nie s� po kolei, ale mo�na je posortowa� p�niej
		if((maxAmplitudeSample + 3 > minAmplitudeSample) || (temp.size() < minAmplitudeSample + 2) || (maxAmplitudeSample < 2)){

			itArtifacts = this->artifactsClass.begin() + this->goodQrsNumber.at(i);
			this->artifactsClass.insert(itArtifacts, 3);
			this->artifactsClass.erase(this->artifactsClass.begin() + this->goodQrsNumber.at(i) + 1);
			this->artifactsForClassification.push_back(this->qrsOnset.at(goodQrsNumber.at(i)));
			this->artifactsForClassification.push_back(this->qrsEnd.at(goodQrsNumber.at(i)));
			itMap = this->signalMap.find(goodQrsNumber.at(i));
			this->signalMap.erase(itMap);
			this->goodQrsNumber.erase(goodQrsNumber.begin() + i); 

			// usuwaj�c dan� pr�bk� np. nr 7, pr�bka nr 8 wskakuje na jej miejsce, musimy wi�c wykona� odejmowanie i-- �eby
			// przy kolejnym przej�ciu p�tli trafi� na nasz� 8
			i--;
		} else{

			this->qrsMaxAmplitudes.push_back(maxAmplitude);
			this->qrsMinAmplitudes.push_back(minAmplitude);

			// iteratory s� "pikne" ale robi� niestety syf. Nie interesuje nas tutaj numer pr�bki w mapie, na kt�r� przypada
			// max/min, a numer pr�bki w ca�ym sygnale. Dlatego dodajemy do obliczonych warto�ci numery pr�bek, odpowiadaj�ce
			// pocz�tkom wyliczanych aktualnie QRS�w
			this->qrsMaxAmplitudesSamples.push_back(maxAmplitudeSample + this->qrsOnset.at(this->goodQrsNumber.at(i)));
			this->qrsMinAmplitudesSamples.push_back(minAmplitudeSample + this->qrsOnset.at(this->goodQrsNumber.at(i)));
		}
	}
}


// Obliczenie �redniej z max i min. Tutaj cud�w nie ma
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

// Szukanie 30% warto�ci max i min, z lewej i z prawej strony. �eby znale�� pr�bki najbli�sze tym warto�ciom, trzeba
// od sygna�u odj�� te warto�ci, sygna� odwr�ci� wzgl�dem OX i znale�� minimum, w danym przedziale
void HeartClass::FrameLocator(){

	unsigned int leftMaxSample;
	unsigned int rightMaxSample;
	unsigned int leftMinSample;
	unsigned int rightMinSample;
	
	vector<double> leftMaxAmplitudeSamples;
	vector<double> rightMaxAmplitudeSamples;
	vector<double> leftMinAmplitudeSamples;
	vector<double> rightMinAmplitudeSamples;

	// Chryste... Ok. Najpierw patrzymy ile mamy dobrych QRS�w - czyli rozmiar qrsMaxAmplitudesSamples, bo wsadzali�my tutaj warto�ci
	// tylko dla dobrych QRS�w
	for(unsigned int i = 0; i < this->signalMap.size(); i++){

		// Dla ka�dego QRSa wpisujemy od nowa warto�ci do poni�szych wektor�w, dlatego na pocz�tku ka�dego obiegu
		// czy�cimy wektory
		leftMaxAmplitudeSamples.clear();
		rightMaxAmplitudeSamples.clear();
		leftMinAmplitudeSamples.clear();
		rightMinAmplitudeSamples.clear();
	


//Szukanie 30% warto�ci max z lewej strony	
			
		// �eby by�o pro�ciej, to bierzemy z naszej mapy wszystkie pr�bki od pocz�tku dobrego QRSa do jego maximum (czyli z lewej strony)
		// i �adujemy do leftMaxAmplitudeSamples, odejmuj�c wcze�niej 30% warto�ci max. Nast�pnie Odwracanie sygna�u, czyli 
		// przej�cie po wszystkich pr�bkach i przemno�enie przez -1 tylko tych ujemnych

		for(unsigned int p = 0; p < this->qrsMaxAmplitudesSamples.at(i) - this->qrsOnset.at(goodQrsNumber.at(i)); p++){

			leftMaxAmplitudeSamples.push_back(this->signalMap[goodQrsNumber.at(i)].at(p) - 0.3*this->qrsMaxAmplitudes.at(i));
			if(leftMaxAmplitudeSamples.at(p) < 0){
				
				leftMaxAmplitudeSamples.at(p) = leftMaxAmplitudeSamples.at(p)*(-1);
			}	
		}

		// Szukanie minimum tak jak w Amplitudes(). Wa�ne s� zakresy. Na ko�cu trzeba tak jak w Amplitudes() doda�
		// do otrzymanego numeru pr�bki, numer pr�bki okre�laj�cej pocz�tek danego QRSa. Dzi�ki czemu otrzymujemy
		// warto�� leftMaxSample (czyli numer pr�bki z lewej strony max) w formie globalnej (dla ca�ego sygna�u)
		vector<double>::iterator itLeftMax = min_element(leftMaxAmplitudeSamples.begin(), leftMaxAmplitudeSamples.end());
		double leftMaxValue = *itLeftMax;
		leftMaxSample = distance(leftMaxAmplitudeSamples.begin(), itLeftMax) + this->qrsOnset.at(goodQrsNumber.at(i));
		


//Szukanie 30% warto�ci max z prawej strony
		
		// Tutaj ju� nie ma tak �atwo, poniewa� poszukuj� 30% max z prawej strony pomi�dzy max, a minimum QRSa. 
		// Na iteratorach wygl�da to fatalnie, ale dzia�a

		// Tak jak poprzednio wspiujemy do rightMaxAmplitudeSamples pr�bki od maximum do minimum (dlatego, �e szukamu 30%
		// warto�ci max z prawej strony)
		for(unsigned int z = 0; z < this->qrsMinAmplitudesSamples.at(i) - this->qrsMaxAmplitudesSamples.at(i) - 1; z++){

			// Troch� zamieszania. W mapie znajdujemy dobry QRS i od pr�bki, w kt�rej mamy maksimum odejmujemy
			// numer pr�bki okre�laj�cy pocz�tek QRSa. Robimy to, bo pomimo tego, �e pr�bka, w kt�rej wyst�puje max
			// mo�e mie� numer np. 950, to mapa zawieraj�ca pr�bki dla danego QRSa, ma wielko�� okre�lon� przez ilo�� pr�bek,
			// czyli np. 10. Nie mo�emy wi�c szuka� pr�bki o numerze 950. Tutaj zamieniamy to tak (uwa�aj�c przy tym na 
			// to, �e wektor maj�cy 10 pr�bek, ma indeksy z zakresu 0-9.
			rightMaxAmplitudeSamples.push_back(this->signalMap[goodQrsNumber.at(i)].at(this->qrsMaxAmplitudesSamples.at(i) - 
				this->qrsOnset.at(goodQrsNumber.at(i)) + z + 1) - 0.3*this->qrsMaxAmplitudes.at(i));

			if(rightMaxAmplitudeSamples.at(z) < 0){
				
				rightMaxAmplitudeSamples.at(z) = rightMaxAmplitudeSamples.at(z)*(-1);
			}
		}

		// Szukamy numeru pr�bki w mapie, dla kt�rych wyst�puje min i max
		double tempMinSample = this->qrsMinAmplitudesSamples.at(i) - this->qrsOnset.at(goodQrsNumber.at(i));
		double tempMaxSample = this->qrsMaxAmplitudesSamples.at(i) - this->qrsOnset.at(goodQrsNumber.at(i));
		tempMinSample = tempMinSample - tempMaxSample - 1;

		// szukamy w jakim zakresie b�dziemy szuka� 30% max, czyli je�li max wyst�puje w mapie w 5 pr�bce, a min w 11
		// to szukanym zakresem jest od 6 do 10. Tutaj szukamy minimum po odj�ciu 30% warto�ci max od sygna�u.
		// Problem jest taki, �e w naszym wektorze rightMaxAmplitudeSamples pr�bki zapisane s� znowu z indeksami od 0 do ilu� tam,
		// tak�e do umeru pr�bki, w kt�rym jest 30% max, musimy doda� numer pr�bki, w mapie, w kt�rej wyst�puje maximum
		vector<double>::iterator itRightMax = min_element(rightMaxAmplitudeSamples.begin() + 1, rightMaxAmplitudeSamples.begin() + tempMinSample);
		double rightMaxValue = *itRightMax;

		// Tutaj zamieniamy znaleziony numer zn�w na numer pr�bki w sygnale. Tutaj mamy tylko w mapie, czyli
		// np. znale�li�my 30% max z prawej strony w pr�bce nr 7 (w mapie). W ca�ym sygnale jednak, rzeczywisty numer pr�bki
		// to np. 989. Tutaj w�a�nie to zamieniamy
		rightMaxSample = distance(rightMaxAmplitudeSamples.begin(), itRightMax) + 1;
		rightMaxSample = rightMaxSample + this->qrsMaxAmplitudesSamples.at(i);
	


//Szukanie 30% warto�ci min z lewej strony
		
		// Analogicznie jak wy�ej
		for(unsigned int z = 0; z < this->qrsMinAmplitudesSamples.at(i) - this->qrsMaxAmplitudesSamples.at(i) - 1; z++){
		
			leftMinAmplitudeSamples.push_back(this->signalMap[goodQrsNumber.at(i)].at(this->qrsMaxAmplitudesSamples.at(i) - 
				this->qrsOnset.at(goodQrsNumber.at(i)) + z + 1) - 0.3*this->qrsMinAmplitudes.at(i));

			if(leftMinAmplitudeSamples.at(z) < 0){
				
				leftMinAmplitudeSamples.at(z) = leftMinAmplitudeSamples.at(z)*(-1);
			}
		}

		// Poniewa� szukanie 30% max z prawej odbywa si� na tych samych pr�bkach co min z lewej, mo�emy wykorzysta�
		// wcze�niej utworzony kod. Dlatego tempMinSample bierzemy z poprzedniego szukania 30% warto�ci max
		vector<double>::iterator itLeftMin = min_element(leftMinAmplitudeSamples.begin(), leftMinAmplitudeSamples.begin() + tempMinSample);
		double leftMinValue = *itLeftMin;
		leftMinSample = distance(leftMinAmplitudeSamples.begin(), itLeftMin) + 1;
		leftMinSample = leftMinSample + this->qrsMaxAmplitudesSamples.at(i);
		//cout << leftMinSample << endl;



//Szukanie 30% warto�ci min z prawej strony

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

		// Wpisujemy do mapy nasze pr�bki. Teraz mamy map�, w kt�rej kluczem jest numer QRSa (dobrego QRSa, o numerze
		// wzgl�dem ca�o�ci sygna�u, czyli nie mo�emy sobie wpisa� od i, bo mieliby�my 0, 1, 2, 3, podczas gdy dobre QRSy
		// to np. 76, 345, 456 itd.), a warto�ci� mapy s� 4 numery pr�bek, okre�laj�ce odpowiednio:
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
	
	// Liczymy liczb� pr�bek pomi�dzy 30% z lewej i z prawej strony max, i to samo dla min
	// Dodatkowo obliczamy �redni� liczb�
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
	
	//Zwracanie parametr�w
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



















