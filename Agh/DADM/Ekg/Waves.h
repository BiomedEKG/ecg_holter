#include <map>
#include<vector>
#include<string>
using namespace std;

class Waves{
private:

	map <string, vector<int>> WavesData;
public:
	map <string, vector<int>> Compute(vector<double>* resultFromECKBaseline, vector<double>* resultFromRPeaks);

};