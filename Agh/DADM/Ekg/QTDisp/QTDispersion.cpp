#include "QTDISP.h"



		QTDisp :: QTDisp(unsigned int _iqrDispersion) : iqrDispersion(_iqrDispersion)
		{
		}


		qt_disp :: qt_disp() : AbstractModule(Parameters())
		{
			this->tPeakSearchRange = 0;
			this->intervalBeforeTEndGlobal = 0;
			this->parabolaFittingPointsNumber = 0;
			this->tPeakSearchVectorLength = 0;
			this->mspSearchVectorLength = 0;
			this->tPeak = 0;
		    this->msp = 0;
			this->qtDistanceMeanForSingleChannel = 0;
			this->iqrDispersion = 0;
			this->channelsNumber = 12;
			this->qtMeanOneChannel = 0;
			this->differentiatedDataPointer = NULL;
			this->differentiatedAbsoluteDataPointer = NULL;
			this->tPeakSearchVectorPointer = NULL;
			this->mspVectorPointer = NULL;
			this->parabolaXPointer = NULL;
			this->parabolaYPointer = NULL;
			this->tEndLocalPointer = NULL;
			this->tEndLocalPointerAllChannels = NULL;
			this->qtDistancePointer = NULL;
			this->qtDistancePointerMeanForAllChannels = NULL;
			this->qtDistancePointerMeanForAllChannels_COPY = NULL;
			this->parabolaPeakSearchVectorPointer = NULL;
			this->parabolaPointsPointer = NULL;
			this->parabolaCoefficientsPointer = NULL;
			this->filteredDataPointerAllChannels = NULL;
		}

		void qt_disp :: diff(const vector<double>* filteredDataPointer, vector<double> *differentiatedDataPointer)
		{

			differentiatedDataPointer->push_back(0);
			differentiatedDataPointer->push_back(0);
			for (unsigned int i=2; i<(filteredDataPointer->size()-2); ++i)
			{
				differentiatedDataPointer->push_back((-filteredDataPointer->at(i-2)-2*filteredDataPointer->at(i-1)+2*filteredDataPointer->at(i+1)+filteredDataPointer->at(i+2))/8);
			}
		}

		void qt_disp :: abs(vector<double> *differentiatedDataPointer, vector<double> *differentiatedAbsoluteDataPointer)
		{
			for (unsigned int i=0; i<differentiatedDataPointer->size(); ++i)
			{
				double element = differentiatedDataPointer->at(i);
				double elementAbsolute;
				if (element>=0)
				{
					elementAbsolute = element;
				}
				else
				{
					elementAbsolute = -element;
				}
				differentiatedAbsoluteDataPointer->push_back(elementAbsolute);
			}
		}

		unsigned int qt_disp :: min(vector<double> *tPeakSearchVectorPointer)
		{
			double minValue = tPeakSearchVectorPointer->at(0);
			unsigned int min = 0;
			for (unsigned int i=1; i<tPeakSearchVectorPointer->size(); ++i)
			{
				if (tPeakSearchVectorPointer->at(i)<minValue)
				{
					min = i;
					minValue = tPeakSearchVectorPointer->at(i);
				}
			}
			return min;
		}

		unsigned int qt_disp :: max(vector<double> *mspSearchVectorPointer)
		{
			double maxValue = mspSearchVectorPointer->at(0);
			unsigned int max = 0;
			for (unsigned int i=1; i<mspSearchVectorPointer->size(); ++i)
			{
				if (mspSearchVectorPointer->at(i)>maxValue)
				{
					max = i;
					maxValue = mspSearchVectorPointer->at(i);
				}
			}
			return max;
		}

		void qt_disp :: parabolaFitting(vector<unsigned int> *parabolaXPointer, vector<double> *parabolaYPointer, const unsigned int parabolaFittingPointsNumber, vector<double>* parabolaCoefficientsPointer)
		{
			unsigned int size = parabolaFittingPointsNumber;

			double **data;
			data = new double*[size];
			for(unsigned int i=0; i<size; ++i)
			{
				data[i] = new double[2];
			}

 			for (unsigned int i=0; i<size; ++i)
 			{
 				data[i][0] = parabolaXPointer->at(i);
				data[i][1] = parabolaYPointer->at(i);
 			}

 			double **transposeMatrix;
			transposeMatrix = new double*[3];
			for(unsigned int i=0; i<3; ++i)
			{
				transposeMatrix[i] = new double[size];
			}

			double **matrix;
			matrix = new double*[3];
			for(unsigned int i=0; i<3; ++i)
			{
				matrix[i] = new double[size];
			}

			double sumx4 = 0, sumx3 = 0, sumx2 = 0, sumx1 = 0, det, coefficients[3] = {0};

			for (unsigned int i=0; i<size; ++i)
			{
				sumx4 += data[i][0]*data[i][0]*data[i][0]*data[i][0];
				sumx3 += data[i][0]*data[i][0]*data[i][0];
				sumx2 += data[i][0]*data[i][0];
				sumx1 += data[i][0];

				transposeMatrix[2][i] = 1;
				transposeMatrix[1][i] = data[i][0];
				transposeMatrix[0][i] = data[i][0]*data[i][0];
			}

			det = (sumx4*sumx2*size)+(sumx3*sumx1*sumx2)+(sumx2*sumx3*sumx1)-(sumx2*sumx2*sumx2)-(sumx1*sumx1*sumx4)-(size*sumx3*sumx3);

			double inverseMatrix[3][3] =
			{
				{size*sumx2 - sumx1*sumx1, -(size*sumx3 - sumx1*sumx2), sumx1*sumx3-sumx2*sumx2},
				{-(size*sumx3-sumx2*sumx1), size*sumx4-sumx2*sumx2, -(sumx1*sumx4-sumx3*sumx2)},
				{sumx1*sumx3 - sumx2*sumx2, -(sumx1*sumx4 - sumx2*sumx3), sumx2*sumx4 - sumx3*sumx3}
			};

			for (int i=0; i<3; ++i)
			{
				for (unsigned int j=0; j<size; ++j)
				{
					matrix[i][j] = inverseMatrix[i][0]*transposeMatrix[0][j] + inverseMatrix[i][1]*transposeMatrix[1][j] + inverseMatrix[i][2]*transposeMatrix[2][j];
				}
			}

			for (int i=0; i<3; ++i)
			{
				for (unsigned int j=0; j<size; ++j)
				{
					coefficients[i] += matrix[i][j]*data[j][1];
				}
				coefficients[i] /= det;
			}

			parabolaCoefficientsPointer->at(0) = coefficients[0];
			parabolaCoefficientsPointer->at(1) = coefficients[1];
			parabolaCoefficientsPointer->at(2) = coefficients[2];

			for (unsigned int i=0; i<size; ++i)
			{
				delete [] data[i];
			}
			delete [] data;
			for (int i=0; i<3; ++i)
			{
				delete [] transposeMatrix[i];
			}
			delete [] transposeMatrix;
			for (int i=0; i<3; ++i)
			{
				delete [] matrix[i];
			}
			delete [] matrix;
		}

		unsigned int qt_disp :: avg(vector<unsigned int> *qtDistancePointer)
		{
			int sum = 0;
			for (unsigned int i=0; i<qtDistancePointer->size(); ++i)
			{
				sum = sum+qtDistancePointer->at(i);
			}

			return sum/(qtDistancePointer->size());
		}

		void qt_disp :: sort(vector<unsigned int> *qtDistancePointerMeanForAllChannels)
		{
			int i, j, p;
			bool k;
			k = true;
			i = qtDistancePointerMeanForAllChannels->size() - 1;
			while(k)
			{
			   k = false;
			   for(j=0; j<i; ++j)
			   if (qtDistancePointerMeanForAllChannels->at(j) > qtDistancePointerMeanForAllChannels->at(j+1))
			   {
				   p = qtDistancePointerMeanForAllChannels->at(j);
				   qtDistancePointerMeanForAllChannels->at(j) = qtDistancePointerMeanForAllChannels->at(j+1);
				   qtDistancePointerMeanForAllChannels->at(j+1) = p;
				   k = true;
			   }
		   }
		}

		unsigned int qt_disp :: IQR(vector<unsigned int> *qtDistancePointerMeanForAllChannels)
		{
			 int t = qtDistancePointerMeanForAllChannels->size()/2;
			 int t2 = t/2;
			 float med1;
			 float med3;

			 if (channelsNumber%2 == 0)
			 {
				 int med2 = (qtDistancePointerMeanForAllChannels->at(t-1)+qtDistancePointerMeanForAllChannels->at(t))/2;
				 if (t%2 == 0)
				 {
					 med1 = (float)  (qtDistancePointerMeanForAllChannels->at(t2-1)+qtDistancePointerMeanForAllChannels->at(t2))/2;
					 med3 = (float) (qtDistancePointerMeanForAllChannels->at(t2-1+t)+qtDistancePointerMeanForAllChannels->at(t2+t))/2;
				 }
				 else
				 {
					 med1 =  (float) qtDistancePointerMeanForAllChannels->at(t2);
					 med3 =  (float) qtDistancePointerMeanForAllChannels->at(t2+t);
				 }
			 }
			 else
			 {
				 int med2 = qtDistancePointerMeanForAllChannels->at(t);
				 if (t%2 == 0)
				 {
					 med1 =  (float) (qtDistancePointerMeanForAllChannels->at(t2-1)+qtDistancePointerMeanForAllChannels->at(t2))/2;
					 med3 =  (float) (qtDistancePointerMeanForAllChannels->at(t2+t)+qtDistancePointerMeanForAllChannels->at(t2+t+1))/2;
				 }
				 else
				 {
					 med1 =  (float) qtDistancePointerMeanForAllChannels->at(t2);
					 med3 =  (float) qtDistancePointerMeanForAllChannels->at(t2+t+1);
				 }
			 }

			unsigned int IQR = med3-med1;
			return IQR;
		}

		//Wyciąganie danych - pytanie czy dobre nazwy zmiennych odprowadzen? (tzn, i, ii, aVr itd....)
		
		QTDisp* compute(ResultKeeper* rkp) {
			//Waves* resultWaves = rkp->getResultFromWaves();
			//map<std::string, vector<unsigned int>*> resultWaves = rkp->getResultFromWaves();
			//this->QRSonset_=(*resultWaves)["QRS_ONSET"];
			//this->tPeak=(*resultWaves)["T_END"]; 
			vector<double> QRSonset = rkp->QRS_ONSET; 
			vector<double> tPeak = rkp->T_END; 


			//ECGBaseline* resultECGBaseline = rkp->getResultFrom_ECGBaseline();
			//this->Signal= rkp->getResultFrom_ECGBaseline();

			const unsigned int samplingFrequency = rkp->samplingFrequency;

			vector<double> Signal1 = rkp->i; 
			vector<double> Signal2 = rkp->ii;
			vector<double> Signal3 = rkp->iii;
			vector<double> Signal4 = rkp->aVf;
			vector<double> Signal5 = rkp->aVr;
			vector<double> Signal6 = rkp->aVl;
			vector<double> Signal7 = rkp->v1;
			vector<double> Signal8 = rkp->v2;
			vector<double> Signal5 = rkp->v3;
			vector<double> Signal6 = rkp->v4;
			vector<double> Signal7 = rkp->v5;
			vector<double> Signal8 = rkp->v6;

		}
		/*
		QTDisp qt_disp:: compute(map <string, vector<unsigned int> > *resultFromWaves, vector<double>*signal,int Frequency) {
				this->Signal= signal;	
				this->samplingFrequency=Frequency;
	
				this->QRSonset_= (*resultFromWaves)["QRS_ONSET"];  
				this->tPeak=(*resultFromWaves)["T_END"]; 
		}
		*/

		QTDisp* qt_disp :: run(unsigned int channel, map<std::string, vector<unsigned int>*> &wavesResult,vector<double> *signal, int samplingFrequency) const
		{

			qt_disp* QTDISP = new qt_disp();
			const unsigned int samplingFrequency = this->samplingFrequency;

			
			const vector<double>* input1 = this->Signal1;
			const vector<double>* input2 = this->Signal2;
			const vector<double>* input3 = this->Signal3;
			const vector<double>* input4 = this->Signal4;
			const vector<double>* input5 = this->Signal5;
			const vector<double>* input6 = this->Signal6;
			const vector<double>* input7 = this->Signal7;
			const vector<double>* input8 = this->Signal8;
			const vector<double>* input9 = this->Signal9;
			const vector<double>* input10 = this->Signal10;
			const vector<double>* input11 = this->Signal11;
			const vector<double>* input12 = this->Signal12;
		
			//const map<std::string, vector<unsigned int>*> &inputwavesMap = wavesResult;
			const vector<unsigned int> &qrsOnset_ =this->QRSonset_; // (*inputwavesMap)["QRS_ONSET"];
			const vector<unsigned int> &tEndGlobal_ =this->tPeak; // (*inputwavesMap)["T_END"];
			

			unsigned int sizeQrsOnsetVector = qrsOnset_.size();
			unsigned int sizeTEndGlobalVector = tEndGlobal_.size();
			vector<unsigned int> qrsOnset;
			vector<unsigned int> tEndGlobal;
			if (sizeQrsOnsetVector!=sizeTEndGlobalVector)
			{
				if (sizeQrsOnsetVector>sizeTEndGlobalVector)
				{
					unsigned int sizeDifference = sizeQrsOnsetVector-sizeTEndGlobalVector;
					qrsOnset = vector<unsigned int> (qrsOnset_.begin(), qrsOnset_.end()-sizeDifference);
					tEndGlobal = vector<unsigned int> (tEndGlobal_.begin(), tEndGlobal_.end());
				}
				else
				{
					unsigned int sizeDifference = sizeTEndGlobalVector-sizeQrsOnsetVector;
					qrsOnset = vector<unsigned int> (qrsOnset_.begin(), qrsOnset_.end());
					tEndGlobal = vector<unsigned int> (tEndGlobal_.begin()+sizeDifference, tEndGlobal_.end());
				}
			}
			else
			{
				qrsOnset = vector<unsigned int> (qrsOnset_.begin(), qrsOnset_.end());
				tEndGlobal = vector<unsigned int> (tEndGlobal_.begin(), tEndGlobal_.end());
			}

			vector<vector<double> > filteredDataAllChannels(QTDISP.channelsNumber);
			QTDISP.filteredDataPointerAllChannels = &filteredDataAllChannels;
			QTDISP.filteredDataPointerAllChannels->at(0) = *input1;
			QTDISP.filteredDataPointerAllChannels->at(1) = *input2;
			QTDISP.filteredDataPointerAllChannels->at(2) = *input3;
			QTDISP.filteredDataPointerAllChannels->at(3) = *input4;
			QTDISP.filteredDataPointerAllChannels->at(4) = *input5;
			QTDISP.filteredDataPointerAllChannels->at(5) = *input6;
			QTDISP.filteredDataPointerAllChannels->at(6) = *input7;
			QTDISP.filteredDataPointerAllChannels->at(7) = *input8;
			QTDISP.filteredDataPointerAllChannels->at(8) = *input9;
			QTDISP.filteredDataPointerAllChannels->at(9) = *input10;
			QTDISP.filteredDataPointerAllChannels->at(10) = *input11;
			QTDISP.filteredDataPointerAllChannels->at(11) = *input12;

			QTDISP.tPeakSearchRange = 0.150*samplingFrequency;
			QTDISP.intervalBeforeTEndGlobal = 0.080*samplingFrequency;
			QTDISP.parabolaFittingPointsNumber = 0.1*samplingFrequency;
			QTDISP.tPeakSearchVectorLength = QTDISP.tPeakSearchRange-QTDISP.intervalBeforeTEndGlobal+1;

			vector<double> tPeakSearchVector(QTDISP.tPeakSearchVectorLength);
			QTDISP.tPeakSearchVectorPointer = &tPeakSearchVector;
			vector<unsigned int> parabolaX(QTDISP.parabolaFittingPointsNumber);
			QTDISP.parabolaXPointer = &parabolaX;
			vector<double> parabolaY(QTDISP.parabolaFittingPointsNumber);
			QTDISP.parabolaYPointer = &parabolaY;
			vector<unsigned int> tEndLocal(tEndGlobal.size());
			QTDISP.tEndLocalPointer = &tEndLocal;
			vector<vector<unsigned int> > tEndLocalAllChannels;
			QTDISP.tEndLocalPointerAllChannels = &tEndLocalAllChannels;
			vector<unsigned int> qtDistanceMeanForAllChannels(QTDISP.channelsNumber);
			QTDISP.qtDistancePointerMeanForAllChannels = &qtDistanceMeanForAllChannels;
			vector<unsigned int> qtDistanceMeanForAllChannels_COPY(QTDISP.channelsNumber);
			QTDISP.qtDistancePointerMeanForAllChannels_COPY = &qtDistanceMeanForAllChannels_COPY;
			vector<double> parabolaPeakSearchVector;
			QTDISP.parabolaPeakSearchVectorPointer = &parabolaPeakSearchVector;
			vector<double> parabolaCoefficients(3);
			QTDISP.parabolaCoefficientsPointer = &parabolaCoefficients;


			for (int i=0; i<QTDISP.channelsNumber; ++i)
			{
				vector<double> filteredData = QTDISP.filteredDataPointerAllChannels->at(i);
				vector<double> *filteredDataPointer = &filteredData;
				vector<double> differentiatedData;
				QTDISP.differentiatedDataPointer = &differentiatedData;
				vector<double> differentiatedAbsoluteData;
				QTDISP.differentiatedAbsoluteDataPointer = &differentiatedAbsoluteData;
				vector<unsigned int> mspVector;
				QTDISP.mspVectorPointer = &mspVector;
				vector<unsigned int> qtDistance(tEndGlobal.size());
				QTDISP.qtDistancePointer = &qtDistance;

				QTDISP.diff(filteredDataPointer, QTDISP.differentiatedDataPointer);
				QTDISP.abs(QTDISP.differentiatedDataPointer, QTDISP.differentiatedAbsoluteDataPointer);

				for (int a=0; a<tEndGlobal.size(); ++a)
				{
					QTDISP.mspSearchVectorLength = 0;
					for (int j=0; j<QTDISP.tPeakSearchVectorLength; ++j)
					{
						QTDISP.tPeakSearchVectorPointer->at(j) = QTDISP.differentiatedAbsoluteDataPointer->at(tEndGlobal.at(a)-QTDISP.tPeakSearchRange+j);
					}

					QTDISP.tPeak = QTDISP.min(QTDISP.tPeakSearchVectorPointer);
					QTDISP.tPeak = QTDISP.tPeak+tEndGlobal.at(a)-QTDISP.tPeakSearchRange;
					for (int j=QTDISP.tPeak; j<=tEndGlobal.at(a); ++j)
					{
						QTDISP.mspSearchVectorLength = QTDISP.mspSearchVectorLength+1;
					}
					vector<double> mspSearchVector(QTDISP.mspSearchVectorLength);
					vector<double> *mspSearchVectorPointer = &mspSearchVector;
					for (int j=0; j<mspSearchVectorPointer->size(); ++j)
					{
						mspSearchVectorPointer->at(j) = QTDISP.differentiatedAbsoluteDataPointer->at(QTDISP.tPeak+j);
					}
					QTDISP.msp = QTDISP.max(mspSearchVectorPointer);
					QTDISP.mspVectorPointer->push_back(QTDISP.msp+QTDISP.tPeak);
				}

				for (int d=0; d<tEndGlobal.size(); ++d)
				{
					for (int j=0; j<QTDISP.parabolaFittingPointsNumber; ++j)
					{
						QTDISP.parabolaXPointer->at(j) = QTDISP.mspVectorPointer->at(d)+j;
						QTDISP.parabolaYPointer->at(j) = filteredDataPointer->at(QTDISP.mspVectorPointer->at(d)+j);
					}
					QTDISP.parabolaFitting(QTDISP.parabolaXPointer, QTDISP.parabolaYPointer, QTDISP.parabolaFittingPointsNumber, QTDISP.parabolaCoefficientsPointer);
					double a = QTDISP.parabolaCoefficientsPointer->at(0);
					double b = QTDISP.parabolaCoefficientsPointer->at(1);
					double c = QTDISP.parabolaCoefficientsPointer->at(2);

					vector<double> parabolaPeakSearchVector;
					QTDISP.parabolaPeakSearchVectorPointer = &parabolaPeakSearchVector;
					for (int k=QTDISP.mspVectorPointer->at(d); k<=tEndGlobal.at(d); ++k)
					{
						QTDISP.parabolaPeakSearchVectorPointer->push_back(k);
					}

					vector<double> parabolaPoints(QTDISP.parabolaPeakSearchVectorPointer->size());
					QTDISP.parabolaPointsPointer = &parabolaPoints;
					for (int l=0; l<QTDISP.parabolaPeakSearchVectorPointer->size(); ++l)
					{
						double x = QTDISP.parabolaPeakSearchVectorPointer->at(l);
						QTDISP.parabolaPointsPointer->at(l) = a*x*x+b*x+c;
					}

					if (a>0)
					{
						QTDISP.tEndLocalPointer->at(d) = QTDISP.min(QTDISP.parabolaPointsPointer)+QTDISP.mspVectorPointer->at(d);
					}
					else
					{
						QTDISP.tEndLocalPointer->at(d) = QTDISP.max(QTDISP.parabolaPointsPointer)+QTDISP.mspVectorPointer->at(d);
					}
				}

				QTDISP.tEndLocalPointerAllChannels->push_back(tEndLocal);

				for (int j=0; j<QTDISP.tEndLocalPointer->size(); ++j)
				{
					if (tEndLocal.at(j)>qrsOnset.at(j))
					{
						QTDISP.qtDistancePointer->at(j) = ((tEndLocal.at(j)-qrsOnset.at(j)-1)*1000)/samplingFrequency;
					}
					else
					{
						QTDISP.qtDistancePointer->at(j) = ((qrsOnset.at(j)-tEndLocal.at(j)-1)*1000)/samplingFrequency;
					}
				}
				QTDISP.qtDistanceMeanForSingleChannel = QTDISP.avg(QTDISP.qtDistancePointer);

				QTDISP.qtDistancePointerMeanForAllChannels->at(i) = QTDISP.qtDistanceMeanForSingleChannel;
			}

			qtDistanceMeanForAllChannels_COPY = qtDistanceMeanForAllChannels;
			QTDISP.sort(QTDISP.qtDistancePointerMeanForAllChannels);
			QTDISP.iqrDispersion = QTDISP.IQR(QTDISP.qtDistancePointerMeanForAllChannels);

			return new QTDisp(QTDISP.iqrDispersion);
		}


		qt_disp :: ~qt_disp()
		{
		}




