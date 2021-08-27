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
relax_data = []
# Extract useful information
for sbjct in range(1, sbjct_num + 1):
    figure = plt.figure("Subject " + str(sbjct) + "Raw Data")
    data.append({})
    relax_data.append({})
    count = 1
    for trail in trails:
        # Load raw data and extract the three relevant columns (time, ch1 and ch2 of ADC)
        data[sbjct-1][trail] = np.loadtxt("../Data/RawData/data_" + trail + "_" + str(sbjct) + ".tsv")[:,[0,7,8]]
        # Load relax data and extract
        relax_data[sbjct-1][trail] = np.loadtxt("../Data/RawData/relax_" + trail + "_" + str(sbjct) + ".tsv")[:,[0,7,8]]
        # save
        np.savetxt("../Data/ProcessedData/extracted_" + trail + "_" + str(sbjct) + ".tsv", data[sbjct-1][trail])
        print(" File saved to" + "  ../Data/ProcessedData/extracted_" + trail + "_" + str(sbjct) + ".tsv")
        np.savetxt("../Data/ProcessedData/extracted_relax" + trail + "_" + str(sbjct) + ".tsv", relax_data[sbjct-1][trail])
        print(" File saved to" + "../Data/ProcessedData/extracted_relax" + trail + "_" + str(sbjct) + ".tsv")

        # plot data (two chanel)
        figure.add_subplot(2*len(trails), 2, count) # chanel 1
        plt.plot(data[sbjct-1][trail][:, 1], linewidth=1)
        plt.title('Subject' + str(sbjct) + ' ' + trail + ' CH1')
        figure.add_subplot(2*len(trails), 2, count+1) # chanel 2
        plt.plot(data[sbjct-1][trail][:, 2], linewidth=1)
        plt.title('Subject' + str(sbjct) + ' ' + trail + ' CH2')

        figure.add_subplot(2*len(trails), 2, count + 2)  # chanel 1
        plt.plot(relax_data[sbjct-1][trail][:, 1], linewidth=1)
        plt.title('Relax ' + trail + ' CH1')
        figure.add_subplot(2*len(trails), 2, count + 3)  # chanel 2
        plt.plot(relax_data[sbjct-1][trail][:, 2], linewidth=1)
        plt.title('Relax ' + trail + ' CH2')
        count += 4

plt.show()
