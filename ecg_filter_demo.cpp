<<<<<<< HEAD
// The only head file you need to include 
=======
// The only head file you need to include
>>>>>>> dev
#include "ecg_filter.h"

using namespace std;

// Define contants
//const float fs = 250;
const int num_subjects = 2; // total number of subject
const int num_trials = 4; //as arm and wrist
string trials[num_trials] = {"arm","wrist","relaxarm","relaxwrist"};

// Define Neuron Network
<<<<<<< HEAD
int nNeurons[NLAYERS]={N5,N4,N3,N2,N1,N0};
int* numNeuronsP = nNeurons;
const int num_inputs = Inputs_Num;
double gains[4] = {100,100,10,1};// channel 1 gain, channel 2 gain, remover gain and feedback gain

// Define Learning Rate of DNN
double w_learningRate = 1;
double b_learningRate = 2;
=======
int nNeurons[NLAYERS]={N6,N5,N4,N3,N2,N1,N0};
int* numNeuronsP = nNeurons;
const int num_inputs = Inputs_Num;
double gains[4] = {2500,2500,2000,5};// channel 1 gain, channel 2 gain, remover gain and feedback gain

// Define Learning Rate of DNN
double w_learningRate = 1.1;
double b_learningRate = 0;
>>>>>>> dev

ecg_filter *filter1;

int main(){
	std::srand(1);
	cout << "Layer : " << NLAYERS << endl;
	for (int k = 0 ; k < NLAYERS; k++){
		cout << nNeurons[k] << " ;  ";
	}
	cout << endl;
<<<<<<< HEAD
	cout << "Inputs : " << Inputs_Num << endl; 
	for (int subject = 0; subject <= num_subjects; subject++) { // for each subject
		string str_subject = std::to_string(subject+1); // convert data format
		if (subject == num_subjects ){
			cout << "Subject : Relax" << endl;
		} else {
			cout << "Subject : " + str_subject << endl;
		}
		
=======
	cout << "Inputs : " << Inputs_Num << endl;
	for (int subject = 0; subject < num_subjects; subject++) { // for each subject
		string str_subject = std::to_string(subject+1); // convert data format
		cout << "Subject : " + str_subject << endl;

>>>>>>> dev
		// for each trial
		for (int trial = 0; trial < num_trials; trial++){
			cout << "Trial : " + trials[trial] << endl;

			string data_file_name = "";
			string output_file_name = "";
			// Open extracted data file, and output file
			data_file_name = "./Data/ProcessedData/extracted_" + trials[trial] + "_" + str_subject + ".tsv";
            output_file_name = "./Data/Output/output_" + trials[trial] + "_" + str_subject + ".tsv";

			FILE* data_infile = fopen(data_file_name.c_str(),"rt");
			FILE* output_outfile = fopen(output_file_name.c_str(),"w");
			// for testing
			//string testfile_name = "./Data/TestData/" + std::to_string((int)gains[0]) + std::to_string((int)gains[1]) +std::to_string((int)gains[2]) +std::to_string((int)gains[3]) + "_" +std::to_string((int)w_learningRate) + "_" + trials[trial] + "_" + str_subject + ".tsv";
			//FILE* test_outfile = fopen(testfile_name.c_str(),"w");

			if (!data_infile || !output_outfile) {
    	    	cout << "Unable to open file";
   	    		exit(1); // terminate with error
    		}

    		//initialize ecg filter
    		filter1 = new ecg_filter(NLAYERS, numNeuronsP, num_inputs, subject, trials[trial]);
    		filter1->setLearningRate(w_learningRate, b_learningRate);
    		filter1->setGains(gains[0],gains[1],gains[2],gains[3]);
			//Fir1 filter1(num_inputs);

			double data_time = 0, ch1_raw_data = 0, ch2_raw_data = 0; // colmun 1,2,3
			int count = 0;
    		// Read Raw data from tsv file
    		while (fscanf(data_infile,"%lf %lf %lf\n",&data_time, &ch1_raw_data, &ch2_raw_data) >= 1) {
    			count++;
    			// do filter
    			//cout << "Sample " << count  << " ";
    			double output = filter1->filter(ch1_raw_data, ch2_raw_data);
				// Pre filter
    			double ch1_filtered_data = filter1->getCurrentFilteredData(0);
				double ch2_filtered_data = filter1->getCurrentFilteredData(1);
    			//Remover
    			double remover = filter1->getCurrentRemover();


        		// for Testing monitoring
        		//double weight_distance = filter1->get_d_nn()->getWeightDistance();
        		//double exploding_gra =  filter1->get_d_nn()->getGradient(Neuron::onBackwardError,Layer::exploding);
        		//double vanishing_gra = filter1->get_d_nn()->getGradient(Neuron::onBackwardError,Layer::vanishing);
                //fprintf(test_outfile, "%lf %lf %lf\n",weight_distance, exploding_gra, vanishing_gra);
                //fprintf(test_outfile, "%lf\n",weight_distance);

				// Save File
				fprintf(output_outfile, "%lf %lf %lf %lf %lf\n", data_time, output, remover, ch1_filtered_data, ch2_filtered_data);// Time Output Remover ch1 filtered data ch2 filtered data
			}

			// Close file stream
			fclose(data_infile);
			fclose(output_outfile);
			cout << "output save to " << output_file_name << endl;
			//fclose(test_outfile);
			//cout << "test data save to " << testfile_name << endl;

			// reset ecg filter
			filter1->reset();
		}
	}
	return 0;
}
<<<<<<< HEAD
=======
<<<<<<< HEAD

/*
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

// Define Neuron Network
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
}*/
=======
>>>>>>> dev
>>>>>>> release
