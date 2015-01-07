#include <stdio.h>
#include <gsl/gsl_block.h>
#include <vector>
#include <iostream>
#include <dataVCG.h>
#include <math.h>

using namespace std;

int main (){
	
double All_T_AxisVectors[13][3]; //Init array containing T endpoints coordinates
double All_T_AxisModules[13]; //Init array containing magnitudes of axis vectors (needed in RMMV)
double All_QRS_AxisVectors[13][3]; //same as above
double T_LoopsModulesMeans[13]; //Init array containing mean values for each loop (needed in RMMV)
double DEA_EachLoopMeans[13];
int HeartbeatsCtr;
int HeartbeatsAmount=50;    // takie strzelone!!!
double ElAz_Sum = 0; // We will need to sum all DEA to calculate the DEA mean

for (HeartbeatsCtr = 0;  HeartbeatsCtr < HeartbeatsAmount; HeartbeatsCtr++)
{

    //Find T axis vectors IN CURRENT HEARTBEAT
	double T_AxisVector [3]= {0, 0, 0}; //Init T loop axis vectors
    double T_MaxModuleValue = 0; //Init maximum T loop's module value
    double T_ModulesSum = 0; //Init sum needed to count up the mean value (needed in RMMV)
    double This_Heartbeat_DEAs_Sum = 0; //We will need to sum all DEA to calculate the DEA mean
    double ThisPointVector [3];
	double ThisPointLSVector [2];
	double Z_axis_LSVector [2] = {0,1}; //[Y,Z]
	double X_axis_FVector [2] = {1,0}; //[X,Y]
	double Elevation;
	double normZ_axis_LSVector=1, normX_axis_FVector=1;  //!!!!!!!!!!!!!!!!!!!
	double norm_ThisPointLSVector=0.0667; //norm(ThisPointLSVector) !!!!!!!!!!!!!!!!obliczyc funkcja norm(ThisPointLSVector)
	double norm_ThisPointFVector=0.0371;//!!!!!!!!!!!!!!!!!!!!
	double Azimuth;
	double dzielnik = 0;

	for (int TLoopPointsCtr = T_EdgesIndexes[HeartbeatsCtr][1]; TLoopPointsCtr < T_EdgesIndexes[HeartbeatsCtr][2]; TLoopPointsCtr++)
	{
	double ThisPointModule;   
	double dot1, dot2;

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
   
		dot2 = dot(ThisPointFVector,X_axis_FVector);
        Azimuth = acos(dot2/norm_ThisPointFVector/normX_axis_FVector); 
        ElAz_Sum = ElAz_Sum + abs(Elevation-Azimuth); //as DEA = mean(abs(El-Az)    
        dzielnik = dzielnik+1;   
   	}
	
	All_T_AxisVectors[HeartbeatsCtr][0] = T_AxisVector[0];
	All_T_AxisVectors[HeartbeatsCtr][1] = T_AxisVector[1];
	All_T_AxisVectors[HeartbeatsCtr][2] = T_AxisVector[2];
    All_T_AxisModules[HeartbeatsCtr] = T_MaxModuleValue; //(needed in RMMV)
    T_LoopsModulesMeans[HeartbeatsCtr] = T_ModulesSum/(T_EdgesIndexes[HeartbeatsCtr][2]-T_EdgesIndexes[HeartbeatsCtr][1]+1); //(needed in RMMV)
    DEA_EachLoopMeans[HeartbeatsCtr] = ElAz_Sum/dzielnik;  // (needed in DEA)
   
    
    //Find QRS axis vectors in current heartbeat
	double QRS_AxisVector[3] = {0, 0, 0}; //Init QRS loop vectors
    double QRS_MaxModuleValue = 0; //Init maximum QRS loop's module value
    
	for (int QRSLoopPointsCtr = QRS_EdgesIndexes[HeartbeatsCtr][1]; QRSLoopPointsCtr<QRS_EdgesIndexes[HeartbeatsCtr][2]; QRSLoopPointsCtr++)
	{
	double X = AllX[QRSLoopPointsCtr];
	double Y = AllY[QRSLoopPointsCtr];
	double Z = AllZ[QRSLoopPointsCtr];

	double ThisPointModule = sqrt(pow(X-IsoelectricPoint[0],2) + pow(Y-IsoelectricPoint[1],2) + pow(Z-IsoelectricPoint[2],2)) ;

		 if (ThisPointModule>QRS_MaxModuleValue)
			{
			    QRS_MaxModuleValue = ThisPointModule;
				QRS_AxisVector [0] = AllX[QRSLoopPointsCtr];
				QRS_AxisVector [1] = AllY[QRSLoopPointsCtr];
				QRS_AxisVector [2] = AllZ[QRSLoopPointsCtr];
			}
	}
    
	for (int i=0; i<3; i++)
	{
    All_QRS_AxisVectors[HeartbeatsCtr][i] = QRS_AxisVector[i];
	}
}


//Calculate MA parameter for each heartbeat:

//"The angle between two lines is the angle between their direction vectors.
//The direction vectors of two lines can always be found by subtracting the 
//position vectors of two points on the line"
//http://www.mathworks.com/matlabcentral/newsreader/view_thread/276582

double mMA[50]; //Init MA array !!!!!!!!!!!!!!!!!!!!!!!!!!!?????
double Results_mMA;
double Results_mMA_std;

for (HeartbeatsCtr = 0;  HeartbeatsCtr < HeartbeatsAmount; HeartbeatsCtr++)
{//Calculate axis (as vectors)
	double TLoopVector[3] = {All_T_AxisVectors[HeartbeatsCtr][0],All_T_AxisVectors[HeartbeatsCtr][1],All_T_AxisVectors[HeartbeatsCtr][2]};
	double TLoopVector_XY[2] = {TLoopVector[1], TLoopVector[2]};
	double TLoopVector_XZ[2] = {TLoopVector[1], TLoopVector[3]};
	double TLoopVector_ZY[2] = {TLoopVector[2], TLoopVector[3]};
    double QRSLoopVector[3] =  {All_QRS_AxisVectors[HeartbeatsCtr][0],All_QRS_AxisVectors[HeartbeatsCtr][1],All_QRS_AxisVectors[HeartbeatsCtr][2]};
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

Results_mMA = mean(mMA);
Results_mMA_std = stddev(mMA);


//-------------------------LICZENIE PARAMETRÓW------------------------------
//---------RMMV tj. the ratio of maximum to mean vector magnitudes----------

//Variables' values are calculated in MA algorithm:

double mRMMV[13]; //Init array of RMMVs,  ERROR: Expression must have constant value!!!!!
double Vmax;
double Vn;  

for (HeartbeatsCtr = 0;  HeartbeatsCtr < HeartbeatsAmount; HeartbeatsCtr++)
{
	Vmax = All_T_AxisModules[HeartbeatsCtr];  
    Vn = T_LoopsModulesMeans[HeartbeatsCtr];  
    mRMMV[HeartbeatsCtr] = Vmax/Vn;
}

double Results_mRMMV;
double Results_mRMMV_std;

Results_mRMMV = mean(mRMMV);
Results_mRMMV_std = stddev(mRMMV);


//-------------------------LICZENIE PARAMETRÓW------------------------------
//---------- DEA - T axis elevation and azimuth angle difference -----------

double Results_mDEA;
double Results_mDEA_std;

Results_mDEA = mean(DEA_EachLoopMeans);
Results_mDEA_std = stddev(DEA_EachLoopMeans);

	
	return 0;}