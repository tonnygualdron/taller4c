import matplotlib.pyplot as plt
import numpy as np

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











    



