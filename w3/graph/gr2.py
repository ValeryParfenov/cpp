import numpy as np
import matplotlib.pyplot as plt

X1 = np.array([1, 2, 5, 20, 10, 30, 40, 50, 60, 70, 80, 90, 100])
Y = np.array([1204, 679, 274, 48, 124, 25, 14, 8, 5, 3, 1.16, 0.58, 0])
X = 1/X1

plt.grid(True)
plt.errorbar(X, Y, color='green', marker='v', linestyle='none')
title = str(r'$ T \sim \nu^{-1}$')
p, v = np.polyfit(X, Y, deg=1, cov=True)
plt.xlabel(r'$\nu^{-1} \quad  (концентрация)^{-1}$')
plt.ylabel(r'$Т \quad  (количество шагов)$')
plt.plot(X, p[0]*X+p[1])
plt.title(title)
plt.savefig('gr2_2.pdf')
plt.show()