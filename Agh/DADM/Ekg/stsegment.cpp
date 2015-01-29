#include "stsegment.h"
//#include "stdafx.h"
#include <math.h>

// czêstotliwoœæ w Hercach
vector<unsigned int> STSegment:: computeJ20  ( )
{
	int ms20= (double)(Frequency*0.001*20);
	//int ms20= 2;
	
	vector <unsigned int> J20;
	
	for(int i=0; i<SizeVector;i++)
	{
		J20.push_back(QRSend[i]+ms20);
	}
	
	return J20;
}

vector<double> STSegment:: computeSlope (vector<unsigned int> TE)
{
	vector <double> Slope;
	
	for(int i=0; i<SizeVector;i++)
	{
		Slope.push_back((Signal[TE[i]]-Signal[J20[i]])/(TE[i]-J20[i]));		
	}
	return Slope;
}


vector<unsigned int> STSegment :: computeMaxDistanceIndex (vector <double> Slope,  vector<unsigned int> TE,
														   vector<double>& MaxDistance)
{
	int Size,End,IndeksMax;
	double distance_numerator, distance_denumerator;
	
	vector <unsigned int> MaxDistanceIndex;
	
	for(int i=0; i<TE.size(); i++)
	{
		vector <double> Distance;
		
		Size=TE[i]-J20[i];
		End=Size;
		
		distance_denumerator=sqrt(1+Slope[i]*Slope[i]);
		for (int j=0; j<=Size;j++)
		{
			distance_numerator= abs(-Slope[i]*j+1*Signal[J20[i]+j]-Signal[J20[i]]);
			Distance.push_back(distance_numerator/distance_denumerator);
		}

		vector<double>::iterator result;
		result=max_element(Distance.begin(), Distance.end());
		
		MaxDistance.push_back(*result);
		IndeksMax=distance(Distance.begin(), result);
		MaxDistanceIndex.push_back(J20[i]+IndeksMax);
			
	}

	return MaxDistanceIndex; //Ton 
}

vector<string> STSegment :: defineOffsetLevel ( )
{
	unsigned int JX;
	double offset; 
	unsigned int time;
	vector <string> OffsetLevel;
	//double hr=110;
	for(int i=0; i<SizeVector;i++)
	{
		if(HeartRate[i]<100) time=(double)(Frequency*0.001*80);
		else if (HeartRate[i]>=100||HeartRate[i]<110) time=(double)(Frequency*0.001*72);
		else if (HeartRate[i]>=110||HeartRate[i]<120) time=QRSend[i]+(double)(Frequency*0.001*64);
		else  time=(double)(Frequency*0.001*60);

		JX=QRSend[i]+time;
		
		offset=Signal[JX]-Signal[QRSonset[i]];	
		
		if(offset<k1offset) OffsetLevel.push_back("lower");
		else if(offset>k2offset) OffsetLevel.push_back("higher");
		else OffsetLevel.push_back("normal");
	}
	return OffsetLevel;
}

//
vector<double> STSegment :: correctSlopeorMaxDistanceForShapeST (vector <double> StraightTpeak,vector <double> StraighTon)
{
	vector <double> ForShapeST;
	for(int i=0;i<SizeVector;i++)
	{
		if(OffsetLevel[i]=="higher") ForShapeST.push_back(StraightTpeak[i]);
		else ForShapeST.push_back(StraighTon[i]);
	}

	return ForShapeST;
}

vector<unsigned int> STSegment :: correctTEForShapeST ()
{
	vector <unsigned int> ForShapeST;
	for(int i=0;i<OffsetLevel.size();i++)
	{
		if(OffsetLevel[i]=="higher") ForShapeST.push_back(Ton[i]);
		else ForShapeST.push_back(TMax[i]);
	}

	return ForShapeST;

}

vector<string> STSegment :: defineShapeST ()
{
	
	vector<string> ShapeST;
	for(int i=0; i<SizeVector;i++)
	{
		if(MaxDistanceShapeSKST[i]<=threshold) ShapeST.push_back("straight");
		else ShapeST.push_back("curve");
	}
	return ShapeST;
}



