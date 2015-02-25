#include <iostream>
#include "TO.h"

#define NORMAL_VALUE 1.5

void TO::turbulenceOnsetEvaluation(std::vector<double> meanTachogram, static const int before){

	std::vector<double>::iterator T_it = meanTachogram.begin();
	this->TOvalue = 100*((*(T_it+before)+*(T_it+before+1)) - (*(T_it+before-1)+*(T_it+before-2)))/(*(T_it+before-1)+*(T_it+before-2));

	if(this->TOvalue > NORMAL_VALUE)
		this->TO_correct =false;
	else
		this->TO_correct=true;

}

void TO::show(){

	std::cout << "Wartosc parametru TO: "; std::cout << this->TOvalue;
	if(this->TO_correct==true)
		std::cout<<" jest poprawna." << std::endl << std::endl;
	else{
		std::cout <<" jest niepoprawna. Norma wynosi: "; std::cout << NORMAL_VALUE << std::endl << std::endl;
	}
}