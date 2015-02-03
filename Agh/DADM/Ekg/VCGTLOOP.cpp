#include <math.h>
#include <methodsVCG.h>
#include <VCGTLOOP.h>

using namespace std;


ResultVCG* VCGTLoop::compute (ResultKeeper *rkp) 
{
	//obiekt zwracany res
	ResultVCG *res = new ResultVCG;
	
 map <string,double> param;
 param["mMA"] = 0;
 param["mRMMV"] = 0;

 map <char,vector<double>> XYZ;
 XYZ['X'];
 XYZ['Y'];
 XYZ['Z'];
  

//Tutaj chcemy sobie wziac 8 przefiltrowanych przez ECGBaseline odprowadzen
vector<double> i = rkp->i; 
vector<double> ii = rkp->ii;
vector<double> v1 = rkp->v1;
vector<double> v2 = rkp->v2;
vector<double> v3 = rkp->v3;
vector<double> v4 = rkp->v4;
vector<double> v5 = rkp->v5;
vector<double> v6 = rkp->v6;

//A tutaj chcemy wziac wiadomo co, bo jest napisane, od Waves
vector<double> QRS_ONSET = rkp->QRS_ONSET; //INDEKSY!!!!!!!!!!!!!!!!!!!!! a nie wartoúci
vector<double> QRS_END = rkp->QRS_END; //INDEKSY!!!!!!!!!!!!!!!!!!!!!
vector<double> T_ONSET = rkp->T_ONSET; //INDEKSY!!!!!!!!!!!!!!!!!!!!!
vector<double> T_END = rkp->T_END; //INDEKSY!!!!!!!!!!!!!!!!!!!!!

XYZ = DowerTransform ( i, ii, v1, v2, v3, v4, v5, v6);
AllX = XYZ['X'];
AllY = XYZ['Y'];
AllZ = XYZ['Z'];

int HeartbeatsCtr;
int HeartbeatsAmount= sizeof(QRS_ONSET);    
double ElAz_Sum = 0; // We will need to sum all DEA to calculate the DEA mean

vector <double> All_T_AxisVectorsX;   //Init array containing T endpoints coordinates
vector <double> All_T_AxisVectorsY;
vector <double> All_T_AxisVectorsZ;

vector <double> All_T_AxisModules; //Init array containing magnitudes of axis vectors (needed in RMMV)

vector <double> All_QRS_AxisVectorsX;   //Init array containing QRS endpoints coordinates
vector <double> All_QRS_AxisVectorsY;
vector <double> All_QRS_AxisVectorsZ;

vector <double> T_LoopsModulesMeans; //Init array containing mean values for each loop (needed in RMMV)
vector <double> DEA_EachLoopMeans;
vector < double >::iterator wsk_DEA_EachLoopMeans = DEA_EachLoopMeans.begin();


//-----Znajdümy punkt izoelektryczny w ca≥ym VCG:---------------------------
vector <double> Z; 

double IsoelectricPoint[3]= {AllX[0],AllY[0],AllZ[0]};
double minZ= sqrt(AllX[0]*AllX[0] + AllY[0]*AllY[0] + AllZ[0]*AllZ[0]);  // Z[0]

for (HeartbeatsCtr = 1;  HeartbeatsCtr < AllSignalLength+1; HeartbeatsCtr++){
	Z[HeartbeatsCtr] = sqrt(AllX[HeartbeatsCtr]*AllX[HeartbeatsCtr] + AllY[HeartbeatsCtr]*AllY[HeartbeatsCtr] + AllZ[HeartbeatsCtr]*AllZ[HeartbeatsCtr]);
	if (Z[HeartbeatsCtr-1]>Z[HeartbeatsCtr] & minZ>Z[HeartbeatsCtr]){
		IsoelectricPoint[0,1,2]=AllX[HeartbeatsCtr],AllY[HeartbeatsCtr],AllZ[HeartbeatsCtr];
	    minZ = Z[HeartbeatsCtr];
	}
}

//==============================================================================================================

for (HeartbeatsCtr = 0;  HeartbeatsCtr < HeartbeatsAmount; HeartbeatsCtr++){

	double LoopPointsCtr;
// ------------------------- T-LOOP -----------------------------------------
	double T_MaxModuleValue = 0; //Init maximum T loop's module value
    double T_ModulesSum = 0; //Init sum needed to count up the mean value (needed in RMMV)
	double dzielnik = 0;
	double T_AxisVector[3]={0,0,0};
// ------------------------- QRS-LOOP -----------------------------------------
    double QRS_AxisVector[3] = {0,0,0}; //Init QRS loop axis vectors
    double QRS_MaxModuleValue = 0; //Init maximum QRS loop's module value
    double X,Y,Z; 
	double ThisPointModule;

// ------------------------- T-LOOP -----------------------------------------
    
	for (LoopPointsCtr = T_ONSET[HeartbeatsCtr]; LoopPointsCtr < T_END[HeartbeatsCtr]; LoopPointsCtr++)	{
	
		double ThisPointVector [3];
		double ThisPointLSVector [2];
		double Z_axis_LSVector [2] = {0,1}; //[Y,Z]
		double X_axis_FVector [2] = {1,0}; //[X,Y]
		double ThisPointFVector [2] = {0,0};
		double Elevation;
		double Azimuth;
		double ThisPointModule;   
		double dot1;

// ------------------------- T-LOOP -----------------------------------------
		X = AllX[LoopPointsCtr];
		Y = AllY[LoopPointsCtr];
		Z = AllZ[LoopPointsCtr];

		ThisPointModule = sqrt(pow(X-IsoelectricPoint[0],2) + pow(Y-IsoelectricPoint[1],2) + pow(Z-IsoelectricPoint[2],2)) ;
	 
		if (ThisPointModule>T_MaxModuleValue){

				T_MaxModuleValue = ThisPointModule;
				T_AxisVector[0] = AllX[LoopPointsCtr];
				T_AxisVector[1] = AllY[LoopPointsCtr];
				T_AxisVector[2] = AllZ[LoopPointsCtr];
		}
		T_ModulesSum = T_ModulesSum + ThisPointModule; //(needed in RMMV)
        
        //Meanwhile do some calculcations for DEA:
        ThisPointVector[0] = AllX[LoopPointsCtr];
		ThisPointVector[1] = AllY[LoopPointsCtr]; 
		ThisPointVector[2] = AllZ[LoopPointsCtr];
		ThisPointLSVector[0,1] = ThisPointVector[2], ThisPointVector[3]; //[Y,Z], LS - Left Sagittal plane
        
		
		dot1 = dot(ThisPointLSVector,Z_axis_LSVector);
        Elevation = acos(dot1/norm(ThisPointLSVector)/norm(Z_axis_LSVector)); 

		ThisPointFVector [0,1]= ThisPointVector[0], ThisPointVector[1]; //[X,Y], F - Frontal plane
   
		dot1 = dot(ThisPointFVector,X_axis_FVector);
        Azimuth = acos(dot1/norm(ThisPointFVector)/norm(X_axis_FVector)); 
        ElAz_Sum = ElAz_Sum + abs(Elevation-Azimuth); //as DEA = mean(abs(El-Az)    
        dzielnik = dzielnik+1;   
   	}
	
	All_T_AxisVectorsX[HeartbeatsCtr] = T_AxisVector[0];
	All_T_AxisVectorsY[HeartbeatsCtr] = T_AxisVector[1];
	All_T_AxisVectorsZ[HeartbeatsCtr] = T_AxisVector[2];
    All_T_AxisModules[HeartbeatsCtr] = T_MaxModuleValue; //(needed in RMMV)
    T_LoopsModulesMeans[HeartbeatsCtr] = T_ModulesSum/(T_END[HeartbeatsCtr]-T_ONSET[HeartbeatsCtr]+1); //(needed in RMMV)
    DEA_EachLoopMeans[HeartbeatsCtr] = ElAz_Sum/dzielnik;  // (needed in DEA)
   

// ------------------------- QRS-LOOP -----------------------------------------	
    
	for (LoopPointsCtr = QRS_ONSET[HeartbeatsCtr]; LoopPointsCtr<QRS_END[HeartbeatsCtr]; LoopPointsCtr++){
		X = AllX[LoopPointsCtr];
		Y = AllY[LoopPointsCtr];
		Z = AllZ[LoopPointsCtr];

		ThisPointModule = sqrt(pow(X-IsoelectricPoint[0],2) + pow(Y-IsoelectricPoint[1],2) + pow(Z-IsoelectricPoint[2],2)) ;

		 if (ThisPointModule>QRS_MaxModuleValue){
			    QRS_MaxModuleValue = ThisPointModule;
				QRS_AxisVector [0] = AllX[LoopPointsCtr];
				QRS_AxisVector [1] = AllY[LoopPointsCtr];
				QRS_AxisVector [2] = AllZ[LoopPointsCtr];
		 }
	}
    
	All_QRS_AxisVectorsX[HeartbeatsCtr] = QRS_AxisVector[0];
	All_QRS_AxisVectorsY[HeartbeatsCtr] = QRS_AxisVector[1];
	All_QRS_AxisVectorsZ[HeartbeatsCtr] = QRS_AxisVector[2];
	
}


//Calculate MA parameter for each heartbeat:

vector <double> mMA; 
vector < double >::iterator wsk_mMA = mMA.begin();

double TLoopVector_XY[2];
double TLoopVector_XZ[2];
double TLoopVector_ZY[2];

double QRSLoopVector_XY[2];
double QRSLoopVector_XZ[2];
double QRSLoopVector_ZY[2];
double ResultmMA, ResultmMA_std;
double A_F, A_H, A_LS, max;

for (HeartbeatsCtr = 0;  HeartbeatsCtr < HeartbeatsAmount; HeartbeatsCtr++){

	//Calculate axis (as vectors)
	TLoopVector_XY[0,1,2] = All_T_AxisVectorsX[HeartbeatsCtr], All_T_AxisVectorsY[HeartbeatsCtr];
	TLoopVector_XZ[0,1,2] = All_T_AxisVectorsX[HeartbeatsCtr], All_T_AxisVectorsZ[HeartbeatsCtr];
	TLoopVector_ZY[0,1,2] = All_T_AxisVectorsY[HeartbeatsCtr], All_T_AxisVectorsZ[HeartbeatsCtr];
    
	QRSLoopVector_XY[0,1,2] = All_QRS_AxisVectorsX[HeartbeatsCtr], All_QRS_AxisVectorsY[HeartbeatsCtr];
	QRSLoopVector_XZ[0,1,2] = All_QRS_AxisVectorsX[HeartbeatsCtr], All_QRS_AxisVectorsZ[HeartbeatsCtr];
	QRSLoopVector_ZY[0,1,2] = All_QRS_AxisVectorsY[HeartbeatsCtr], All_QRS_AxisVectorsZ[HeartbeatsCtr];
    //Find angles between two axis in three planes
    A_F = acos(dot(TLoopVector_XY,QRSLoopVector_XY)/norm(TLoopVector_XY)/norm(QRSLoopVector_XY)); 
    A_H = acos(dot(TLoopVector_XZ,QRSLoopVector_XZ)/norm(TLoopVector_XZ)/norm(QRSLoopVector_XZ)); 
    A_LS = acos(dot(TLoopVector_ZY,QRSLoopVector_ZY)/norm(TLoopVector_ZY)/norm(QRSLoopVector_ZY));
    //Find the greatest angle
	max = 0;
	if (A_F>A_H){max = A_F;}
	else max= A_H;
	if (max<A_LS){max=A_LS;}

    mMA[HeartbeatsCtr] = max * 180 / 3.14159265;  //rad to deg
}

ResultmMA = mean(wsk_mMA);
ResultmMA_std = stddev(wsk_mMA);


//-------------------------LICZENIE PARAMETR”W------------------------------
//---------RMMV tj. the ratio of maximum to mean vector magnitudes----------

//Variables' values are calculated in MA algorithm:

vector <double> mRMMV; 
vector < double >::iterator wsk_mRMMV = mRMMV.begin();
double Vmax;
double Vn;  
double ResultmRMMV, ResultmRMMV_std;

for (HeartbeatsCtr = 0;  HeartbeatsCtr < HeartbeatsAmount; HeartbeatsCtr++){
	Vmax = All_T_AxisModules[HeartbeatsCtr];  
    Vn = T_LoopsModulesMeans[HeartbeatsCtr];  
    mRMMV[HeartbeatsCtr] = Vmax/Vn;
}

ResultmRMMV = mean(wsk_mRMMV);
ResultmRMMV_std = stddev(wsk_mRMMV);


// przypisanie wartoúci do mMA, mRMMV
param["mMA"] = ResultmMA;
param["mRMMV"] = ResultmRMMV;

res->parameters=param;

//wpisanie wektorÛw XYZ do ResultVCG
XYZ['X'].resize(800);
XYZ['Y'].resize(800);
XYZ['Z'].resize(800);

res->VCG=XYZ;


return res;
}