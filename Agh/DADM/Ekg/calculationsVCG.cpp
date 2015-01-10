#include <vector>
#include <map>
#include <math.h>
#include <dataVCG.h>

using namespace std;

int main (){
	
int HeartbeatsCtr;
int HeartbeatsAmount= sizeof(AllX);    
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
//vector <double> Z; 
//for (HeartbeatsCtr = 0;  HeartbeatsCtr < AllSignalLength; HeartbeatsCtr++)
//{
//    Z[HeartbeatsCtr] = sqrt( AllX(HeartbeatsCtr)^2 + AllY(HeartbeatsCtr)^2 + AllZ(HeartbeatsCtr)^2);
//}

//[Nth, IsoelectricPoint_Idx] = min(Z);
//IsoelectricPoint = [AllX(IsoelectricPoint_Idx), AllY(IsoelectricPoint_Idx), AllZ(IsoelectricPoint_Idx)];

//TempDimention = size(QRS_ONSET);
//HeartbeatsAmount = TempDimention(1);

//==============================================================================================================

for (HeartbeatsCtr = 0;  HeartbeatsCtr < HeartbeatsAmount; HeartbeatsCtr++)
{
	double T_MaxModuleValue = 0; //Init maximum T loop's module value
    double T_ModulesSum = 0; //Init sum needed to count up the mean value (needed in RMMV)
	double dzielnik = 0;
	double T_AxisVector[3]={0,0,0};

    
	for (double TLoopPointsCtr = T_ONSET[HeartbeatsCtr]; TLoopPointsCtr < T_END[HeartbeatsCtr]; TLoopPointsCtr++)
	{
	//double This_Heartbeat_DEAs_Sum = 0; //We will need to sum all DEA to calculate the DEA mean
    double ThisPointVector [3];
	double ThisPointLSVector [2];
	double Z_axis_LSVector [2] = {0,1}; //[Y,Z]
	double X_axis_FVector [2] = {1,0}; //[X,Y]
	double Elevation;
	double normZ_axis_LSVector=1, normX_axis_FVector=1;  //!!!!!!!!!!!!!!!!!!!
	double norm_ThisPointLSVector=0.0667; //norm(ThisPointLSVector) !!!!!!!!!!!!!!!!obliczyc funkcja norm(ThisPointLSVector)
	double norm_ThisPointFVector=0.0371;//!!!!!!!!!!!!!!!!!!!!
	double Azimuth;
	double ThisPointModule;   
	double dot1;



	// ------------------------- T-LOOP -----------------------------------------
	double X = AllX[TLoopPointsCtr];
	double Y = AllY[TLoopPointsCtr];
	double Z = AllZ[TLoopPointsCtr];

	ThisPointModule = sqrt(pow(X-IsoelectricPoint[0],2) + pow(Y-IsoelectricPoint[1],2) + pow(Z-IsoelectricPoint[2],2)) ;
	 
	if (ThisPointModule>T_MaxModuleValue)
		{
			T_MaxModuleValue = ThisPointModule;
			T_AxisVector[0] = AllX[TLoopPointsCtr];
			T_AxisVector[1] = AllY[TLoopPointsCtr];
			T_AxisVector[2] = AllZ[TLoopPointsCtr];
		}
        T_ModulesSum = T_ModulesSum + ThisPointModule; //(needed in RMMV)
        
        //Meanwhile do some calculcations for DEA:
        ThisPointVector[0] = AllX[TLoopPointsCtr];
		ThisPointVector[1] = AllY[TLoopPointsCtr]; 
		ThisPointVector[2] = AllZ[TLoopPointsCtr];
		ThisPointLSVector[0,1] = ThisPointVector[2], ThisPointVector[3]; //[Y,Z], LS - Left Sagittal plane
        
		
		dot1 = dot(ThisPointLSVector,Z_axis_LSVector);
        Elevation = acos(dot1/norm_ThisPointLSVector/normZ_axis_LSVector); 

		double ThisPointFVector [2] = {ThisPointVector[0], ThisPointVector[1]}; //[X,Y], F - Frontal plane
   
		dot1 = dot(ThisPointFVector,X_axis_FVector);
        Azimuth = acos(dot1/norm_ThisPointFVector/normX_axis_FVector); 
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
    
	map <char,double> QRS_AxisVector; //Init QRS loop axis vectors
	  QRS_AxisVector['x'] = 0;
      QRS_AxisVector['y'] = 0;
      QRS_AxisVector['z'] = 0;
    double QRS_MaxModuleValue = 0; //Init maximum QRS loop's module value
    
	for (double QRSLoopPointsCtr = QRS_ONSET[HeartbeatsCtr]; QRSLoopPointsCtr<QRS_END[HeartbeatsCtr]; QRSLoopPointsCtr++)
	{
	double X = AllX[QRSLoopPointsCtr];
	double Y = AllY[QRSLoopPointsCtr];
	double Z = AllZ[QRSLoopPointsCtr];

	double ThisPointModule = sqrt(pow(X-IsoelectricPoint[0],2) + pow(Y-IsoelectricPoint[1],2) + pow(Z-IsoelectricPoint[2],2)) ;

		 if (ThisPointModule>QRS_MaxModuleValue)
			{
			    QRS_MaxModuleValue = ThisPointModule;
				QRS_AxisVector ['x'] = AllX[QRSLoopPointsCtr];
				QRS_AxisVector ['y'] = AllY[QRSLoopPointsCtr];
				QRS_AxisVector ['z'] = AllZ[QRSLoopPointsCtr];
			}
	}
    
	
    All_QRS_AxisVectorsX[HeartbeatsCtr] = QRS_AxisVector['x'];
	All_QRS_AxisVectorsY[HeartbeatsCtr] = QRS_AxisVector['y'];
	All_QRS_AxisVectorsZ[HeartbeatsCtr] = QRS_AxisVector['z'];
	
}


//Calculate MA parameter for each heartbeat:

//"The angle between two lines is the angle between their direction vectors.
//The direction vectors of two lines can always be found by subtracting the 
//position vectors of two points on the line"
//http://www.mathworks.com/matlabcentral/newsreader/view_thread/276582

vector <double> mMA; //Init MA array !!!!!!!!!!!!!!!!!!!!!!!!!!!?????
vector < double >::iterator wsk_mMA = mMA.begin();
double Results_mMA;
double Results_mMA_std;

for (HeartbeatsCtr = 0;  HeartbeatsCtr < HeartbeatsAmount; HeartbeatsCtr++)
{//Calculate axis (as vectors)
	double TLoopVector[3] = {All_T_AxisVectorsX[HeartbeatsCtr],All_T_AxisVectorsY[HeartbeatsCtr],All_T_AxisVectorsZ[HeartbeatsCtr]};
	double TLoopVector_XY[2] = {TLoopVector[1], TLoopVector[2]};
	double TLoopVector_XZ[2] = {TLoopVector[1], TLoopVector[3]};
	double TLoopVector_ZY[2] = {TLoopVector[2], TLoopVector[3]};
    double QRSLoopVector[3] =  {All_QRS_AxisVectorsX[HeartbeatsCtr],All_QRS_AxisVectorsY[HeartbeatsCtr],All_QRS_AxisVectorsZ[HeartbeatsCtr]};
	double QRSLoopVector_XY[2] = {QRSLoopVector[1], QRSLoopVector[2]};
	double QRSLoopVector_XZ[2] = {QRSLoopVector[1], QRSLoopVector[3]};
	double QRSLoopVector_ZY[2] = {QRSLoopVector[2], QRSLoopVector[3]};
    //Find angles between two axis in three planes
    double A_F = acos(dot(TLoopVector_XY,QRSLoopVector_XY)/norm(TLoopVector_XY)/norm(QRSLoopVector_XY)); 
    double A_H = acos(dot(TLoopVector_XZ,QRSLoopVector_XZ)/norm(TLoopVector_XZ)/norm(QRSLoopVector_XZ)); 
    double A_LS = acos(dot(TLoopVector_ZY,QRSLoopVector_ZY)/norm(TLoopVector_ZY)/norm(QRSLoopVector_ZY));
    //Find the greatest angle
	double max = 0;
	if (A_F>A_H){max = A_F;}
	else max= A_H;
	if (max<A_LS){max=A_LS;}

    mMA[HeartbeatsCtr] = max * 180 / 3.14159265;  //rad to deg
}

Results_mMA = mean(wsk_mMA);
Results_mMA_std = stddev(wsk_mMA);


//-------------------------LICZENIE PARAMETR”W------------------------------
//---------RMMV tj. the ratio of maximum to mean vector magnitudes----------

//Variables' values are calculated in MA algorithm:

vector <double> mRMMV; //Init array of RMMVs,  ERROR: Expression must have constant value!!!!!
vector < double >::iterator wsk_mRMMV = mRMMV.begin();
double Vmax;
double Vn;  
double Results_mRMMV;
double Results_mRMMV_std;

for (HeartbeatsCtr = 0;  HeartbeatsCtr < HeartbeatsAmount; HeartbeatsCtr++)
{
	Vmax = All_T_AxisModules[HeartbeatsCtr];  
    Vn = T_LoopsModulesMeans[HeartbeatsCtr];  
    mRMMV[HeartbeatsCtr] = Vmax/Vn;
}

Results_mRMMV = mean(wsk_mRMMV);
Results_mRMMV_std = stddev(wsk_mRMMV);


//-------------------------LICZENIE PARAMETR”W------------------------------
//---------- DEA - T axis elevation and azimuth angle difference -----------

double Results_mDEA;
double Results_mDEA_std;

Results_mDEA = mean(wsk_DEA_EachLoopMeans);
Results_mDEA_std = stddev(wsk_DEA_EachLoopMeans);

	
	return 0;}