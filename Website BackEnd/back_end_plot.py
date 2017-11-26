#import urlib2
#import time
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm

#number of points
n = 10

#declare a "D array to hold data points
data = np.zeros((n,3))
counter=0

		
while(counter <n):
	X=np.random.randint(0,5)
	Y=np.random.randint(10,15)
	Z=np.random.randint(10,16)
	data[counter][0] = X
	data[counter][1] = Y
	data[counter][2] = Z
	counter +=1


print(data)

Xs = data[:,0]
Ys = data[:,1]
Zs = data[:,2]


# ======
## plot:
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

surf = ax.plot_trisurf(Xs, Ys, Zs, linewidth=0)


fig.tight_layout()

plt.show() # or:


