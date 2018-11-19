import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import math

data = np.loadtxt("45grados.txt")
x = data[:,1]
y = data[:,2]
t = data[:,0]

plt.plot(x,y)
plt.show()

plt.plot(t,x)
plt.show()

plt.plot(t,y)
plt.show()

import time
data1 = np.loadtxt("caso11.txt")
j = 0
data3=[]
for i in range(31):
    data2 = []
    while j < (i+1)*103:
        data2.append(data1[j,:])
        j=j+1
    data3.append(data2)

fig = plt.figure()
ax = fig.add_subplot(111)
im = ax.imshow(data3[0]))
plt.show(block=False)
for i in range(31):
    # wait for a second
    time.sleep(0.1)
    # replace the image contents
    im.set_array(data3[i])
    # redraw the figure
    fig.canvas.draw()
    print(i)

from mpl_toolkits.mplot3d import Axes3D

X = np.linspace(0,0.5,103)
Y =  np.linspace(0,0.5,103)
X, Y = np.meshgrid(X, Y)
Z = np.asarray(data3[0])
fig = plt.figure() 
ax = fig.gca(projection='3d')
surf = ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=plt.cm.jet, linewidth=0.01, antialiased=False)
plt.show(block=False)
# draw some data in loop
for i in range(31):
    # wait for a second
    time.sleep(0.00001)
    # replace the image contents
    surf = ax.plot_surface(X, Y, np.asarray(data3[i]), rstride=1, cstride=1, cmap=plt.cm.jet, linewidth=0.01, antialiased=False)
    # redraw the figure
    fig.canvas.draw()
    print(i)
plt.savefig("lalala.gif")
plt.close()







    



