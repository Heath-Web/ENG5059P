#include "cldl/Neuron.h"
#include "cldl/Layer.h"
#include "cldl/Net.h"

#include <iostream>
#include <Fir1.h>
#include <string>
#include <string.h>
#include <stdio.h>

#ifndef ECG_FILTER_H
#define ECG_FILTER_H

class ecg_filter {

public:
	
	/** Constructor: The ECG filter with a deep neuron network 
	*				 used to remove ECG artefacts (EMG).
 	* @param _dnn_nLayers Total number of hidden layers of DNN, excluding the input layer
 	* @param _dnn_nNeurons A pointer to an int array with number of
 	* neurons for all layers need to have the length of _nLayers.
 	* @param _dnn_nInputs Number of Inputs to the network
 	**/
    ecg_filter(int _dnn_nLayers, int *_dnn_nNeurons,const int _dnn_nInputs, int _subject, string _trial);

	/**
 	* Destructor
 	* De-allocated any memory
 	**/
    ~ecg_filter();
    
    /**
 	* Allow user to Customize the coefficient of 
	* fir filter for pre-filtering.
 	* @param _ch1_filter The channel 1 fir filter used to pre-filtering.
 	**/
    void setPreFilter(Fir1 *_ch1_filter, Fir1 *_ch2_filter); 
    
    /**
 	* Set the learning rate of the DNN weight and bias.
 	* @param _w_learningRate The Learning rate of weight in DNN.
 	* @param _b_learningRate The Learning rate of bias in DNN. 
 	**/
    void setLearningRate(double _w_learningRate, double _b_learningRate);
    
    /**
 	* The filter function operation: it receives one sample
    * and returns one sample.
 	* @param _signal The signal combined with noise, refers to channel 1.
 	* @param _noise The noise signal, refers to channel 2. 
 	* @return Return the final output of the ECG filter which should be the cleaned ECG
 	**/
    double filter(double _signal, double _noise);  
    
    /**
 	* Get the current remover (the output of DNN) after one filter operation 
 	* @return Return the output of the deep neuron network
 	**/
    double getCurrentRemover();
    
    /**
 	* Get the current filtered data (pre-filtered)
	* If haven't set the coefficients of the pre-filtering fir filter 
	* (see setPreFilterCoeff) this function will return NULL.
	* @param _channel The channel number 0 for channel 1 and 1 for channel 2
 	* @return Return the current channel pre-filtered data
 	**/
	double getCurrentFilteredData(int _channel);
	
	/**
 	* Get the current feedback to DNN (the output of DNN) 
	* after one filter operation.
 	* @return Return the feedback
 	**/
	double getCurrentFeedback();
    
    /**
	* The filter function operation 
	* filter all data from a file and save all results once.
	* The input file should only contain three columns, time, channel 1 and channel 2.
	* The output will be saved as 6 columns 
	* which are time, output, remover, filtered channel 1 and filtered channel 2 by order.
	* @param _infile_name The path of the input file.
	* @param _outfile_name The path of the output file. 
	**/
    void filterECGFromFile(string _infile_name, string _outfile_name);  
    
    /**
 	* Set Gians
 	* @param gains channel 1 and channel 2 input gain , remover gian , feedback gain by order
 	**/
    void setGains(double _ch1_gain, double _ch2_gain, double _remover_gain, double _feedback_gain);
    
    double* getDNNLearningRate(); 
    
    void reset();
    

    
    /**
	* Set the Input file stream.
	* The data file should only contain 3 columns 
	* which are time, channel 1, channel 2 by order.
	* @param _data_file_name The path of the input data file
	*
    void setInputFile(string _data_file_name);
    
	/**
 	* Set the output file stream.
 	* @param _output_file_name The path of the output file
 	*
    void setOutputFile(string _output_file_name);
    */

	// 初始化时候 建立delay队列， 

private:
	// Deep Neuron Network
	Net* NN = NULL;
	
	// DNN inputs delay line
	double *dnn_inputs;
	
	// Extracted signals
	double data_time = 0, ch1_data = 0, ch2_data = 0; // colmun 1,2,3
	
	// Prefilter
	// Define prefiltering fir filters for each channel
	Fir1 *ch1_fir_prefilter = NULL; 
	Fir1 *ch2_fir_prefilter = NULL;
	
	// Define Learning Rate of DNN (default value)
	double w_learningRate = 1;
	double b_learningRate = 1;
	
	// current Buffer when filtering 
	double ch1_filtered_data = 0;
	double ch2_filtered_data = 0;
	double remover = 0;
	double feedback = 0;
	double output = 0;
	
	// Gains (default value)
	double ch1_gain = 100;
    double ch2_gain = 100;
    double remover_gain = 10;
    double feedback_gain = 1;
	
};
#endif
