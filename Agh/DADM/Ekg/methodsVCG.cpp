#include <methodsVCG.h>





double dot(double *vector1, double *vector2){
	int length = sizeof(vector1);
	double a=0;
	for (int i=0; i<=length; i++){
        a = a + vector1[i]*vector2[i];
	}
	return a;
}

double norm(double *vector){
	int length = sizeof(vector);
	double a=0;
	double result = 0;
	for (int i=0; i<=length; i++){
        a = vector[i]*vector[i];
		result = result+a;
	}
	result = sqrt(result);
	return result;
}

double mean(vector < double >::iterator data){
	int length = sizeof(data);
	double result = 0;
	for (int i=0; i<=length; i++){
        result = result+data[i];
	}
	result = result/length;
	return result;
}

double stddev(vector < double >::iterator data){
	double srednia = mean(data);
	int length = sizeof(data);
	double a, odchylenie = 0;
	for (int i=0; i<=length; i++){
		a = (data[i]-srednia)*(data[i]-srednia);
		odchylenie = odchylenie + a;
	}
	odchylenie = odchylenie/length-1;
	return odchylenie;
}

map<char, vector<double>> DowerTransform ( vector<double> i, vector<double> ii, vector<double> v1, vector<double> v2, vector<double> v3, vector<double> v4, vector<double> v5, vector<double> v6)
{
//Column order = t i ii iii avr avl avf v1 v2 v3 v4 v5 v6 x y z 

map <char, vector<double>> VCG;
VCG['x'];
VCG['y'];
VCG['z'];
vector <double> VCG_X;
vector <double> VCG_Y;
vector <double> VCG_Z;

for (int iter = 0; iter<VCG_X.size(); iter++){
	VCG_X [iter]= (-0.172*i[iter]) + (-0.074*ii[iter]) + (0.122*v1[iter]) + (0.231*v2[iter]) + (0.239*v3[iter]) + (0.194*v4[iter]) +  (0.156*v5[iter]) + (-0.010*v6[iter]);
	VCG_Y [iter]= (0.057*i[iter]) + (-0.019*ii[iter]) + (-0.106*v1[iter]) + (-0.022*v2[iter]) + (0.041*v3[iter]) + (0.048*v4[iter]) +  (-0.227*v5[iter]) + (0.887*v6[iter]);
	VCG_Z [iter]= (-0.229*i[iter]) + (-0.310*ii[iter]) + (-0.246*v1[iter]) + (-0.063*v2[iter]) + (0.055*v3[iter]) + (0.108*v4[iter]) +  (0.022*v5[iter]) + (0.102*v6[iter]);
}

VCG['x'] = VCG_X;
VCG['y'] = VCG_Y;
VCG['z'] = VCG_Z;

return VCG;
}



