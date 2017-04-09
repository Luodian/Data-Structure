import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import networkx as nx
import re
import random
import matplotlib.patches as mpc


def readRawFile(filename, Raw_edge):
    file = open(filename)
    print "Name of file: ", file.name
    line = file.readline()
    line_arr = re.sub("[^\w]]", " ", line).split()
    int_arr = []
    for element in line_arr:
        int_arr.append(int(element))
    n = int_arr[0]
    m = int_arr[1]
    for i in xrange(0, m):
        line = file.readline()
        line_arr = []
        line_arr = re.sub("[^\w]]", " ", line).split()
        int_arr = []
        for element in line_arr:
            int_arr.append(int(element))

        u = int_arr[0]
        v = int_arr[1]
        Raw_edge.append((u, v))
    return n


def readBccFile(filename, Bcc_matrix, cut_arr):
    file = open(filename)
    print "Name of file: ", file.name
    line = file.readline()
    cut_num = int(line[0])
    line = file.readline()
    line_arr = re.sub("[^\w]]", " ", line).split()
    for element in line_arr:
        cut_arr.append(int(element))

    line = file.readline()
    bcc_num = int(line)
    for i in xrange(0, bcc_num):
        bcc_array = []
        line = file.readline()
        int_arr = re.sub("[^\w]", " ", line).split()
        for element in int_arr:
            bcc_array.append(int(element))
        Bcc_matrix.append(bcc_array)


def plot():
    # set default color
    #colors = ['brown', 'r', 'b', 'oldlace', 'yellowgreen', 'teal', 'tomato', 'palegreen', 'cornsilk', 'pink', 'crimson', 'darkgreen', 'hotpink', 'gray', 'green', 'gold', 'beige', 'bisque']
    colors = [(0., 1, 1),(0.05, 1, 1),(0.11, 0, 0),(0.66, 1, 1),(0.89, 1, 1),(1, 0.5, 0.5),(0, 1, 1),(0.05, 1, 1),(0.11, 0, 0),(0.375, 1, 1),(0.64, 1, 1),(0.91, 0, 0),(1, 0, 0),(0., 1, 1),
             (0.05, 1, 1),
             (0.11, 1, 1),
             (0.34, 1, 1),
             (0.65, 0, 0),
             (1, 0, 0)]

    Raw_edge = []
    Bcc_matrix = []
    cut_arr = []
    n = readRawFile("/Users/luodian/Desktop/DSA/Graph Plus/Graph Plus/DATA/in.txt", Raw_edge)
    readBccFile("/Users/luodian/Desktop/DSA/Graph Plus/Graph Plus/DATA/Bcc.txt", Bcc_matrix, cut_arr)

    all_node = range(1, n + 1)

    G = nx.Graph()
    G.add_edges_from(Raw_edge)
    G.add_nodes_from(all_node)
    pos = nx.spring_layout(G)

    # color the bcc nodes
    for i in xrange(0, len(Bcc_matrix)):
        nx.draw_networkx_nodes(G, pos, nodelist = Bcc_matrix[i],alpha = 0.6, node_color=colors[i])

    # color the cut nodes
    nx.draw_networkx_nodes(G, pos, nodelist = cut_arr, node_color = 'salmon')
    nx.draw_networkx_edges(G, pos, edge_color='black', alpha=0.6, width=1.0)
    nx.draw_networkx_labels(G, pos)
    # print type(node_blue)
    # nx.draw_networkx_edges(G, pos = nx.spring_layout(G), edgelist=[(1,2)], edge_color = 'blue')
    # nx.draw_networkx_nodes(G, pos, nodelist = Bcc_matrix[1], node_color = 'b')
    font = {'color'      : 'k',
            'fontweight' : 'bold',
            'fontsize'   : 14}
    plt.title("The cut and bcc info",font)
    plt.annotate('The cut vertexs',(1,1.15))
    plt.plot([0.95],[1.1666],color = 'salmon',marker = 'o',markersize = 15)
    plt.axis('off')
    plt.cool()
    plt.savefig('Bcc.png', dpi=233)
    plt.show()


if __name__ == "__main__":
    plot()