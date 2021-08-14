#ifndef ECGFILTER_PARAMETERS_H
#define ECGFILTER_PARAMETERS_H

#define LMS_COEFF (int)(250)
#define LMS_LEARNING_RATE 0.00001

#define DoShowPlots

#define maxFilterLength 250

// NOISE:
#define doOuterPreFilter
#define doOuterDelayLine
#define outerDelayLineLength 250

// SIGNAL:
#define doInnerPreFilter
#define doInnerDelay
#define innerDelayLineLength 250

//NN specifications
#define DoDeepLearning
#define NLAYERS 10
//#define N12 125 //12
//#define N11 63 //11
//#define N10 37 //10
#define N9 125 //9
#define N8 63 //8
#define N7 37 //7
#define N6 19 //6
#define N5 11 //5
#define N4 7  //4
#define N3 5 //3
#define N2 3 //2
#define N1 2 //1
#define N0 1 //this has to always be 1

#endif //ECGFILTER_PARAMETERS_H
