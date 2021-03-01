from __future__ import print_function
import numpy as np
import matplotlib.pyplot as plt
np.random.seed(11)
#!/usr/bin/python
f = open('Data/file_2.txt', 'r')
f_location = open('Data/location.txt', 'r')

string = f.read()
str = string.split()
num_of_node = int(str[0])

string2 = f_location.read()
str2 = string2.split()

X1 = []
X2 = []

for a in str2:
    X2.append(float(a))
loc = []
M = len(X2)
for i in range(M):
    if(i % 3 == 0):
        a = []
        a.append(int(X2[i]))
        a.append(X2[i + 1])
        a.append(X2[i + 2])
        loc.append(a)
        
for i in range(1, num_of_node * 2, 2):
    X1.append([int(str[i]), int(str[i + 1])])


def Location(X):
    for i in range(int(M / 3)):
        k = X[i][0]
        x1 = X[i][1]
        y1 = X[i][2]
        if k == 1:
            plt.plot(x1, y1, 'g^', markersize = 3, alpha = .8)
        if k == 2:
            plt.plot(x1, y1, 'bs', markersize = 6, alpha = .8)
    #plt.xlabel('EVRP', color = 'purple')
    #plt.axis('equal')
    #plt.plot(X[:, 0], X[:, 1])
    #plt.show()

def display(X2):
    for i in range(num_of_node - 1):
        x1, y1, x2, y2 = X2[i][0], X2[i][1], X2[i + 1][0], X2[i + 1][1]
        plt.plot([x1, x2], [y1, y2], color = 'tomato', linewidth = 1)
        #print(x1, y1, x2, y2)
    #plt.xlabel('EVRP', color = 'purple')
   #plt.xlabel('Generation', color = 'black')
    #plt.ylabel('Tour length', color = 'black')
    #plt.show()
    plt.plot(loc[0][1], loc[0][2], 'ro', markersize = 7, alpha = .8)
    plt.savefig('n459k26_graph.pdf',bbox_inches='tight')
    #plt.axis('equal')
    #plt.plot(X[:, 0], X[:, 1])
    #plt.show()

Location(loc)
display(X1)