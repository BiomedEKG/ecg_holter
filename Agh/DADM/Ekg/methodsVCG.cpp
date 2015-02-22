#include "methodsVCG.h"
#include <math.h>


double dot(double *vector1, double *vector2){
	//int length = 2; //vectors have 3 elements each
	double a=0;
	for (int i=0; i<=1; i++){
        a = a + vector1[i]*vector2[i];
	}
	return a;
}

double norm(double *tab){
	double a=0;
	double b=0;
	double result = 0;
        a = tab[0]*tab[0];
		b = tab[1]*tab[1];
	result = a + b;
	result = sqrt(result);
	return result;
}

map<char, vector<double> > DowerTransform ( vector<double> i, vector<double> ii, vector<double> v1, vector<double> v2, vector<double> v3, vector<double> v4, vector<double> v5, vector<double> v6)
{
//Column order = t i ii iii avr avl avf v1 v2 v3 v4 v5 v6 x y z

map <char, vector<double> > VCG;
VCG['X'];
VCG['Y'];
VCG['Z'];
vector <double> VCG_X;
vector <double> VCG_Y;
vector <double> VCG_Z;
int signalLength = i.size();
VCG_X.resize(signalLength);
VCG_Y.resize(signalLength);
VCG_Z.resize(signalLength);

for (unsigned iter = 0; iter<signalLength; iter++){
	VCG_X [iter]= (-0.172*i[iter]) + (-0.074*ii[iter]) + (0.122*v1[iter]) + (0.231*v2[iter]) + (0.239*v3[iter]) + (0.194*v4[iter]) +  (0.156*v5[iter]) + (-0.010*v6[iter]);
	VCG_Y [iter]= (0.057*i[iter]) + (-0.019*ii[iter]) + (-0.106*v1[iter]) + (-0.022*v2[iter]) + (0.041*v3[iter]) + (0.048*v4[iter]) +  (-0.227*v5[iter]) + (0.887*v6[iter]);
	VCG_Z [iter]= (-0.229*i[iter]) + (-0.310*ii[iter]) + (-0.246*v1[iter]) + (-0.063*v2[iter]) + (0.055*v3[iter]) + (0.108*v4[iter]) +  (0.022*v5[iter]) + (0.102*v6[iter]);
}

VCG['X'] = VCG_X;
VCG['Y'] = VCG_Y;
VCG['Z'] = VCG_Z;

return VCG;
}



