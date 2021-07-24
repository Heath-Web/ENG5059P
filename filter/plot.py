import pylab as pl
import numpy as np
import matplotlib.pyplot as plt

ecg = np.loadtxt("ecg50hz.dat")
plt.figure()
plt.plot(ecg)

ecg2 = np.loadtxt("ecg_filtered.dat")
plt.figure()
plt.plot(ecg2[200:1000,1])


plt.figure()
plt.plot(ecg2[:,0])
plt.show()