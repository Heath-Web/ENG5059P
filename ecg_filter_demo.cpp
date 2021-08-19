// The only head file you need to include 
#include "ecg_filter.h"

using namespace std;

// Define contants
//const float fs = 250;
const int num_subjects = 2; // total number of subject
const int num_trials = 2; //as arm and wrist
string trials[num_trials] = {"arm","wrist"};

// Define Neuron Network
int nNeurons[NLAYERS]={N5,N4,N3,N2,N1,N0};
int* numNeuronsP = nNeurons;
const int num_inputs = Inputs_Num;
double gains[4] = {100,100,10,1};// channel 1 gain, channel 2 gain, remover gain and feedback gain

// Define Learning Rate of DNN
double w_learningRate = 1;
double b_learningRate = 2;

ecg_filter *filter1;

int main(){
	std::srand(1);
	cout << "Layer : " << NLAYERS << endl;
	for (int k = 0 ; k < NLAYERS; k++){
		cout << nNeurons[k] << " ;  ";
	}
	cout << endl;
	cout << "Inputs : " << Inputs_Num << endl; 
	for (int subject = 0; subject <= num_subjects; subject++) { // for each subject
		string str_subject = std::to_string(subject+1); // convert data format
		if (subject == num_subjects ){
			cout << "Subject : Relax" << endl;
		} else {
			cout << "Subject : " + str_subject << endl;
		}
		
		// for each trial
		for (int trial = 0; trial < num_trials; trial++){ 
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

        		// Save File
				fprintf(output_outfile, "%lf %lf %lf %lf %lf\n", data_time, output, remover, ch1_filtered_data, ch2_filtered_data);// Time Output Remover ch1 filtered data ch2 filtered data 
				//printf("Sample: %d, ch2Raw:%lf, DNNInput: %lf, DNNoutput: %lf\n", count, ch2_raw_data , ch2_filtered_data,remover);
			}
			
			// Close file stream
			fclose(data_infile);
			fclose(output_outfile);
			
			// reset ecg filter
			filter1->reset();
		}
	}
	return 0;
}
