import numpy as np
import matplotlib.pyplot as plt

Y2 = np.array([19442.8, 10458.2, 6408.88, 4615.06, 3445.25, 2747.53, 2113.6,
        1721.11, 1433.89, 1206.26, 1054.73, 882.552, 831.18, 736.72, 630.974,
        578.886, 522.06, 477.8, 431.152, 419.05, 353.374, 322.178, 315.81, 278.368,
        243.93, 233.636, 211.664, 200.99, 196.75, 177.83, 164.894, 146.678, 138.322,
        130.12, 133.8, 110.89, 112.254, 104.444, 102.264, 89.686, 88.898, 85.194, 74.266,
        72.52, 67.812, 63.252, 57.868, 53.036, 52.96, 50.186, 44.896, 45.536, 42.464,
        39.77, 36.726, 35.066, 33.444, 30.172, 29.766, 27.208, 27.776, 24.882, 23.574,
        21.394, 19.624, 18.502, 18.686, 16.584, 16.156, 14.47, 13.808, 12.98, 11.738,
        11.254, 10.142, 9.644, 9.038, 8.406, 8.15, 6.97, 6.03, 5.38, 5.302, 5.174, 4.394,
        3.732, 3.284, 3.056, 2.398, 2.176, 1.864, 1.59, 1.298, 1.168, 0.832, 0.608, 0.366,
        0.2, 0.034])
X2 = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
               21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
               39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56,
               57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
               75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92,
               93, 94, 95, 96, 97, 98, 99])


plt.grid(True)
plt.errorbar(X2, Y2, color='green', marker='v', linestyle='none')
plt.xlabel(r'$\nu \quad  (концентрация)$')
plt.ylabel(r'$Т \quad  (количество шагов)$')
plt.savefig('gr3_2.pdf')
plt.show()
