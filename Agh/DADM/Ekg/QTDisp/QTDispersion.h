#ifndef QTDISPERSION_H
#define QTDISPERSION_H


#include <vector>
#include <iostream>
#include <AbstractModule.h>
#include <QTDisp.h>



using namespace std;

		class qt_disp : public AbstractModule<QTDispResult>
		{

		public:

			QTDispResult* compute(ResultKeeper* rkp);
			QTDispResult* run(unsigned int,vector<unsigned int>, vector<unsigned int> , vector < vector < double > >, int) const;
			//QTDisp* run(unsigned int channel, map<std::string, vector<unsigned int>*> &wavesResult,vector<double> *signal, int samplingFrequency) const;

            unsigned int channelsNumber;

			unsigned int tPeakSearchRange;
			unsigned int intervalBeforeTEndGlobal;
			unsigned int parabolaFittingPointsNumber;
			unsigned int tPeakSearchVectorLength;
			unsigned int mspSearchVectorLength;
			unsigned int tPeak;
			unsigned int msp;

			unsigned int qtDistanceMeanForSingleChannel;
			unsigned int iqrDispersion;
			unsigned int qtMeanOneChannel;
			vector<unsigned int> tEndLocalOneChannel;
			vector<double> *differentiatedDataPointer;
			vector<double> *differentiatedAbsoluteDataPointer;
			vector<double> *tPeakSearchVectorPointer;
			vector<unsigned int> *mspVectorPointer;
			vector<unsigned int> *parabolaXPointer;
			vector<double> *parabolaYPointer;
			vector<unsigned int> *tEndLocalPointer;
			vector<vector<unsigned int> > *tEndLocalPointerAllChannels;
			vector<unsigned int> *qtDistancePointer;
			vector<unsigned int> *qtDistancePointerMeanForAllChannels;
			vector<unsigned int> *qtDistancePointerMeanForAllChannels_COPY;
			vector<double> *parabolaPeakSearchVectorPointer;
			vector<double> *parabolaPointsPointer;
			vector<double> *parabolaCoefficientsPointer;
			vector<vector<double> > *filteredDataPointerAllChannels;


			void diff(const vector<double>*, vector<double>*);
			void abs(vector<double>*, vector<double>*);
			unsigned int min(vector<double>*);
			unsigned int max(vector<double>*);
			void parabolaFitting(vector<unsigned int>*, vector<double>*, const unsigned int, vector<double>*);
			unsigned int avg(vector<unsigned int>*);
			void sort(vector<unsigned int>*);
			unsigned int IQR(vector<unsigned int>*);
		};



#endif

