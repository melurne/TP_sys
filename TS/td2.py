import matplotlib.pyplot as plt
import numpy as np

t0, t1 = 0, 1.5
N = 1e4

def x(t, Tl) :
	out = [0 for i in t]
	for i in range(len(t)) :
		for k in range(len(Tl))	:
			out[i] += Tl[k]*np.sinc(np.pi*(k-2*t[i]))		
	return out

def signal(Ts) :
	Tl = [2*np.pi*(t0 + t*Ts) for t in range(int(t1/Ts)+1)]
	Tex = [2*np.pi*(t0 + t*1e-3) for t in range(int(t1/1e-3)+1)]
	plt.plot(Tex, np.sin(Tex), 'k--')
	plt.plot(Tex, x(Tex, Tl), 'g-')
	plt.plot(Tl, np.sin(Tl), 'bo')

signal(0.4)

#signal(3, 'r*')
plt.show()
