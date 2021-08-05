import matplotlib.pyplot as plt 
import numpy as np

# Load raw data and extract the three relevant columns (time, ch1 and ch2 of ADC)
data_arm_1 = np.loadtxt("../RawData/data_arm_1.tsv")[:,[0,7,8]]
data_arm_2 = np.loadtxt("../RawData/data_arm_2.tsv")[:,[0,7,8]]
data_wrist_1 = np.loadtxt("../RawData/data_wrist_1.tsv")[:,[0,7,8]]
data_wrist_2 = np.loadtxt("../RawData/data_wrist_2.tsv")[:,[0,7,8]]
relax_arm = np.loadtxt("../RawData/relax_arm.tsv")[:,[0,7,8]]
relax_wrist = np.loadtxt("../RawData/relax_wrist.tsv")[:,[0,7,8]]

# specific data
signal_arm_1 = data_arm_1[:,1]
noise_arm_1 = data_arm_1[:,2]
signal_arm_2 = data_arm_2[:,1]
noise_arm_2 = data_arm_2[:,2]
signal_wrist_1 = data_wrist_1[:,1]
noise_wrist_1 = data_wrist_1[:,2]
signal_wrist_2 = data_wrist_2[:,1]
noise_wrist_2 = data_wrist_2[:,2]
signal_arm_relax = relax_arm[:,1]
noise_arm_relax = relax_arm[:,2]
signal_wrist_relax = relax_wrist[:,1]
noise_wirst_relax = relax_wrist[:,2]

# plot
figure = plt.figure('Raw data')
figure.add_subplot(621)
plt.plot(signal_arm_1, linewidth=1)
plt.title('1.Ch1 signal --arm')
figure.add_subplot(622)
plt.plot(noise_arm_1, linewidth=1)
plt.title('1.Ch2 noise --arm')

figure.add_subplot(623)
plt.plot(signal_arm_2, linewidth=1)
plt.title('2.Ch1 signal --arm')
figure.add_subplot(624)
plt.plot(noise_arm_2, linewidth=1)
plt.title('2.Ch2 noise --arm')

figure.add_subplot(625)
plt.plot(signal_wrist_1, linewidth=1)
plt.title('1.Ch1 signal --wrist')
figure.add_subplot(626)
plt.plot(noise_wrist_1, linewidth=1)
plt.title('1.Ch2 noise --wrist')

figure.add_subplot(627)
plt.plot(signal_wrist_2, linewidth=1)
plt.title('2.Ch1 signal --wrist')
figure.add_subplot(628)
plt.plot(noise_wrist_2, linewidth=1)
plt.title('2.Ch2 noise --wrist')

figure.add_subplot(629)
plt.plot(signal_arm_relax, linewidth=1)
plt.title('Ch1 signal -- relax arm')
figure.add_subplot(6,2,10)
plt.plot(noise_arm_relax, linewidth=1)
plt.title('Ch2 noise -- relax arm')

figure.add_subplot(6,2,11)
plt.plot(signal_wrist_relax, linewidth=1)
plt.title('Ch1 signal -- relax wrist')
figure.add_subplot(6,2,12)
plt.plot(noise_wirst_relax, linewidth=1)
plt.title('Ch2 noise -- relax wrist')

plt.show()