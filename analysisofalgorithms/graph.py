# # !/usr/bin/python
# # -*- coding: utf-8 -*-
import matplotlib.pyplot as plt

lenStr = [100, 500, 1000, 2000, 3000]

#Bubble = [2.5701e-08, 1.06766e-06, 2.467561e-06, 2.30337e-05, 0.0219477, 42.0425]

#Insert = [1.3292e-08, 4.6446e-07, 1.01595e-06, 9.42429e-06 , 0.00947836, 10.3583]

#Shacker = [1.4298e-08, 4.9508e-07, 1.19424e-06, 1.08025e-05, 0.0105426, 25.831]

#Bubble = [2.4857e-08, 1.55071e-06, 2.21443e-06, 2.11861e-05, 0.0211227, 21.1897]

#Insert = [1.4997e-08, 4.364e-07, 1.19455e-06, 9.70069e-06, 0.00939746, 9.04181]

#Shaker = [1.7846e-08, 6.3083e-07, 1.20394e-06, 1.07621e-05, 0.0105984, 10.4366]

#Bubble = [2.4734e-08, 9.6256e-07, 2.14968e-06, 2.11855e-05, 0.021119, 37.8792]

#Insert = [1.2523e-08, 4.4005e-07, 1.22781e-06, 9.45353e-06, 0.00951246, 11.9067]

#Shaker = [1.3225e-08, 5.0671e-07, 1.36617e-06, 1.10513e-05, 0.0105476, 26.5102]


CompleteBust = [3.29358e-05, 8.37049e-06, 3.67731e-06, 2.23531e-06, 1.35468e-06]
BinSearch = [1.25649e-06, 3.21602e-07, 1.20759e-07, 6.02785e-08, 4.04583e-08]
FreqAnalysis = [1.86112e-06, 2.60602e-07, 9.9533e-08, 4.93705e-08, 3.46913e-08]

fig, ax = plt.subplots()

ax.plot(lenStr, CompleteBust, label="CompleteBust")

ax.plot(lenStr, BinSearch, label="BinSearch")

ax.plot(lenStr, FreqAnalysis, label="FreqAnalysis")

ax.legend()
ax.grid()
ax.set_xlabel('Размерность массива')
ax.set_ylabel('Время (с)')

plt.show()