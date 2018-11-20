import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import imageio
from os import remove

data = np.loadtxt("45grados.txt")
x = data[:,1]
y = data[:,2]
t = data[:,0]

data1070 = np.loadtxt("10-70grados.txt")
data1070V =[]

plt.plot(x,y)
plt.xlabel("X")
plt.ylabel("Y")
plt.savefig("45grados.jpg")
plt.close()

actual2=[]
for i in range(len(data1070[:,1])):
    actual=data1070[i,:]
    if(actual[0]==999):
        data1070V.append(actual2)
        actual2 = []
    else:
        actual2.append(actual)
for i in range(7):
    M=np.asarray(data1070V[i])
    l=(i+1)*10
    plt.plot(M[:,1],M[:,2], label=str(l))

plt.xlabel("X")
plt.ylabel("Y")
plt.legend()
plt.savefig("10-70grados.jpg") 
plt.close() 

data1 = np.loadtxt("caso1.txt")
data11 = np.loadtxt("caso11.txt")
data1T = np.loadtxt("Caso1T.txt")

j = 0
data1A=[]
for i in range(4):
    dataActual = []
    while j < (i+1)*103:
        dataActual.append(data1[j,:])
        j=j+1
    data1A.append(dataActual)

j = 0
data11A=[]
for i in range(int(len(data11[:,0])/103)):
    dataActual = []
    while j < (i+1)*103:
        dataActual.append(data11[j,:])
        j=j+1
    data11A.append(dataActual)

X = np.linspace(0,0.5,103)
Y =  np.linspace(0,0.5,103)
X, Y = np.meshgrid(X, Y)


for i in range(4):
    Z = np.asarray(data1A[i])
    fig = plt.figure() 
    ax = fig.gca(projection='3d')
    surf = ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=plt.cm.jet, linewidth=0.01, antialiased=False)
    if(i==0):
        plt.savefig("Caso1t0.jpg")
        plt.close()
    if(i==1):
        plt.savefig("Caso1t1.jpg")
        plt.close()
    if(i==2):
        plt.savefig("Caso1t2.jpg")
        plt.close()
    if(i==3):
        plt.savefig("Caso1t.jpg")
        plt.close()

plt.plot(data1T[:,0],data1T[:,1])
plt.xlabel("Tiempo (s)")
plt.ylabel("Temperatura [k]")
plt.savefig("Caso1Tprom.jpg")
plt.close()

filenames = []

for i in range(int(len(data11[:,0])/103)):
    filenames.append(str(i)+".jpg")

for i in range(int(len(data11[:,0])/103)):
    Z = np.asarray(data11A[i])
    fig = plt.figure() 
    ax = fig.gca(projection='3d')
    surf = ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=plt.cm.jet, linewidth=0.01, antialiased=False)
    plt.savefig(filenames[i])
    plt.close()

images=[]
for i in range(int(len(data11[:,0])/103)):
    images.append(imageio.imread(filenames[i]))

imageio.mimsave('movie.gif', images)

for i in range(int(len(data11[:,0])/103)):
    remove(filenames[i])

##########################################################################################################

data1 = np.loadtxt("caso2.txt")
data11 = np.loadtxt("caso22.txt")
data1T = np.loadtxt("Caso2T.txt")

j = 0
data1A=[]
for i in range(4):
    dataActual = []
    while j < (i+1)*103:
        dataActual.append(data1[j,:])
        j=j+1
    data1A.append(dataActual)

j = 0
data11A=[]
for i in range(int(len(data11[:,0])/103)):
    dataActual = []
    while j < (i+1)*103:
        dataActual.append(data11[j,:])
        j=j+1
    data11A.append(dataActual)

X = np.linspace(0,0.5,103)
Y =  np.linspace(0,0.5,103)
X, Y = np.meshgrid(X, Y)


