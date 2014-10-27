#include "ekg.h"
#include <QtWidgets/QApplication>
#include <iostream>
#define FFTW_DLL
#include <fftw3.h>
#include <gsl\gsl_sf_bessel.h>
#include <qdebug.h>



int main(int argc, char *argv[])
{
	const int L = 10;
	fftw_complex *in; 
	fftw_complex *out;
	gsl_sf_bessel_k0_scaled(0.684684);
	fftw_plan p;

	in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*L);
	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*L);
	p = fftw_plan_dft_1d(L, in, out,FFTW_FORWARD,FFTW_MEASURE); 

	fftw_execute(p);
	fftw_destroy_plan(p);
	fftw_free(in);
	fftw_free(out);
	 
	QApplication a(argc, argv);
	Ekg w;
	w.show();
	qDebug() << "sdfsdfsd";
	std::cout << "ALKO PROJEKT CPP CHLOSTA!";			
	
	return a.exec();
}
