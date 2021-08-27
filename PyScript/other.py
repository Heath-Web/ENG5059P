import sys
import time
import pylab as plt
import matplotlib.animation as animation
import numpy as np

def plotECG_EMG_freq():
    sbjct_num = "2"  # "1", "2" or "relax"
    trail = "wrist"  # "arm" or "wrist"
    DC = 1

    raw_data = np.loadtxt("../Data/RawData/" + ("" if (sbjct_num == "relax") else "data_") + ("relax" if (sbjct_num == "relax") else trail) + "_" + (trail if (sbjct_num == "relax") else sbjct_num) + ".tsv")[:,[0,7,8]]
    ECG = raw_data[:,1]
    EMG = raw_data[:,2]
    plt.rcParams['font.sans-serif'] = ['SimHei']
    plt.figure(figsize=(7,5))
    y1 = np.real(np.fft.fft(ECG))[int((2/250)*int(len(ECG))):int(len(ECG)/2)]
    x = np.linspace(DC, 250 / 2, len(y1))
    plt.plot(x,y1, color='grey', label='ECG ')
    y2 = np.real(np.fft.fft(EMG))[int((2/250)*int(len(EMG))):int(len(EMG)/2)]
    x = np.linspace(DC, 250 / 2, len(y2))
    plt.plot(x,y2,  label='EMG')
    plt.xlabel("Frequency(Hz) fs=250Hz",fontsize=13)
    plt.ylabel("Amplitude A(F)",fontsize=13)
    plt.title("Frequency spectrum",fontsize=15)
    plt.ylim(0,max(y1))
    plt.xlim(DC,125)
    plt.grid(True)
    plt.legend(fontsize=15)
    plt.show()

def plot_ECGandEMG():
    start = 70
    end = 75

    rawECG = np.loadtxt("../Data/Output/" + "output_" + "wrist_1" + ".tsv")[:,3]
    cleanedECG = np.loadtxt("../Data/Output/" + "output_relax_" + "wrist" + ".tsv")[:,1]
    EMG = np.loadtxt("../Data/Output/" + "output_" + "wrist_1" + ".tsv")[:,4]
    x1 = start*250
    x2 = end*250
    x = np.linspace(start,end,x2-x1)

    figure = plt.figure(figsize=(5,5))
    plt.subplots_adjust(left=0.15, bottom=0.1, right=0.95, top=0.90, wspace=0.06, hspace=0.6)
    plt.subplot(311)
    plt.title("ECG", fontsize=15)
    plt.plot(x, cleanedECG[x1:x2])
    plt.subplot(312)
    plt.title("EMG", fontsize=15)
    plt.plot(x, EMG[x1:x2])
    plt.subplot(313)
    plt.title("ECG with EMG", fontsize=15)
    figure.supylabel("Amplitude",fontsize=15)
    figure.supxlabel("Time(s)", fontsize=15)
    plt.rcParams['axes.unicode_minus']=False
    plt.plot(x, rawECG[x1:x2])
    plt.show()

def plotWeightDistance():
    sbjct_num = "2"  # "arm" or "wrist"
    trail = "wrist"  # "arm" or "wrist"
    learningrate = ["1"]
    colors = ["grey","red","green"]
    gains = [3000,3000,200,1]

    plt.rcParams['font.sans-serif'] = ['SimHei']
    plt.figure("Weight")
    labelv = ""
    count = 0
    for i in learningrate:
        weightDistance = np.loadtxt(("../Data/TestData/" + gains[0] + gains[1]+ + gains[2] + gains[3] +"_"  + i +  + "_" + trail + "_" + sbjct_num + ".tsv"))
        labelv = i +" learning rate"
        plt.plot(weightDistance,color=colors[count],label=labelv)
        count = count + 1

    plt.xlabel("Samples")
    plt.grid(True)
    plt.legend()
    plt.show()

def plotRemover_CH1():
    sbjct_num = "1"  # "arm" or "wrist"
    trail = "wrist"  # "arm" or "wrist"

    results_data = np.loadtxt(("../Data/Output/output_" +  trail + "_" +  sbjct_num + ".tsv"))
    remover = results_data[:, 2]
    output = results_data[:, 1]
    #output = []
    filtered_data = results_data[:, [3, 4]]
    ch1 = filtered_data[:,0]


        #output.append(ch1[i] - remover[i])

    #ch1.extend( filtered_data[:len(filtered_data[:,0]) - delay, 0] )
    plt.rcParams['font.sans-serif'] = ['SimHei']
    plt.figure(figsize=(15,5))
    plt.plot(ch1[17700:18000],label="Ch1 filtered data")
    plt.plot(remover[17700:18000], color='red', label="Remover")
    #plt.plot(output[17600:18000], color='red', label="Output")
    plt.ylim(-1,2)
    plt.xlabel("Samples")
    plt.ylabel("Amplitude")
    #plt.plot(np.real(np.fft.fft(output[len(output)-5000:])), color='red', label='Remover')

    #plt.plot(output[len(output)-5000:len(output)-4000], color='green', label='Output')
    plt.grid(True)
    plt.legend(fontsize=13)
    plt.show()

#plotWeightDistance()
plotRemover_CH1()
#plotECG_EMG_freq()