for i in range(4):
    Z = np.asarray(data1A[i])
    fig = plt.figure() 
    ax = fig.gca(projection='3d')
    surf = ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=plt.cm.jet, linewidth=0.01, antialiased=False)
    if(i==0):
        plt.savefig("Caso2t0.jpg")
        plt.close()
    if(i==1):
        plt.savefig("Caso2t1.jpg")
        plt.close()
    if(i==2):
        plt.savefig("Caso2t2.jpg")
        plt.close()
    if(i==3):
        plt.savefig("Caso2t.jpg")
        plt.close()

plt.plot(data1T[:,0],data1T[:,1])
plt.xlabel("Tiempo (s)")
plt.ylabel("Temperatura [k]")
plt.savefig("Caso2Tprom.jpg")
plt.close()

filenames = []

for i in range(int(len(data11[:,0])/103)):
    filenames.append(str(i)+".jpg")

for i in range(int(len(data11[:,0])/103)):
    Z = np.asarray(data11A[i])
    fig = plt.figure() 
    ax = fig.gca(projection='3d')
    surf = ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=plt.cm.jet, linewidth=0.01, antialiased=False)
    plt.savefig(filenames[i])
    plt.close()

images=[]
for i in range(int(len(data11[:,0])/103)):
    images.append(imageio.imread(filenames[i]))

imageio.mimsave('movie2.gif', images)

for i in range(int(len(data11[:,0])/103)):
    remove(filenames[i])

############################################################################################################

data1 = np.loadtxt("caso3.txt")
data11 = np.loadtxt("caso33.txt")
data1T = np.loadtxt("Caso3T.txt")

j = 0
data1A=[]
for i in range(4):
    dataActual = []
    while j < (i+1)*103:
        dataActual.append(data1[j,:])
        j=j+1
    data1A.append(dataActual)

j = 0
data11A=[]
for i in range(int(len(data11[:,0])/103)):
    dataActual = []
    while j < (i+1)*103:
        dataActual.append(data11[j,:])
        j=j+1
    data11A.append(dataActual)

X = np.linspace(0,0.5,103)
Y =  np.linspace(0,0.5,103)
X, Y = np.meshgrid(X, Y)


for i in range(4):
    Z = np.asarray(data1A[i])
    fig = plt.figure() 
    ax = fig.gca(projection='3d')
    surf = ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=plt.cm.jet, linewidth=0.01, antialiased=False)
    if(i==0):
        plt.savefig("Caso3t0.jpg")
        plt.close()
    if(i==1):
        plt.savefig("Caso3t1.jpg")
        plt.close()
    if(i==2):
        plt.savefig("Caso3t2.jpg")
        plt.close()
    if(i==3):
        plt.savefig("Caso3t.jpg")
        plt.close()

plt.plot(data1T[:,0],data1T[:,1])
plt.xlabel("Tiempo (s)")
plt.ylabel("Temperatura [k]")
plt.savefig("Caso3Tprom.jpg")
plt.close()

filenames = []

for i in range(int(len(data11[:,0])/103)):
    filenames.append(str(i)+".jpg")

for i in range(int(len(data11[:,0])/103)):
    Z = np.asarray(data11A[i])
    fig = plt.figure() 
    ax = fig.gca(projection='3d')
    surf = ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=plt.cm.jet, linewidth=0.01, antialiased=False)
    plt.savefig(filenames[i])
    plt.close()

images=[]
for i in range(int(len(data11[:,0])/103)):
    images.append(imageio.imread(filenames[i]))

imageio.mimsave('movie3.gif', images)

for i in range(int(len(data11[:,0])/103)):
    remove(filenames[i])

remove("caso3.txt")
remove("caso1.txt")
remove("caso2.txt")
remove("caso33.txt")
remove("caso11.txt")
remove("caso22.txt")
remove("Caso3T.txt")
remove("Caso1T.txt")
remove("Caso2T.txt")
remove("45grados.txt")
remove("10-70grados.txt")
