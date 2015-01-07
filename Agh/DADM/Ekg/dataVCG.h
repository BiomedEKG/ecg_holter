#ifndef DATAVCG_H
#define DATAVCG_H

double AllX [5] = {0.0617880000000000,0.0579930000000000,0.0602990000000000,0.0622410000000000,0.0642610000000000};
double * wskX= AllX;

double AllY [5] = {0.0617880000000000,0.0579930000000000,0.0602990000000000,0.0622410000000000,0.0642610000000000};
double * wskY= AllY;

double AllZ [5] = {0.0617880000000000,0.0579930000000000,0.0602990000000000,0.0622410000000000,0.0642610000000000};
double * wskZ= AllZ;

double IsoelectricPoint [3] = {-0.00972300000000000, 0.00303600000000000,0.0177390000000000};

int T_EdgesIndexes[13][2] = {{1,580},{801,1300},{1551,2060},{2251,2780},{2951,3520},{3701,4260},{4451,5000},{5171,5750},{5901,6480},{6651,7200},{7401,7930},{8101,8670},{8850,9390}};

int QRS_EdgesIndexes[13][2] = {{581,800},{1301,1550},{2061,2250},{2781,2950},{3521,3700},{4261,4450},{5001,5170},{5751,5900},{6481,6650},{7201,7400},{7931,8100},{8671,8850},{9391,9550}};
    //float pi=3.1415;
	//for (i=0; i<=arrayset; i++){
	//	a[i]= pi*(pow(static_cast<float>(g[i]),2));
	//}

//method dot: dot(ThisPointFVector,X_axis_FVector)
//dot1 = ();

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

double mean(double *vector){
	int length = sizeof(vector);
	double result = 0;
	for (int i=0; i<=length; i++){
        result = result+vector[i];
	}
	result = result/length;
	return result;
}

double stddev(double *vector){
	double srednia = mean(vector);
	int length = sizeof(vector);
	double a, odchylenie = 0;
	for (int i=0; i<=length; i++){
		a = (vector[i]-srednia)*(vector[i]-srednia);
		odchylenie = odchylenie + a;
	}
	odchylenie = odchylenie/length-1;
	return odchylenie;
};

#endif // DATAVCG_H


