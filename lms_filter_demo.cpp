#include <Fir1.h>
#include <iostream>
#include <stdio.h> 
#include "parameters.h"

using namespace std;

// Define contants
//const float fs = 250;
const int num_subjects = 2; // total number of subject
const int num_trials = 2; //as arm and wrist
string trials[num_trials] = {"arm","wrist"};


Fir1 *filter1;
Fir1 *ch1_prefilter;
Fir1 *ch2_prefilter;

int main(){
	std::srand(1);
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
				output_file_name = "./Data/LMS_Output/output_relax_" + trials[trial] + ".tsv";
			} else {
				data_file_name = "./Data/ProcessedData/extracted_" + trials[trial] + "_" + str_subject + ".tsv";
				output_file_name = "./Data/LMS_Output/output_" + trials[trial] + "_" + str_subject + ".tsv";
			}
			FILE* data_infile = fopen(data_file_name.c_str(),"rt");
			FILE* output_outfile = fopen(output_file_name.c_str(),"w");
			
			if (!data_infile || !output_outfile) {
    	    	cout << "Unable to open file";
   	    		exit(1); // terminate with error
    		}
    		
    		//initialize lms filter
    		filter1 = new Fir1(LMS_COEFF);
    		// initialize pre-filter
    		ch1_prefilter = new Fir1("firCoefficient.dat");
    		ch2_prefilter = new Fir1("firCoefficient.dat");
			
			double data_time = 0, ch1_raw_data = 0, ch2_raw_data = 0; // colmun 1,2,3
			int count = 0;
    		// Read Raw data from tsv file
    		while (fscanf(data_infile,"%lf %lf %lf\n",&data_time, &ch1_raw_data, &ch2_raw_data) >= 1) {
    			//pre filter
				double ch1_data = ch1_prefilter->filter(ch1_raw_data);
				double ch2_data = ch2_prefilter->filter(ch2_raw_data);
				//lms
				double canceller = filter1->filter(ch2_data);
				
				double output_signal = ch1_data - canceller;
				filter1->lms_update(output_signal);

        		// Save File
				fprintf(output_outfile, "%lf %lf %lf %lf %lf\n", data_time, output_signal, canceller, ch1_data, ch2_data);
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
