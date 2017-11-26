import urllib2
import time
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm

#number of points
n = 100

#declare a 2D array to hold data points
data = np.zeros((n,3))
counter=0

#read from server
while(True):
	#access the server
	f = urllib2.urlopen('http://10.25.2.118:8080')
	#read input string
	inStr = f.read()
	#convert string into list of strings
	inStrL = inStr.split()
	inStrF = []

	print(inStrL)
	#create a list of floats to hold a_x, a_y, a_z, R
	for i in range(4):
		inStrF.append(float(inStrL[i]))
		
	#for every input string
	if(counter <n):
		#extract variable from list the variables
		a_x=inStrF[0]
		a_y=inStrF[1]
		a_z=inStrF[2]
		R=inStrF[3]
		#Calculate Pitch and Roll angles PHI and THETA
		PHI = np.arctan2(a_y, a_z) * 180/np.pi
		THETA = np.arctan2(a_x, np.sign(a_z)*np.sqrt(np.power(a_y,2) + np.power(a_z,2)))*180/np.pi
		
		#convert to X,Y,Z cartesian coordinates
		data[counter][0] = R * np.sin(PHI) * np.cos(THETA)
		data[counter][1] = R * np.sin(PHI) * np.sin(THETA)
		data[counter][2] = R * np.cos(PHI)
		#increment counter to keep track of the number of points
		counter +=1
	else:
		break
		#update every 0.2 seconds
	time.sleep(0.5)
		
print(data)
#extract X,Y,Z point space
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

