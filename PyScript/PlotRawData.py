#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Extract useful information from Raw Data and save to the folder ProcessedData
Plot Chanel 1 and Chanel 2 of ADC for each subject and trail (arm, wrist)

Define total subject number and trails first
"""
import matplotlib.pyplot as plt
import numpy as np

# define total subject number , trails
sbjct_num = 2
trails = ['arm', 'wrist']

data = []
# Extract useful information
for sbjct in range(1, sbjct_num + 1):
    figure = plt.figure("Subject " + str(sbjct) + "Raw Data")
    data.append({})
    count = 1
    for trail in trails:
        # Load raw data and extract the three relevant columns (time, ch1 and ch2 of ADC)
        data[sbjct-1][trail] = np.loadtxt("../Data/RawData/data_" + trail + "_" + str(sbjct) + ".tsv")[:,[0,7,8]]
        # save
        np.savetxt("../Data/ProcessedData/extracted_" + trail + "_" + str(sbjct) + ".tsv", data[sbjct-1][trail])
        print(" File saved to" + "  ../Data/ProcessedData/extracted_" + trail + "_" + str(sbjct) + ".tsv")

        # plot (two chanel)
        figure.add_subplot(len(trails), 2, count) # chanel 1
        plt.plot(data[sbjct-1][trail][:, 1], linewidth=1)
        plt.title('Subject' + str(sbjct) + ' ' + trail + ' CH1')
        figure.add_subplot(len(trails), 2, count+1) # chanel 2
        plt.plot(data[sbjct-1][trail][:, 2], linewidth=1)
        plt.title('Subject' + str(sbjct) + ' ' + trail + ' CH2')
        count += 2

# relaxed data
relax_data = {}
figure = plt.figure(" Relax Raw Data")
count = 1
for trail in trails:
    relax_data[trail] = np.loadtxt("../Data/RawData/relax_" + trail +  ".tsv")[:,[0,7,8]]
    np.savetxt("../Data/ProcessedData/extracted_relax_" + trail +  ".tsv", relax_data[trail])
    print(" File saved to" + "  ../Data/ProcessedData/extracted_relax_" + trail + ".tsv")

    # plot (two chanel)
    figure.add_subplot(len(trails), 2, count)  # chanel 1
    plt.plot(relax_data[trail][:, 1], linewidth=1)
    plt.title('Relax ' + trail + ' CH1')
    figure.add_subplot(len(trails), 2, count + 1)  # chanel 2
    plt.plot(relax_data[trail][:, 2], linewidth=1)
    plt.title('Relax ' + trail + ' CH2')
    count += 2

plt.show()