# ECG artifacts removal with deep adaptive filter

An adaptive and real-time ECG filter Class with a deep neural network in C++, used to reduce ECG artifacts (EMG) from the ECG signals.

## Data Sets

The ECG signal were obtained from 2 subjects using AttysECG. For each subject, two set ups  were used which covers the noise from the bicep (arm) and the whole arm (wrist) separately.  Both of two subjects were holding a large bottle of water (weight 1.5 kg approximately) while recording. Each recording last one minute and a half.

Additional relaxed data was recorded from subject 1 while the subject keep relax.

## Prerequisites Libraries and packages:
1. Install the *Fir1* library from _https://github.com/berndporr/fir1_ by running:

   ` sudo add-apt-repository ppa:berndporr/dsp `
   ` sudo apt-get install fir1 ` 
   ` sudo apt-get install fir1-dev `

2. Install `Cmake`
   `wget https://github.com/Kitware/CMake/releases/download/v3.21.1/cmake-3.21.1.tar.gz`
   `tar -zxv -f cmake-3.21.1.tar.gz`
   `cd cmake-3.21.1`
   `./bootstrap`
   `make`
   `sudo make install`

   Alternatively,  install any `cmake` version beyond 3.1.0.

## How to compile and run the program (Demo):
1. Clone this repository: ` git clone https://github.com/Heath-Web/ENG5059P.git` 
2. Navigate to the folder: `cd ENG5059P`
3. compile the file using *cmake*: `cmake .` and `make`
4. run : `./ecg_filter_demo` 
   This will create the necessary folders, build the program and the DNF library. The program will filter all the data in `./Data/ProcessedData` and generate the output to `./Data/Output`. 
5. Show final results : 
   You can use either jupyter notebook `Plotresults.ipynb` or simply run the python file `Python PlotResults.py` in the PyScripts folder to plot the final results both in frequency domain and in dynamic time domain.

## How to use ecg_filter class

ecg_filter filter = new ecg_filter ()

ecg_filter->set

## File Structure

- Parameters.h : The parameters of the demo program.
- ecg_filter_demo : demo program of using ecg filter 
- ecg_filter.h and ecg_filter.cpp : head file and implementation file of ecg filter Class  
- Data :
  - RawData :  The raw data recorded from attys-scope directly.
  - ProcessedData : Extracted data from raw data, only remain 3 columns which are time, channel 1 and channel 2 of ADC.
  - Output: The output of the *ecg_filter_demo.cpp* 
- DNF ：Deep neuronal Filter
- PyScript : Python Files
  - PlotRawData.py : Extract useful information from Raw Data and save to the folder *ProcessedData*. Plot Chanel 1 and Chanel 2 of ADC for each subject and trail (arm, wrist).
  - GenerateFirCoeff.py : Generate the coefficient of fir filter for pre-filtering (Remove DC and 50HZ).
    The coefficients will be save to *"firCoefficient.dat".*
  - PlotResults.py : Dynamic Plot results in time domain, and the frequency spectrum.
  - PlotResults.ipynb : Jupyter notebook version of *PlotResults.py.*
