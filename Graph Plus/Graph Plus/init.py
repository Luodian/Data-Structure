import networkx as nx
import matplotlib.pyplot as plt
import pickle
import random
import re

node_list = []
edge_list = []


def randomEdge(n, m):
    file = open("/Users/luodian/Desktop/DSA/Graph Plus/Graph Plus/DATA/in.txt", 'w+');
    strBuffer = str(str(n) + " " + str(m) + "\n")
    file.write(strBuffer)
    edgeSet = set(tuple())
    for i in xrange(0, m):
        u = random.randint(1, n)
        v = random.randint(1, n)
        edge_list.append((u, v))
        if (u != v and ((u, v) not in edgeSet)):
            edgeSet.add((u, v))
            strBuffer = str(str(u) + " " + str(v) + "\n")
            file.write(strBuffer)
    file.seek(0)
    strBuffer = str(str(n) + " " + str(len(edgeSet)) + "\n")
    file.write(strBuffer)


def readFile():
    file = open("//Users/luodian/Desktop/DSA/Graph Plus/Graph Plus/DATA/in.txt", 'r');
    strBuffer = file.readline()
    int_arr = re.sub("[^\w]]", " ", strBuffer).split()
    n = int(int_arr[0])
    m = int(int_arr[1])
    for i in xrange(0, m):
        strBuffer = file.readline()
        int_arr = re.sub("[^\w]]", " ", strBuffer).split()
        u = int(int_arr[0])
        v = int(int_arr[1])
        edge_list.append((u, v))
    return (n, m)


def initGraph(n, m):
    node_list = range(1, n + 1)
    G = nx.Graph()
    G.add_nodes_from(node_list)
    G.add_edges_from(edge_list)
    pos = nx.spring_layout(G)

    nx.draw(G, pos, node_size=50, node_color='azure')
    plt.show()


if __name__ == "__main__":
    # m = randomEdge(20, 30)
    (n, m) = readFile()
    initGraph(20, 30)
