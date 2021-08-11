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

# generate coefficient
fir_coefficient = sig.firwin(ntaps-1, [cf[5], cf[45], cf[55]], window='hamming', pass_zero=False)
# Save
np.savetxt('../firCoefficient.dat', fir_coefficient)

# plot frequency domain and time domain
fft = np.fft.fft(fir_coefficient)
fig1 = plt.figure(1)
ax1 = fig1.add_subplot(121)
plot1 = ax1.plot(np.real(fft))
plt.title("Frequency domain")

ax2 = fig1.add_subplot(122)
plot2 = ax2.plot(fir_coefficient)
plt.title("Time domain")
plt.show()

