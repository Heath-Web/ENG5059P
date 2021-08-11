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
const int num_subjects = 2; // total number of subject
const int num_trials = 2; //as arm and wrist
string trials[num_trials] = {"arm","wrist"};

// Define and 
int nNeurons[NLAYERS]={N10, N9, N8, N7, N6, N5, N4, N3, N2, N1, N0};
int* numNeuronsP = nNeurons;
int num_inputs = outerDelayLineLength;

// Define Learning Rate of DNN
double w_learningRate = 1;
double b_learningRate = 2;

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
				output_file_name = "./Data/Output/output_relax_" + trials[trial] + ".tsv";
			} else {
				data_file_name = "./Data/ProcessedData/extracted_" + trials[trial] + "_" + str_subject + ".tsv";
				output_file_name = "./Data/Output/output_" + trials[trial] + "_" + str_subject + ".tsv";
			}
			FILE* data_infile = fopen(data_file_name.c_str(),"rt");
			FILE* output_outfile = fopen(output_file_name.c_str(),"w");
			
			if (!data_infile || !output_outfile) {
    	    	cout << "Unable to open file";
   	    		exit(1); // terminate with error
    		}
    		
    		// Define fir filters for each trial (arm and wrist) and initialize 
    		// Read fir coefficient
			Fir1 *ch1_fir_filter = new Fir1("firCoefficient.dat"); // chanel 1
			Fir1 *ch2_fir_filter = new Fir1("firCoefficient.dat"); // chanel 2
			 
			// Extracted signals
			double data_time, ch1_raw_data, ch2_raw_data; // colmun 1,2,3
			
			//initialize deep Neural Network
			Net* NN = new Net(NLAYERS, numNeuronsP, num_inputs, subject, trials[trial]);
			NN->initNetwork(Neuron::W_RANDOM, Neuron::B_RANDOM, Neuron::Act_Sigmoid);
			
			// Define inputs queue of DNN
			double dnn_inputs[num_inputs] = {};
			
			int count = 0;
    		// Read Raw data from tsv file
    		while (fscanf(data_infile,"%lf %lf %lf\n",&data_time, &ch1_raw_data, &ch2_raw_data) >= 1) {
    			count++;
				// Pre filter
    			double ch1_filtered_data = ch1_fir_filter->filter(ch1_raw_data);
				double ch2_filtered_data = ch2_fir_filter->filter(ch2_raw_data);
								
    			// Chanel 2 Delay line
        		for (int i = num_inputs-1 ; i > 0; i--){
            		dnn_inputs[i] = dnn_inputs[i-1];
        		}
        		dnn_inputs[0] = ch2_filtered_data;
        		double* dnn_inputs_pointer = &dnn_inputs[0];
    			
    			// Input Chanel 2 into Network
    			NN->setInputs(dnn_inputs_pointer);
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
				fprintf(output_outfile, "%lf %lf %lf %lf %lf\n", data_time, feedback, remover, ch1_filtered_data, ch2_filtered_data);// Time Output Remover ch1 filtered data ch2 filtered data 
				//printf("Sample: %d, ch2Raw:%lf, DNNInput: %lf, DNNoutput: %lf\n", count, ch2_raw_data , ch2_filtered_data,remover);
			}
			
			// Close file stream
			fclose(data_infile);
			fclose(output_outfile);
		}
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
