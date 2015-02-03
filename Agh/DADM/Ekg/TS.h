#include <vector>


class TS{
private:
	double TS_value;		//a
	double b;
	bool TScorrect;
	std::vector<double> Y;  //warto�ci y dw�ch punkt�w przez kt�re przechodzi prosta nachylenia
	std::vector<double> X;	//warto�ci x     ------------ || ---------------------------
	
public:
	friend class HRT;
	//methods
	void weightedLeastSquares(std::vector<double>, static const int);
	void turbulenceSlopeEvaluation();
	void show();


	void setY(std::vector<double> a){
		this->Y = a;
	}

	void setX(std::vector<double> a){
		this->X = a;
	}

	void setTS_value(double a){
		this->TS_value = a;
	}

	void setb(double b){
		this->b = b;
	}

	void setTScorrect(bool a){
		this->TScorrect = a;
	}

	std::vector<double> getY(){
		return Y;
	}

	std::vector<double> getX(){
		return X;
	}

	double getTS_value(){
		return TS_value;
	}

	double getb(){
		return b;
	}

	bool getTScorrect(){
		return TScorrect;
	}
};

