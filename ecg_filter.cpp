#include "ecg_filter.h"
#include "parameters.h"

using namespace std;

ecg_filter::ecg_filter(int _dnn_nLayers, int *_dnn_nNeurons,const int _dnn_nInputs, int _subject, string _trial){
	// Initialize Neuron Network
	NN = new Net(_dnn_nLayers, _dnn_nNeurons, _dnn_nInputs, _subject, _trial);
	//NN->initNetwork(Neuron::W_ZEROS, Neuron::B_NONE, Neuron::Act_Sigmoid);
	NN->initNetwork(Neuron::W_RANDOM, Neuron::B_RANDOM, Neuron::Act_Sigmoid);
	//NN->initNetwork(Neuron::W_ONES, Neuron::B_NONE, Neuron::Act_Sigmoid);
	
	// initialize dnn inputs delay line
	static double _inputs[outerDelayLineLength] = {};
	dnn_inputs = _inputs;
	
	// Initailize fir filter for prefiltering 
	if (fopen("firCoefficient.dat","r")) {
		ch1_fir_prefilter = new Fir1("firCoefficient.dat"); // channel 1
		ch2_fir_prefilter = new Fir1("firCoefficient.dat"); // channel 2
	} else{
		ch1_fir_prefilter = NULL;
		ch2_fir_prefilter = NULL;
	}
}

void ecg_filter::setPreFilter(Fir1 *_ch1_filter, Fir1 *_ch2_filter){
	ch1_fir_prefilter = _ch1_filter; // chanel 1
	ch2_fir_prefilter = _ch2_filter; // chanel 2 
} 

void ecg_filter::setLearningRate(double _w_learningRate, double _b_learningRate){
	w_learningRate = _w_learningRate;
	b_learningRate = _b_learningRate; 
	NN->setLearningRate(w_learningRate, b_learningRate);
}

double ecg_filter::getCurrentRemover(){
	return remover;
}

double ecg_filter::getCurrentFilteredData(int _channel) {
	if (_channel == 0){
		return ch1_filtered_data;
	} else if (_channel == 1) {
		return ch2_filtered_data;
	} else {
		cout << "Fail to gee current prefiltered Data return 0" << endl; 
		return 0; 
	}
}

double ecg_filter::getCurrentFeedback(){
	return feedback;
}

double ecg_filter::filter(double _signal, double _noise){
	double ch1_data, ch2_data;
	// Pre filter
	if (ch2_fir_prefilter != NULL && ch1_fir_prefilter != NULL){
		ch1_filtered_data = ch1_fir_prefilter->filter(_signal*ch1_gain);
	    ch2_filtered_data = ch2_fir_prefilter->filter(_noise*ch2_gain);
	    ch1_data = ch1_filtered_data;
	    ch2_data = ch2_filtered_data; 
	} else {
		cout << "Can't find Fir filter coefficient file \"firCoefficient.dat\" " << endl;
		exit(1); // terminate
	}	 
	
	double num_inputs = NN->getnInputs();	
	//cout << num_inputs << "||" << ch2_filtered_data << "  :: " << ch2_data << " ]]]] ";				
    // Chanel 2 Delay line
    
    for (int i = num_inputs-1 ; i > 0; i--){ 
        dnn_inputs[i] = dnn_inputs[i-1];
    }
    dnn_inputs[0] = ch2_data;
				
    // Input Chanel 2 into Network
    NN->setInputs(dnn_inputs);
	NN->propInputs();
    
    //Remover
    remover = NN->getOutput(0);
    remover = remover*remover_gain;
    			
    // Learn, Update weights
	output = ch1_data - remover;
	feedback = output*feedback_gain;
    NN->setErrorCoeff(0, 1, 0, 0, 0, 0); //global, back, mid, forward, local, echo error
    NN->setBackwardError(feedback);
    NN->propErrorBackward();
    NN->setLearningRate(w_learningRate, b_learningRate);
    NN->updateWeights();
    
    return output;
}

void ecg_filter::filterECGFromFile(string _infile_name, string _outfile_name){
	FILE *infile = fopen(_infile_name.c_str(), "rt");
	FILE *outfile = fopen(_outfile_name.c_str(), "w");
	
	if(!infile || !outfile) {
		cout << "Unable to open file" << _infile_name << "or" << _outfile_name << endl;
   	    exit(1); // terminate with error
	}
	
	int count = 0;
	while (fscanf(infile,"%lf %lf %lf\n",&data_time, &ch1_data, &ch2_data) >= 1) {
    	count++;
    	// do filter 
    	double feedback = filter(ch1_data, ch2_data); 
		// Pre filter
    	double ch1_filtered_data = getCurrentFilteredData(0);
		double ch2_filtered_data = getCurrentFilteredData(1);
    	//Remover
    	double remover = getCurrentRemover();

        // Save File
		fprintf(outfile, "%lf %lf %lf %lf %lf\n", data_time, feedback, remover, ch1_filtered_data, ch2_filtered_data);// Time Output Remover ch1 filtered data ch2 filtered data 
		//printf("Sample: %d, ch2Raw:%lf, DNNInput: %lf, DNNoutput: %lf\n", count, ch2_raw_data , ch2_filtered_data,remover);
	}
			
	// Close file stream
	fclose(infile);
	fclose(outfile);
}

void ecg_filter::reset(){
	memset(dnn_inputs, 0, sizeof(dnn_inputs));
}

void ecg_filter::setGains(double _ch1_gain, double _ch2_gain, double _remover_gain, double _feedback_gain){
	ch1_gain = _ch1_gain;
	ch2_gain = _ch2_gain;
	remover_gain = _remover_gain;
	feedback_gain = _feedback_gain;
}

/*
void ecg_filter::setOutputFile(string _output_file_name){
	if (output_outfile != NULL){
		fclose(output_outfile);
	}
	output_outfile = fopen(_output_file_name.c_str(),"w");
	if (!output_outfile) {
	    cout << "Unable to open file" << _output_file_name << endl;
   	   	exit(1); // terminate with error
    }
}

void ecg_filter::setInputFile(string _data_file_name){
	if (data_infile != NULL){
		fclose(data_infile);
	} 
	data_infile = fopen(_data_file_name.c_str(), "rt");	
	if (!data_infile) {
        cout << "Unable to open file" << _data_file_name << endl;
   	   	exit(1); // terminate with error
    }	
			
}*/
