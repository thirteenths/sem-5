import numpy as np
import matplotlib.pyplot as plt

#x = np.arange(1, 4)
#y = np.random.randint(1, 10, size = 7)

CompletBust = [3.4176e-05, 3.74649e-05, 3.80184e-05, 3.67947e-05, 1.37932e-05]
BinSearch = [1.15654e-06, 1.17931e-06, 1.17461e-06, 1.12426e-06, 9.46893e-07]
FreqAnalysis = [9.33152e-07, 9.85748e-07, 1.04804e-06, 8.90548e-07, 7.74257e-07]


#fig, ax = plt.subplots(1, 1, sharey=True, tight_layout=True)
#bins = np.linspace(-10, 10, 20)
color_rectangle = np.random.rand(7, 3)    # RGB
#ax[0].bar(x, (CompletBust[0], BinSearch[0], BinSearch[0]), color = color_rectangle)
#ax[1].bar(x, (CompletBust[1], BinSearch[1], BinSearch[1]), color = color_rectangle)
#ax[2].bar(x, (CompletBust[2], BinSearch[2], BinSearch[2]), color = color_rectangle)

#plt.hist([CompletBust, BinSearch, FreqAnalysis], label=['CompletBust', 'BinSearch', 'FreqAnalysis'])
#plt.legend(loc='upper left')
#plt.xticks(index+1.5*bw,['A','B','C','D','E'])

#fig.set_figwidth(12)    #  ширина и
#fig.set_figheight(6)    #  высота "Figure"
#fig.set_facecolor('floralwhite')
#ax[0].set_facecolor('seashell')

#plt.show()

t = ['first key', 'averege key', 'last key', 'random key', ' not exist key']

index = np.arange(5)
values1 = [5,7,3,4,6]
values2 = [6,6,4,5,7]
values3 = [5,6,5,4,6]
bw = 0.3
plt.axis([-0.5,5,0,3.8e-05])

plt.figure(figsize=(8, 6), dpi=80)

plt.title('Temporary characteristics', fontsize=20)
plt.bar(index, CompletBust, bw, color='b')
plt.bar(index+bw, BinSearch, bw, color='g')
plt.bar(index+2*bw, FreqAnalysis, bw, color='r')
plt.xticks(index+1.5*bw,t)
plt.show()