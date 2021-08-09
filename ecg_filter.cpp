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
const int num_subjects = 1;
const int num_trials = 1; //as arm and wrist
string trials[num_trials] = {"arm"};//{"arm","wrist"};

// Define Learning Rate of DNN
double w_learningRate = 0.5;
double b_learningRate = 0.5;

// Define methods
//void Pre_filter() {} // Remove 50Hz and DC from extracted data

int main(){
	std::srand(1);
	for (int subject = 0; subject <= num_subjects; subject++) { // for each subject
		string str_subject = std::to_string(subject+1); // convert data formatb
		if (subject == num_subjects ){
			cout << "Subject : Relax" << endl;
		} else {
			cout << "Subject : " + str_subject << endl;
		}
		for (int trial = 0; trial < num_trials; trial++){ // for each trial
			cout << "Trial : " + trials[trial] << endl;
			
			string data_file_name = "";
			string output_file_name = "";
			// Open extracted data file, and output file 
			if (subject == num_subjects ){
				data_file_name = "./Data/ProcessedData/extracted_relax_" +  trials[trial] + ".tsv";
				//prefilter_file_name = "./Data/FilteredData/filtered_relax_" + trials[trial] + ".tsv";
				//remover_file_name = "./Data/Remover/remover_relax_" + trials[trial] + ".tsv";
				output_file_name = "./Data/Output/output_relax_" + trials[trial] + ".tsv";
			} else {
				data_file_name = "./Data/ProcessedData/extracted_" + trials[trial] + "_" + str_subject + ".tsv";
				//prefilter_file_name = "./Data/FilteredData/filtered_" + trials[trial] + "_" + str_subject + ".tsv";
				//remover_file_name = "./Data/Remover/remover_" + trials[trial] + "_" + str_subject + ".tsv";
				output_file_name = "./Data/Output/output_" + trials[trial] + "_" + str_subject + ".tsv";
			}
			FILE* data_infile = fopen(data_file_name.c_str(),"rt");
			//FILE* prefilter_outfile = fopen(prefilter_file_name.c_str(),"w");
			//FILE* remover_outfile = fopen(remover_file_name.c_str(),"w");
			FILE* output_outfile = fopen(output_file_name.c_str(),"w");
			
			if (!data_infile || !output_outfile) {
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
			Net* NN = new Net(NLAYERS, numNeuronsP, num_inputs, subject, trials[trial]);
			NN->initNetwork(Neuron::W_RANDOM, Neuron::B_RANDOM, Neuron::Act_Sigmoid);
			
			// Define inputs queue of DNN
			double dnn_inputs[num_inputs] = {};
			//double* dnn_inputs_queue_pointer;
			
			int count = 0;
    		// Read Raw data from tsv file
    		while (fscanf(data_infile,"%lf %lf %lf\n",&data_time, &ch1_raw_data, &ch2_raw_data) >= 1) {
    			count++;
				// Pre filter
    			double ch1_filtered_data = ch1_fir_filter->filter(ch1_raw_data);
				double ch2_filtered_data = ch1_fir_filter->filter(ch2_raw_data);				
    			  
    			// Chanel 2 Delay line
        		for (int i = num_inputs-1 ; i > 0; i--){
            		dnn_inputs[i] = dnn_inputs[i-1];
        		}
        		dnn_inputs[0] = ch2_filtered_data;
        		double* dnn_inputs_point = &dnn_inputs[0];
    			
    			// Input Chanel 2 into Network
    			NN->setInputs(dnn_inputs_point);
				NN->propInputs();
    
    			//Remover
    			double remover = NN->getOutput(0);
    			
    			// Learn, Update weights
    			double feedback = ch1_filtered_data - remover;
    			NN->setErrorCoeff(0, 1, 0, 0, 0, 0); //global, back, mid, forward, local, echo error
        		NN->setBackwardError(feedback);
        		NN->propErrorBackward();
        		NN->setLearningRate(w_learningRate, b_learningRate);
        		//if (count > maxFilterLength+outerDelayLineLength){
        		NN->updateWeights();
        		
        		// Save File
				//fprintf(prefilter_outfile, "%lf %lf %lf\n", data_time, ch1_filtered_data, ch2_filtered_data);
				//fprintf(remover_outfile, "%lf %lf\n", data_time, remover);
				fprintf(output_outfile, "%lf %lf %lf %lf %lf\n", data_time, feedback, remover, ch1_filtered_data, ch2_filtered_data);
				//printf("Sample: %d, ch2Raw:%lf, DNNInput: %lf, DNNoutput: %lf\n", count, ch2_raw_data , ch2_filtered_data,remover);
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
