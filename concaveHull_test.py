import numpy as np
import matplotlib.pyplot as plt



##x=np.loadtxt('xx.txt')
##y=np.loadtxt('yy.txt')



x, y=np.loadtxt('p.txt',unpack=True)
xx, yy=np.loadtxt('pCH.txt',unpack=True)

    
plt.scatter(x,y)
plt.plot(xx, yy, c='red')
plt.scatter(xx,yy,c='red',s=10)

##for i in [0,9,19,29,39,49,59,69,79,89,99,109,119,129,139,149,159]:
##    plt.scatter(xx[i],yy[i],c='green')

plt.show()





