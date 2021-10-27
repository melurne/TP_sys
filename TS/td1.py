R=3

F1 = lambda x: (R+1)*x - R*(x*x)
F2 = lambda x: R*x*(1-x) + x
F3 = lambda x: x*(R+1) - (R*x)*x

x1 = 0.5
x2 = 0.5
x3 = 0.5


for i in range(2500):
	x1 = F1(x1)
	x2 = F2(x2)
	x3 = F3(x3)

print(x1)
print(x2)
print(x3)
