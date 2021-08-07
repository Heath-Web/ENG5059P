#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <Fir1.h>
#include "parameters.h"

#include "cldl/Neuron.h"
#include "cldl/Layer.h"
#include "cldl/Net.h"

using namespace std;

// Define contants
//const float fs = 250;
const int num_subjects = 2;
const int num_trials = 2; //as arm and wrist
string trials[num_trials] = {"arm","wrist"};

// Define methods
//void Pre_filter() {} // Remove 50Hz and DC from extracted data


int main(){
	std::srand(1);
	for (int subject = 0; subject < num_subjects; subject++) { // for each subject
		string str_subject = std::to_string(subject+1); // convert data formatb
		cout << "Subject : " + str_subject << endl;
		for (int trial = 0; trial < num_trials; trial++){ // for each trial
			cout << "Trial : " + trials[trial] << endl;
			
			// Open extracted data file
			string file_name = "./Data/ProcessedData/extracted_";
			file_name.append(trials[trial]);
			file_name.append("_");
			file_name.append(str_subject);
			file_name.append(".tsv");
			FILE* data_infile = fopen(file_name.c_str(),"rt");
			if (!data_infile) {
    	    	cout << "Unable to open file";
   	    		exit(1); // terminate with error
    		}
    		
    		// Define fir filters for each trial (arm and wrist) and initialize 
    		// read fir coefficient
			Fir1 *ch1_fir_filter = new Fir1("firCoefficient.dat"); // chanel 1
			Fir1 *ch2_fir_filter = new Fir1("firCoefficient.dat"); // chanel 2
			 
			// Extracted signals
			double data_time, ch1_raw_data, ch2_raw_data; // colmun 1,2,3
			
			// Define and initialize deep Neural Network
			int nNeurons[NLAYERS]={N10, N9, N8, N7, N6, N5, N4, N3, N2, N1, N0};
			int* numNeuronsP = nNeurons;
			int num_inputs = outerDelayLineLength;
			Net* NN = new Net(NLAYERS, numNeuronsP, num_inputs, 0, trials[trial]);
			NN->initNetwork(Neuron::W_RANDOM, Neuron::B_RANDOM, Neuron::Act_Sigmoid);
			
			// Define inputs queue of DNN
			//double dnn_inputs_queue[num_inputs];
			//double* dnn_inputs_queue_pointer;
			
    		// Read Raw data from tsv file
    		while (fscanf(data_infile,"%lf %lf %lf\n",&data_time, &ch1_raw_data, &ch2_raw_data) >= 1) {
    			// Pre filter
    			double ch1_filtered_data = ch1_fir_filter->filter(ch1_raw_data);
				double ch2_filtered_data = ch1_fir_filter->filter(ch2_raw_data);				
    			printf("%lf ; ", ch1_filtered_data);
    			// Delay line
        		//for (int i = num_inputs-1 ; i > 0; i--){
            	//	dnn_inputs_queue[i] = dnn_inputs_queue[i-1];
        		//}
        		//dnn_inputs_queue[0] = outer_closed;
        		//outer_open_delayLine[0] = outer_open;
        		
        		//double* outer_closed_delayed = &outer_closed_delayLine[0];
        		//double* outer_open_delayed = &outer_open_delayLine[0];
    			
    			// Input Chanel 2 into Network
    			
    			
    			// Learn, Update weights	
			}
		}

	
	
	
		//initiate Neuronal Network
		/*
		NN_ARM->initNetwork(Neuron::W_RANDOM, Neuron::B_RANDOM, Neuron::Act_Sigmoid);
		NN_WRIST->initNetwork(Neuron::W_RANDOM, Neuron::B_RANDOM, Neuron::Act_Sigmoid);
	
	
		const double inputs[num_inputs] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		const double* inp = inputs;
		NN->setInputs(inp);
		NN->propInputs();
		double remover = NN->getOutput(0);
	
		NN->printNetwork();
		printf("%f",remover);*/
	}

	return 0;
}


/*
void Pre_filter() {
	// Define fir filters
	Fir1 *ch1_fir_filter[num_trials]; // for each trial (arm and wrist)
	Fir1 *ch2_fir_filter[num_trials]; 
	for (int i = 0; i < num_trials; i++) {
		for (int j = 0; j < num_chanels; j++){
	        fir_filter[i][j] = new Fir1("firCoefficient.dat"); // read fir coefficient
        	fir_filter[i][j]->reset();	
		}
    }
    
    
}*/
