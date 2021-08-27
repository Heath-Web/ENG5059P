#ifndef ECGFILTER_PARAMETERS_H
#define ECGFILTER_PARAMETERS_H

#define LMS_COEFF (int)(250)
#define LMS_LEARNING_RATE 0.1

// NOISE:
#define Inputs_Num 45

//NN specifications
#define DoDeepLearning
#define NLAYERS 7

#define N6 39 //6
#define N5 27 //5
#define N4 13  //4
#define N3 7 //3
#define N2 5 //2
#define N1 3 //1
#define N0 1 //always be 1

#endif //ECGFILTER_PARAMETERS_H
