using namespace std;

class AbstractExtractor{
	public:
        vector<double> qrsOnset;
        vector<double> qrsEnd;
		vector<double> signal; 
        double numberOfQrs;

        AbstractExtractor(vector<double> qrsOnsetFromWaves, vector<double> qrsEndFromWaves, vector<double> signalFromEcgBaseline);
		vector<double> SignalExtractor(unsigned int qrsNumber);
};