vector<string> STSegment :: defineTypeShapeST ()
{
	vector <string> TypeShapeST;
	unsigned int difference,above,below;
	double straight;
	for(int i =0; i<SizeVector;i++)
	{
		if(ShapeST[i]=="curve")
		{
			above=0,below=0;
			difference=TE[i]-J20[i];
			for(int j=0;j<=difference;j++)
			{
				
				straight=SlopeSKST[i]*j+Signal[J20[i]];
				if(straight>Signal[J20[i]+j]) above++;
				else if(straight<Signal[J20[i]+j]) below++;
			}
			
			if((above/(difference+1))>=0.7) TypeShapeST.push_back("convex");
			else if((below/(difference+1))>=0.7) TypeShapeST.push_back("concave");
			else TypeShapeST.push_back("not defined");	
		}
		
		else
		{
			if(SlopeSKST[i]<k1slope) TypeShapeST.push_back("downward");
			else if (SlopeSKST[i]>k2slope) TypeShapeST.push_back("upward");
			else TypeShapeST.push_back("horizon");
		}
	}
	
	return TypeShapeST;
}

vector <double> STSegment :: computeHeartRate ()

{
	vector<double> HeartRate;
	
	int i;
	for(i=0; i<(QRSend.size()-1);i++)
	{
		HeartRate.push_back(60/((Rpeak[i+1]-Rpeak[i])*(1/Frequency)));
	}
	HeartRate.push_back(HeartRate[HeartRate.size()-1]);
	
	return HeartRate;
}

void STSegment :: Run()
{
	HeartRate=computeHeartRate();
	J20=computeJ20();
	SlopeTpeak=computeSlope(Tpeak);
	Ton=computeMaxDistanceIndex (SlopeTpeak, Tpeak, MaxDistanceTpeak);
	OffsetLevel=defineOffsetLevel ();
	SlopeTon=computeSlope(Ton);
	TMax=computeMaxDistanceIndex (SlopeTon, Ton, MaxDistanceTon);
	TE=correctTEForShapeST();
	SlopeSKST=correctSlopeorMaxDistanceForShapeST(SlopeTpeak, SlopeTon);
	MaxDistanceShapeSKST=correctSlopeorMaxDistanceForShapeST(MaxDistanceTpeak, MaxDistanceTon);
	ShapeST=defineShapeST ();
	TypeShapeST=defineTypeShapeST();
}

void STSegment :: CorrectSize()
{
	vector<int> Size;
	Size.push_back(QRSonset.size());
	Size.push_back(QRSend.size());
	Size.push_back(Tpeak.size());
	Size.push_back(Rpeak.size());
	SizeVector=min_element(begin(Size), end(Size));
}

STSegmentResult STSegment:: compute(map <string, vector<unsigned int> >*resultFromWaves, vector<double>*signal,
									vector<unsigned int>*Rpeaks)
{
	this->Signal= *signal;	
	this->Frequency=Frequency;
	
	this->QRSonset= resultFromWaves["QRSonset"]; 
	this->QRSend=*resultFromWaves["QRSend"];  
	this->Tpeak=*resultFromWaves["Tpeak"]; 
	this->Rpeak=*Rpeaks;
	k1offset=-0.1;
	k2offset=0.1;
	threshold=0.15;
	k1slope=-0.15;
	k2slope=0.15;
	CorrectSize();
	Run();
	STSegmentResult p(OffsetLevel,ShapeST,TypeShapeST);
	return p;
}


STSegment::STSegment (vector<double> Signal, int Frequency, vector<unsigned int> QRSonset, vector<unsigned int> QRSend, 
					  vector<unsigned int> Tpeak,vector <unsigned int> Rpeak)
	
   
{
	this->Signal=Signal;
	this->Frequency=Frequency;
	this->QRSonset= QRSonset; 
	this->QRSend=QRSend;  
	this->Tpeak=Tpeak; 
	this->Rpeak=Rpeak;
	k1offset=-0.1;
	k2offset=0.1;
	threshold=0.15;
	k1slope=-0.15;
	k2slope=0.15;
			
}

STSegmentResult::STSegmentResult(vector<string> OffsetLevel, vector<string>ShapeST, vector <string> TypeShapeST)
{
	this->OffsetLevel=OffsetLevel;
	this->ShapeST=ShapeST;
	this->TypeShapeST=TypeShapeST;
}