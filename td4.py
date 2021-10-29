import matplotlib.pyplot as plt
import numpy as np
from scipy.fft import fft

N = 128
m = 300
f1 = 400
f2 = 420
A1 = 3
A2 = 5
fe = 2000

Lt = [t/fe for t in range(N)]
Lsin = [A1*np.sin(2*np.pi*f1*t) + A2*np.sin(2*np.pi*f2*t) for t in Lt]
LsinPadded = [A1*np.sin(2*np.pi*f1*t) + A2*np.sin(2*np.pi*f2*t) for t in Lt] + [0 for i in range(m)]


Lf = [t*fe/(N) for t in range(N)]
LfPadded = [t*fe/(N+m) for t in range(N+m)]
Lfft = fft(Lsin)
LfftPadded = fft(LsinPadded)

plt.subplot(211)
plt.plot(Lf, abs(Lfft/N))
plt.xlim(200, 600)

plt.subplot(212)
plt.plot(LfPadded, abs(LfftPadded/N))
plt.xlim(200, 600)

plt.show()


