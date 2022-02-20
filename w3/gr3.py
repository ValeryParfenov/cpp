import numpy as np
import matplotlib.pyplot as plt

X = np.array([21, 41, 61, 81, 101, 121, 141, 161, 181, 201, 221, 241, 261, 281, 301, 321, 341, 361, 381, 401, 421, 441, 461, 481, 501,
 521, 541, 561, 581, 601, 621, 641, 661, 681, 701, 721, 741, 761])
Y = np.array([92, 405, 962, 1619, 2402, 3616, 5031, 6315, 8222, 10549, 11923, 14024, 17086, 19326, 21626, 24848, 27571, 32564, 36430,
40724, 43413, 46676, 54187, 57291, 62781, 67856, 71286, 82714, 87045, 91684, 94334,	 103259, 108710, 114784, 124348, 129037, 135051, 138779])


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

plt.savefig('gr3.pdf')
plt.show()
