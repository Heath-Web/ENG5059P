import sys
import time
import pylab as plt
import matplotlib.animation as animation
import numpy as np
import math

sbjct_num = "2"
trail = "arm"

def getSNR_improvement():
     stratHZ = 10
     endHZ = 125
     samples = 5000

     # read data
     #raw_signal = np.loadtxt("../Data/RawData/" + "data_" +  trail + "_" +  sbjct_num + ".tsv")[:,7]
     #raw_relax = np.loadtxt("../Data/RawData/" + "relax_" +  trail + "_" +  sbjct_num + ".tsv")[:,7]

     raw_signal = np.loadtxt(("../Data/Output/output_" +  trail + "_" +  sbjct_num + ".tsv"))[:,3]
     raw_relax = np.loadtxt(("../Data/Output/output_relax" +  trail + "_" +  sbjct_num + ".tsv"))[:,3]
     output_signal = np.loadtxt(("../Data/Output/output_" +  trail + "_" +  sbjct_num + ".tsv"))[:,1]
     output_relax = np.loadtxt(("../Data/Output/output_relax" +  trail + "_" +  sbjct_num + ".tsv"))[:,1]
     # fft
     af_raw_signal = np.real(np.fft.fft(raw_signal[len(raw_signal)-samples:]))
     af_raw_relax = np.real(np.fft.fft(raw_relax[len(raw_relax)-samples:]))
     af_output_signal = np.real(np.fft.fft(output_signal[len(output_signal)-samples:]))
     af_output_relax = np.real(np.fft.fft(output_relax[len(output_relax)-samples:]))

     # before
     sum1 = 0
     sum2 = 0
     for i in af_raw_relax[int(stratHZ*samples/250):int(endHZ*samples/250)]:
        sum1 += i
     for j in af_raw_signal[int(stratHZ*samples/250):int(endHZ*samples/250)]:
        sum2 += i
     SNR_before = sum1/(sum2-sum1)

     # after
     sum3 = 0
     sum4 = 0
     for i in af_output_relax[int(stratHZ*samples/250):int(endHZ*samples/250)]:
        sum3 += i
     for j in af_output_signal[int(stratHZ*samples/250):int(endHZ*samples/250)]:
        sum4 += i
     SNR_after = sum3/(sum4-sum3)

     SNR = SNR_after - SNR_before
     print("SNR improvement",  SNR)

getSNR_improvement()
