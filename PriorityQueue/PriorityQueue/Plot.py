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


def plotGraph():
    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/PriorityQueue/PriorityQueue/Heap_insert.txt",words,times)
    fig = plt.figure(figsize = (10,8))
    plt.subplot(211)
    plt.plot(words, times, color = 'b', label="Time of Heap")
    plt.xlabel = "Scale(n)"
    plt.ylabel = "Times(s)"
    plt.legend(loc="upper right", shadow=True)
    plt.grid()

    yMin = min(times)
    yMax = max(times)
    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/PriorityQueue/PriorityQueue/LeftHeap_insert.txt",words,times)
    yMin = min(min(times),yMin)
    yMax = max(max(times),yMax)
    plt.subplot(212)
    plt.plot(words, times, color='g', label='Time of LeftistHeap')
    plt.xlabel = "Scale(n)"
    plt.ylabel = "Times(s)"
    plt.legend(loc="upper right", shadow=True)
    plt.grid()

    plt.xlabel = "Scale(n)"
    plt.ylabel = "Times(s)"
    plt.legend(loc="upper right", shadow=True)
    plt.grid()
    plt.savefig('/Users/luodian/Desktop/DSA/PriorityQueue/PriorityQueue/InsertTime.png')

def plotWhole():
    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/PriorityQueue/PriorityQueue/Heap_insert.txt",words,times)
    fig = plt.figure(figsize = (10,8))
    plt.subplot(111)
    plt.plot(words, times, color = 'b', label="Time of Heap")
    yMin = min(times)
    yMax = max(times)

    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/PriorityQueue/PriorityQueue/LeftHeap_insert.txt",words,times)
    plt.plot(words, times, color='g', label='Time of LeftistHeap')
    yMin = min(min(times),yMin)
    yMax = max(max(times),yMax)

    plt.ylim(yMin , yMax)
    plt.xlabel = "Scale(n)"
    plt.ylabel = "Times(s)"
    plt.legend(loc="upper right", shadow=True)
    plt.grid()
    plt.savefig('/Users/luodian/Desktop/DSA/PriorityQueue/PriorityQueue/InsertTimeWhole.png')

if __name__ == "__main__":
    plotGraph()
    plotWhole()
