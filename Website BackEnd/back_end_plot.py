import numpy as np
import urlib2
import time

#number of points
n = 10

#declare a "D array to hold data points
data = np.zeros((n,3))
counter=0

#read from server
while(True):
	f = urlib2.urlopen('http://10.25.2.118:8080')
	inStr = f.read()
	inStrL = inStr.split()
	inStrF = []

	print(inStrL)
	for i in range(3):
		inStrF.append(float(inStrL[i]))
		

	if(counter <n):
		X=inStrF[0]
		Y=inStrF[1]
		Z=inStrF[2]
		data[counter][0] = X
		data[counter][1] = Y
		data[counter][2] = Z
		counter +=1
	else:
		break
	
print(data)






	
	
