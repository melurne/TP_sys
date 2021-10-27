from math import pi, cos
import matplotlib.pyplot as plt

an = lambda n: 2/(n*pi)

def carre(iterat, t, moy, f):
	out = moy
	for i in range(1, iterat):
		out = out + an(2*i+1)*cos(2*pi*(2*i+1)*t*f)

a = -20
b = 20
N = 10000
iterat = 3

tabt = [t*(b-a)/N + a for t in range(N)]
tabcarre = [carre(iterat, t, 0.5, 0.5) for t in tabt]

plt.plot(tabt, tabcarre, 'b-')
plt.show()
