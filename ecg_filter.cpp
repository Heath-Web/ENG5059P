#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "parameters.h"

#include "cldl/Neuron.h"
#include "cldl/Layer.h"
#include "cldl/Net.h"

using namespace std;

int num_inputs = outerDelayLineLength;

//NEURAL NETWORK
#ifdef DoDeepLearning
int nNeurons[NLAYERS]={N10, N9, N8, N7, N6, N5, N4, N3, N2, N1, N0};
int* numNeuronsP = nNeurons;
Net* NN = new Net(NLAYERS, numNeuronsP, num_inputs, 0, "ECG");
//Net* NNO = new Net(NLAYERS, numNeuronsP, num_inputs, 0, "OPEN");
double w_eta = 0;
double b_eta = 0;
#endif

int main(){
	NN->initNetwork(Neuron::W_RANDOM, Neuron::B_RANDOM, Neuron::Act_Sigmoid);
	
	const double inputs[num_inputs] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	const double* inp = inputs;
	NN->setInputs(inp);
	NN->propInputs();
	double remover = NN->getOutput(0);
	
	NN->printNetwork();
	printf("%f",remover);
	return 0;
}
