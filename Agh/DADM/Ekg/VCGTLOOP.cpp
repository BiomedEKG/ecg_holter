#include <math.h>
#include <methodsVCG.h>
#include <VCGTLOOP.h>
#include <ResultVCG.h>
 
using namespace std;
 
 
ResultVCG* VCGTLoop::compute (ResultKeeper *rkp)
{
// //obiekt zwracany res
// //ResultVCG *res = new ResultVCG();
 
 map <string,double> param;
 param["mMA"] = 0;
 param["mRMMV"] = 0;
 
 map <char,vector<double> > XYZ;
 XYZ['X'];
 XYZ['Y'];
 XYZ['Z'];
 
 vector <double> AllX, AllY, AllZ;
 
//Tutaj chcemy sobie wziac 8 przefiltrowanych przez ECGBaseline odprowadzen
vector<double> i =  rkp->getECGBaseline()->getSignalMap()["e1"];
vector<double> ii = rkp->getECGBaseline()->getSignalMap()["e2"];
vector<double> v1 = rkp->getECGBaseline()->getSignalMap()["v1"];
vector<double> v2 = rkp->getECGBaseline()->getSignalMap()["v2"];
vector<double> v3 = rkp->getECGBaseline()->getSignalMap()["v3"];
vector<double> v4 = rkp->getECGBaseline()->getSignalMap()["v4"];
vector<double> v5 = rkp->getECGBaseline()->getSignalMap()["v5"];
vector<double> v6 = rkp->getECGBaseline()->getSignalMap()["v6"];
 
 
 
//A tutaj chcemy wziac wiadomo co, bo jest napisane, od Waves
vector<int> QRS_ONSET = rkp->getWaves()->getResult()->GetWavesResultData()["QRS_ONSET"]; //INDEKSY!!!!!!!!!!!!!!!!!!!!! a nie wartoœci
vector<int> QRS_END = rkp->getWaves()->getResult()->GetWavesResultData()["QRS_END"]; //INDEKSY!!!!!!!!!!!!!!!!!!!!!
vector<int> T_ONSET = rkp->getWaves()->getResult()->GetWavesResultData()["T_ONSET"]; //INDEKSY!!!!!!!!!!!!!!!!!!!!!
vector<int> T_END = rkp->getWaves()->getResult()->GetWavesResultData()["T_END"]; //INDEKSY!!!!!!!!!!!!!!!!!!!!!
 
int HeartbeatsCtr;
int HeartbeatsAmount;
int AllSignalLength;
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
 
vector <double> Z; // do punktu izoelektrycznego
double IsoelectricPoint[3];
double minZ;
 
//Calculate MA parameter for each heartbeat:
vector <long double> mMA;
vector < long double >::iterator wsk_mMA = mMA.begin();
 
long double ResultmMA, ResultmMA_std;
double A_F, A_H, A_LS, max;
 
//-------------------------LICZENIE PARAMETRÓW------------------------------
//---------RMMV tj. the ratio of maximum to mean vector magnitudes----------
 
vector <double> mRMMV;
vector < double >::iterator wsk_mRMMV = mRMMV.begin();
double Vmax;
double Vn;
double ResultmRMMV, ResultmRMMV_std;
 
 
// FUNCTIONS =========================================================================================
 
XYZ = DowerTransform ( i, ii, v1, v2, v3, v4, v5, v6);
int size = XYZ['Z'].size();
AllX.resize(size);
AllY.resize(size);
AllZ.resize(size);
AllX = XYZ['X'];
AllY = XYZ['Y'];
AllZ = XYZ['Z'];
 
 
 
HeartbeatsAmount = QRS_ONSET.size();
AllSignalLength = size;
 
//-----ZnajdŸmy punkt izoelektryczny w calym VCG:---------------------------
 
 
IsoelectricPoint[0] = AllX[0];
IsoelectricPoint[1] = AllY[0];
IsoelectricPoint[2] = AllZ[0];
minZ= sqrt(AllX[0]*AllX[0] + AllY[0]*AllY[0] + AllZ[0]*AllZ[0]);  // Z[0]
double previousZ = 1000; //init with big value
 
Z.resize(AllSignalLength);
for (HeartbeatsCtr = 0;  HeartbeatsCtr < AllSignalLength; HeartbeatsCtr++){
        Z[HeartbeatsCtr] = sqrt(AllX[HeartbeatsCtr]*AllX[HeartbeatsCtr] + AllY[HeartbeatsCtr]*AllY[HeartbeatsCtr] + AllZ[HeartbeatsCtr]*AllZ[HeartbeatsCtr]);
        if ((previousZ>Z[HeartbeatsCtr]) & (minZ>Z[HeartbeatsCtr])){
                IsoelectricPoint[0]=AllX[HeartbeatsCtr];
                IsoelectricPoint[1]=AllY[HeartbeatsCtr];
                IsoelectricPoint[2]=AllZ[HeartbeatsCtr];
 
            minZ = Z[HeartbeatsCtr];
        }
        previousZ = Z[HeartbeatsCtr];
}
 
//==============================================================================================================
 
        All_T_AxisVectorsX.resize(HeartbeatsAmount);
        All_T_AxisVectorsY.resize(HeartbeatsAmount);
        All_T_AxisVectorsZ.resize(HeartbeatsAmount);
    All_T_AxisModules.resize(HeartbeatsAmount);
    T_LoopsModulesMeans.resize(HeartbeatsAmount);
    DEA_EachLoopMeans.resize(HeartbeatsAmount);
        All_QRS_AxisVectorsX.resize(HeartbeatsAmount);
        All_QRS_AxisVectorsY.resize(HeartbeatsAmount);
        All_QRS_AxisVectorsZ.resize(HeartbeatsAmount);
 
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
 
        for (LoopPointsCtr = T_ONSET[HeartbeatsCtr]; LoopPointsCtr < T_END[HeartbeatsCtr]; LoopPointsCtr++)     {
 
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
                ThisPointLSVector[0] = ThisPointVector[2]; //[Y,Z], LS - Left Sagittal plane
                ThisPointLSVector[1] = ThisPointVector[3]; //[Y,Z], LS - Left Sagittal plane
 
 
                dot1 = dot(ThisPointLSVector,Z_axis_LSVector);
       Elevation = acos(dot1/norm(ThisPointLSVector)/norm(Z_axis_LSVector));
 
                ThisPointFVector [0]= ThisPointVector[0]; //[X,Y], F - Frontal plane
                ThisPointFVector [1]= ThisPointVector[1]; //[X,Y], F - Frontal plane
 
                dot1 = dot(ThisPointFVector,X_axis_FVector);
        Azimuth = acos(dot1/norm(ThisPointFVector)/norm(X_axis_FVector));
        ElAz_Sum = ElAz_Sum + fabs(Elevation-Azimuth); //as DEA = mean(abs(El-Az)
        dzielnik = dzielnik+1;
        }
       
        All_T_AxisVectorsX[HeartbeatsCtr] = T_AxisVector[0];
        All_T_AxisVectorsY[HeartbeatsCtr] = T_AxisVector[1];
        All_T_AxisVectorsZ[HeartbeatsCtr] = T_AxisVector[2];
    All_T_AxisModules[HeartbeatsCtr] = T_MaxModuleValue; //(needed in RMMV)
    T_LoopsModulesMeans[HeartbeatsCtr] = T_ModulesSum/(T_END[HeartbeatsCtr]-T_ONSET[HeartbeatsCtr]+1); //(needed in RMMV)
    DEA_EachLoopMeans[HeartbeatsCtr] = ElAz_Sum/dzielnik;  // (needed in DEA)
 
 
// ------------------------- QRS-LOOP -----------------------------------------
 
        if (QRS_ONSET[HeartbeatsCtr] = QRS_END[HeartbeatsCtr]){ QRS_END[HeartbeatsCtr]=QRS_END[HeartbeatsCtr]+1;}
 
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
 
mMA.resize(HeartbeatsAmount);
double TLoopVector_XY [2];
double TLoopVector_XZ [2];
double TLoopVector_ZY [2];
double QRSLoopVector_XY [2];
double QRSLoopVector_XZ [2];
double QRSLoopVector_ZY [2];
 
max = 0;
for (HeartbeatsCtr = 0;  HeartbeatsCtr < HeartbeatsAmount; HeartbeatsCtr++){
 
        //Calculate axis (as vectors)
        TLoopVector_XY[0]= All_T_AxisVectorsX[HeartbeatsCtr];
        TLoopVector_XY[1]= All_T_AxisVectorsY[HeartbeatsCtr];
        TLoopVector_XZ[0] = All_T_AxisVectorsX[HeartbeatsCtr];
        TLoopVector_XZ[1] = All_T_AxisVectorsZ[HeartbeatsCtr];
        TLoopVector_ZY[0] = All_T_AxisVectorsY[HeartbeatsCtr];
        TLoopVector_ZY[1] = All_T_AxisVectorsZ[HeartbeatsCtr];
 
        QRSLoopVector_XY[0] = All_QRS_AxisVectorsX[HeartbeatsCtr];
        QRSLoopVector_XY[1] = All_QRS_AxisVectorsY[HeartbeatsCtr];
        QRSLoopVector_XZ[0] = All_QRS_AxisVectorsX[HeartbeatsCtr];
        QRSLoopVector_XZ[1] = All_QRS_AxisVectorsZ[HeartbeatsCtr];
        QRSLoopVector_ZY[0] = All_QRS_AxisVectorsY[HeartbeatsCtr];
        QRSLoopVector_ZY[1] = All_QRS_AxisVectorsZ[HeartbeatsCtr];
    //Find angles between two axis in three planes
 
    A_F = acos(dot(TLoopVector_XY,QRSLoopVector_XY)/norm(TLoopVector_XY)/norm(QRSLoopVector_XY));
    A_H = acos(dot(TLoopVector_XZ,QRSLoopVector_XZ)/norm(TLoopVector_XZ)/norm(QRSLoopVector_XZ));
    A_LS = acos(dot(TLoopVector_ZY,QRSLoopVector_ZY)/norm(TLoopVector_ZY)/norm(QRSLoopVector_ZY));
   
        //Find the greatest angle
        if (A_F>A_H){max = A_F;}
        else max= A_H;
        if (max<A_LS){max=A_LS;};
       
    mMA[HeartbeatsCtr] = max * 180 / 3.14159265;  //rad to deg
       
 
}
 
ResultmMA = 0;
for (HeartbeatsCtr = 0; HeartbeatsCtr < mMA.size()-1; HeartbeatsCtr++)
{
        ResultmMA = ResultmMA + mMA[HeartbeatsCtr];
}
ResultmMA = ResultmMA/HeartbeatsAmount;
 
//-------------------------LICZENIE PARAMETRÓW------------------------------
//---------RMMV tj. the ratio of maximum to mean vector magnitudes----------
//Variables' values are calculated in MA algorithm:
 
mRMMV.resize(HeartbeatsAmount);
for (HeartbeatsCtr = 0;  HeartbeatsCtr < HeartbeatsAmount; HeartbeatsCtr++){
        Vmax = All_T_AxisModules[HeartbeatsCtr];
    Vn = T_LoopsModulesMeans[HeartbeatsCtr];
    mRMMV[HeartbeatsCtr] = Vmax/Vn;
}
 
ResultmRMMV= 0;
for (HeartbeatsCtr = 0; HeartbeatsCtr < mRMMV.size(); HeartbeatsCtr++)
{
        ResultmRMMV = ResultmRMMV + mRMMV[HeartbeatsCtr];
}
ResultmRMMV = ResultmRMMV/HeartbeatsAmount;
 
// przypisanie wartosci do mMA, mRMMV
param["mMA"] = ResultmMA;
param["mRMMV"] = ResultmRMMV;
ResultVCG b = ResultVCG();
b.parameters=param;
 
//wpisanie wektorów XYZ do ResultVCG
XYZ['X'].resize(800);
XYZ['Y'].resize(800);
XYZ['Z'].resize(800);
 
b.VCG=XYZ;
 
 
return b.getResult();
}