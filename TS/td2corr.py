import numpy as np
import matplotlib.pyplot as plt

fig, ax = plt.subplots()

f = 1.0
fs = 3.0
t = np.linspace(-1, 1, 100)
ts = np.arange(-1, 1+1/fs, 1/fs)

num_coeffs=len(ts)
sm=0

for k in range(-num_coeffs, num_coeffs) :
	sm+=np.sin(2*np.pi*(k/fs))*np.sinc(k-fs*t)

ax.plot(t, sm, '--', t, np.sin(2*np.pi*t), ts, np.sin(2*np.pi*ts), 'o')

plt.show()
