from sklearn.neighbors import NearestNeighbors
import numpy as np

dim=3
k=30
it=3

file = open('galaxies.xyz', 'r')
lines = file.readlines()

data = []

for line in lines:
    data += [[float(x) for x in line.split()]]

out = open('pyout.xyz', 'w')


for j in range(it):
    X = np.array(data)
    nbrs = NearestNeighbors(n_neighbors=k, algorithm='ball_tree').fit(X)
    distances, indices = nbrs.kneighbors(X)
    ind = 0
    for row in indices:
        curr = np.array([0]*dim, dtype=float)
        for i in range(k):
            curr+=X[row[i]]
        curr /= k
        data[ind] = curr
        ind += 1

for line in data:
    for i in range(len(line)):
        out.write(str(line[i]))
        if i < len(line)-1:
            out.write(" ")
    out.write("\n")

# print(distances)
