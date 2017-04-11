import random
import re

node_list = []
edge_list = []


def randomEdge(filepath,n, m):
    file = open(filepath, 'w+');
    strBuffer = str(str(n) + " " + str(m) + "\n")
    file.write(strBuffer)
    edgeSet = set(tuple())
    for i in xrange(0, m):
        u = random.randint(1,n)
        v = random.randint(1, n)
        w = random.randint(1,1000)
        edge_list.append((u, v))
        if (u != v and ((u, v) not in edgeSet)):
            edgeSet.add((u, v))
            strBuffer = str(str(u) + " " + str(v) + " " + str(w) + "\n")
            file.write(strBuffer)
    file.seek(0)
    strBuffer = str(str(n) + " " + str(len(edgeSet)) + "\n")
    file.write(strBuffer)

if __name__ == "__main__":
    randomEdge("/Users/luodian/Desktop/DSA/MST/MST/DATA/bigdata.txt" ,50, 200)
