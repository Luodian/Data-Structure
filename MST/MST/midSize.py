import matplotlib
matplotlib.use('Agg')
import networkx as nx
import matplotlib.pyplot as plt
import pickle
import random
import re

node_list = []
edge_list = []

color_edge_list = []


def readFile(filepath):
    file = open(filepath, 'r')
    strBuffer = file.readline()
    int_arr = re.sub("[^\w]]", " ", strBuffer).split()
    n = int(int_arr[0])
    m = int(int_arr[1])
    for i in xrange(0, m):
        strBuffer = file.readline()
        int_arr = re.sub("[^\w]]", " ", strBuffer).split()
        u = int(int_arr[0])
        v = int(int_arr[1])
        w = int(int_arr[2])
        edge_list.append((u, v, w))
    return (n, m)

def readSelectedFile(filepath):
    file = open(filepath,"r")
    strBuffer = file.readline()
    int_arr = re.sub("[^\w]]", " ", strBuffer).split()
    m  = int(int_arr[0])
    for i in xrange (0,m):
        strBuffer = file.readline()
        int_arr = re.sub("[^\w]]", " ", strBuffer).split()
        u = int(int_arr[0])
        v = int(int_arr[1])
        w = int(int_arr[2])
        color_edge_list.append((u,v,w))
    return m

def midGraph(n, m):
    node_list = range(1, n + 1)
    plt.figure(1, figsize=(10, 10))
    G = nx.Graph()
    G.add_nodes_from(node_list)
    G.add_weighted_edges_from(edge_list)
    pos = nx.random_layout(G)

    edge_labels = {(n1, n2): G[n1][n2]['weight'] for (n1, n2) in G.edges()}

    uncolor_set = set()
    color_set = set()

    for element in color_edge_list:
        color_set.add(element)

    for element in edge_list:
        if (element not in color_set):
            uncolor_set.add(element)

    uncolor_list = list(uncolor_set)
    color_list = list(color_set)
    nx.draw_networkx_edges(G,pos,edgelist = uncolor_list , edge_color = 'slategray',width = 0.6,alpha = 1)

    nx.draw_networkx_edges(G,pos,edgelist = color_list ,edge_color = 'orangered',width = 0.6,alpha = 1)

    nx.draw_networkx_nodes(G, pos, nodelist = node_list,node_size = 50,vmin = 0,vmax = 1.0,node_color='azure')

    # nx.draw_networkx_labels(G,pos)
    # nx.draw_networkx_edge_labels(G,pos,edge_labels = edge_labels,label_pos = 0.2)
    font = {'color'      : 'k',
            'fontweight' : 'bold',
            'fontsize'   : 14}
    plt.title("The graph and mst info",font)

    plt.annotate('The selected edge',(0.8,1.25))
    plt.plot([0.75],[1.2666],color = 'orangered',marker = 'o',markersize = 15)
    plt.axis("off")
    plt.savefig("MST_mid.png",dpi = 233)
    plt.show()


if __name__ == "__main__":
    (n, m) = readFile("/Users/luodian/Desktop/DSA/MST/MST/DATA/middata.txt")
    m = readSelectedFile("/Users/luodian/Desktop/DSA/MST/MST/DATA/mid_selected_edge.txt")
    midGraph(n, m)
