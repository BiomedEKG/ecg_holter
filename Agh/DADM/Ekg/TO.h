#ifndef TO_H_
#define TO_H_
#include <vector>

class TO{
	
private:

	double TOvalue;
	bool TO_correct;
	//methods:

public:
	friend class HRT;
	void turbulenceOnsetEvaluation(std::vector<double> meanTachogram, const int before);
	void show();

	void setTOvalue(double a){
		this->TOvalue = a;
	}

	void setTO_correct(double a){
		this->TO_correct=a;
	}

	double getTOvalue(){
		return TOvalue;
	}

	bool getTO_correct(){
		return TO_correct;
	}

};
#endif // !TO_H_