import numpy as np
import matplotlib.pyplot as plt

X = np.array([201, 175, 151, 125, 101, 75, 51, 25, 31, 0])
Y = np.array([11600, 9600, 6200, 4450, 2900, 1640, 747, 168, 264, 0])


plt.grid(True)
plt.errorbar(X, Y, color='green', marker='v', linestyle='none')
p, v = np.polyfit(X, Y, deg=2, cov=True)
print("x2:", p[0], "+-", np.sqrt(v[0][0]),"\n",
      "x:", p[1], "+-", np.sqrt(v[1][1]),"\n",
        "Значение в нуле:", p[2], "+-",np.sqrt(v[2][2]))
title = str(r'$ T \sim n^2$')
plt.title(title)
plt.xlabel(r'$n \quad  (сторона квадрата)$')
plt.ylabel(r'$Т \quad  (количество шагов)$')
plt.plot(X, p[0]*X**2+p[1]*X**1+p[2])

plt.savefig('gr1.pdf')
#plt.show()

