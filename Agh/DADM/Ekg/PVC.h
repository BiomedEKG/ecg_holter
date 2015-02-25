#include <vector>

struct Index{
			std::vector<double> PVCindex;
			std::vector<double> sampleIndex;
		};

struct inputSignal{
	struct Index indeks;
	std::vector< std::vector<double> > signal;
	std::vector< std::vector<double> > QRSclass;
	std::vector< std::vector<double> > tachogram;
	};

struct Artefacts{
	std::vector< std::vector<double> > accepted;
	std::vector< std::vector<double> > rejected;
	std::vector<double> meanTachogram;
};


class PVC{
private:
	struct inputSignal qqq;
	struct Artefacts www; 
	static int accepted_counter;
	static const int before = 6;
	static const int after = 22;
public:	
	friend class HRT;
	void findPVC(std::vector<double>, std::vector<double>);			//zwraca wektor z indeksami pobudzeñ; plus z indeksami próbek w wektorze wejœciowym
	void isolatePVC(std::vector<double>, std::vector<double>, std::vector<double>, double);

	void ArtefactsRemover(std::vector< std::vector<double> >, std::vector< std::vector<double> >);
	void show();
};