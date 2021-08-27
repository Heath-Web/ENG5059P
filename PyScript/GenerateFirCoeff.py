#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Generate the coefficient of fir filter for pre-filtering (Remove DC and 50HZ).
The coefficients will be save to "firCoefficient.dat".

@:return plot1, plot2: figures of frequency response and impulse response
"""
import scipy.signal as sig
import numpy as np
import matplotlib.pylab as plt

# define Sampling rate and n-taps
fs = 250
ntaps = 250
cf = np.arange(0, ntaps/2 + 1, 1) / fs * 2

# generate coefficient for channel 1
ch1_fir_coefficient = sig.firwin(ntaps-1, [cf[2], cf[45], cf[55]], window='hamming', pass_zero=False)
# generate coefficient for channel 2
<<<<<<< HEAD
ch2_fir_coefficient = sig.firwin(ntaps-1, [cf[5], cf[45], cf[55]], window='hamming', pass_zero=False)
=======
ch2_fir_coefficient = sig.firwin(ntaps-1, [cf[10], cf[45], cf[55]], window='hamming', pass_zero=False)
>>>>>>> dev
# Save
np.savetxt('../CH1firCoeff.dat', ch1_fir_coefficient)
np.savetxt('../CH2firCoeff.dat', ch2_fir_coefficient)


# plot frequency domain and time domain
fft1 = np.fft.fft(ch1_fir_coefficient)
fig1 = plt.figure("Fir coefficient for channel 1")
ax1 = fig1.add_subplot(121)
plot1 = ax1.plot(np.real(fft1))
plt.title("Frequency domain")
ax2 = fig1.add_subplot(122)
plot2 = ax2.plot(ch1_fir_coefficient)
plt.title("Time domain")

fft2 = np.fft.fft(ch2_fir_coefficient)
fig2 = plt.figure("Fir coefficient for channel 2")
ax3 = fig2.add_subplot(121)
ax3.plot(np.real(fft2))
plt.title("Frequency domain")
ax4 = fig2.add_subplot(122)
ax4.plot(ch2_fir_coefficient)
plt.title("Time domain")

plt.show()

