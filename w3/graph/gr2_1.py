import numpy as np
import matplotlib.pyplot as plt

X = np.array([1, 2, 5, 20, 10, 30, 40, 50, 60, 70, 80, 90, 100])
Y = np.array([1204, 679, 274, 48, 124, 25, 14, 8, 5, 3, 1.16, 0.58, 0])


plt.grid(True)
plt.errorbar(X, Y, color='green', marker='v', linestyle='none')
plt.xlabel(r'$\nu \quad  (концентрация)$')
plt.ylabel(r'$Т \quad  (количество шагов)$')
plt.savefig('gr2_1.pdf')
plt.show()

