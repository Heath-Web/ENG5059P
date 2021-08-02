// Usage Examples
//
// LMS demo
// removes 50Hz from an ECG with a powerline reference
// here generated with a simple sine. Should be ideally
// also measured with another ADC channel and fed into
// the filter.

// This is the only include you need
//#include "Fir1.cpp"
#include "Fir1.h"

#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>

#define NTAPS 100
#define LEARNING_RATE 0.0005

int main (int,char**)
{
	// inits the filter
	Fir1 fir(NTAPS);
	fir.setLearningRate(LEARNING_RATE);

	FILE *finput = fopen("ecg50hz.dat","rt");
	FILE *foutput = fopen("ecg_filtered.dat","wt");
	for(int i=0;;i++) 
	{
		double input_signal;		
		if (fscanf(finput,"%lf\n",&input_signal)<1) break;
		double ref_noise = sin(2*M_PI/20*i);
		double canceller = fir.filter(ref_noise);
		double output_signal = input_signal - canceller;
		fir.lms_update(output_signal);
		fprintf(foutput,"%f %f %f\n",output_signal,canceller,ref_noise);
	}
	fclose(finput);
	fclose(foutput);
	fprintf(stderr,"Written the filtered ECG to 'ecg_filtered.dat'\n");
}
