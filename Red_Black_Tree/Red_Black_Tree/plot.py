#!/urs/bin/python
# -*- coding: UTF-8 -*-

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

def readFile(fileName,words,times):
    file = open(fileName);
    print "Name of file: ", file.name
    scale = ""
    time = ""
    for line in file.readlines():
        index = line.find(' ', 0, len(line));
        scale = line[0:index];
        words.append(int(scale))
        time = line[index + 1:-1]
        times.append(float(time))
    file.close()


def insert_random():
    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/Red_Black_Tree/Red_Black_Tree/RBTree_insert_random.txt",words,times)
    fig = plt.figure(figsize = (10,8))
    plt.subplot(211)
    plt.plot(words, times, color = 'b', label="Insert Time of RBTree in random data")
    plt.xlabel = "Scale(n)"
    plt.ylabel = "Times(s)"
    plt.legend(loc = "upper right", shadow = True)
    plt.grid()
    yMin = min(times)
    yMax = max(times)

    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/Red_Black_Tree/Red_Black_Tree/AVLTree_insert_random.txt",words,times)
    yMin = min(min(times),yMin)
    yMax = max(max(times),yMax)
    plt.subplot(212)
    plt.plot(words,times, color = 'r', label = "Insert Time of Avl in random data")

    plt.xlabel = "Scale(n)"
    plt.ylabel = "Times(s)"
    plt.legend(loc="upper right", shadow = True)
    plt.grid()
    plt.savefig("/Users/luodian/Desktop/DSA/Red_Black_Tree/Red_Black_Tree/insert_random.png")

def insert_random_whole():
    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/Red_Black_Tree/Red_Black_Tree/RBTree_insert_random.txt",words,times)
    fig = plt.figure(figsize = (10,8))
    plt.subplot(111)
    plt.plot(words, times, color = 'b', label="Insert Time of RBTree in random data")
    yMin = min(times)
    yMax = max(times)

    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/Red_Black_Tree/Red_Black_Tree/AVLTree_insert_random.txt",words,times)
    plt.plot(words, times, color='g', label= "Insert Time of Avl in random data")
    yMin = min(min(times),yMin)
    yMax = max(max(times),yMax)

    plt.ylim(yMin , yMax)
    plt.xlabel = "Scale(n)"
    plt.ylabel = "Times(s)"
    plt.legend(loc="upper right", shadow=True)
    plt.grid()
    plt.savefig('/Users/luodian/Desktop/DSA/Red_Black_Tree/Red_Black_Tree/insert_random_whole.png')

def find_random_whole():
    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/Red_Black_Tree/Red_Black_Tree/RBTree_search_random.txt",words,times)
    fig = plt.figure(figsize = (10,8))
    plt.subplot(111)
    plt.plot(words, times, color = 'b', label="Search Time of RBTree in random data")
    yMin = min(times)
    yMax = max(times)

    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/Red_Black_Tree/Red_Black_Tree/AVLTree_search_random.txt",words,times)
    plt.plot(words, times, color='g', label= "Search Time of Avl in random data")
    yMin = min(min(times),yMin)
    yMax = max(max(times),yMax)

    plt.ylim(yMin , yMax)
    plt.xlabel = "Scale(n)"
    plt.ylabel = "Times(s)"
    plt.legend(loc = "upper right", shadow = True)
    plt.grid()
    plt.savefig('/Users/luodian/Desktop/DSA/Red_Black_Tree/Red_Black_Tree/search_random_whole.png')


def insert_sequntial_whole():
    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/Red_Black_Tree/Red_Black_Tree/RBTree_insert_sequntial.txt",words,times)
    fig = plt.figure(figsize = (10,8))
    plt.subplot(111)
    plt.plot(words, times, color = 'b', label="Insert Time of RBTree in sequntial data")
    yMin = min(times)
    yMax = max(times)

    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/Red_Black_Tree/Red_Black_Tree/AVLTree_insert_sequntial.txt",words,times)
    plt.plot(words, times, color='g', label='Insert Time of Avl in sequntial data')
    yMin = min(min(times),yMin)
    yMax = max(max(times),yMax)

    plt.ylim(yMin , yMax)
    plt.xlabel = "Scale(n)"
    plt.ylabel = "Times(s)"
    plt.legend(loc="upper right", shadow=True)
    plt.grid()
    plt.savefig('/Users/luodian/Desktop/DSA/Red_Black_Tree/Red_Black_Tree/insert_sequntial_whole.png')

def find_sequntial_whole():
    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/Red_Black_Tree/Red_Black_Tree/RBTree_find_sequntial.txt",words,times)
    fig = plt.figure(figsize = (10,8))
    plt.subplot(111)
    plt.plot(words, times, color = 'b', label="Search Time of RBTree in sequntial data")
    yMin = min(times)
    yMax = max(times)

    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/Red_Black_Tree/Red_Black_Tree/AVLTree_find_sequntial.txt",words,times)
    plt.plot(words, times, color='g', label='Search Time of Avl in sequntial data')
    yMin = min(min(times),yMin)
    yMax = max(max(times),yMax)

    plt.ylim(yMin , yMax)
    plt.xlabel = "Scale(n)"
    plt.ylabel = "Times(s)"
    plt.legend(loc="upper right", shadow=True)
    plt.grid()
    plt.savefig('/Users/luodian/Desktop/DSA/Red_Black_Tree/Red_Black_Tree/search_sequntial_whole.png')
if __name__ == "__main__":
    insert_random()
    insert_random_whole()
    find_random_whole()
    insert_sequntial_whole()
    find_sequntial_whole();
