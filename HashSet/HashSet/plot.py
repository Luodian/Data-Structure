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
    readFile("/Users/luodian/Desktop/DSA/HashSet/HashSet/Open_insert.txt",words,times)
    fig = plt.figure(figsize = (10,8))
    plt.subplot(211)
    plt.plot(words, times, color = 'b', label="Insert Time of Open Hash in random data")
    plt.xlabel = "Scale(n)"
    plt.ylabel = "Times(s)"
    plt.legend(loc = "upper right", shadow = True)
    plt.grid()
    yMin = min(times)
    yMax = max(times)

    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/HashSet/HashSet/Probe_insert.txt",words,times)
    yMin = min(min(times),yMin)
    yMax = max(max(times),yMax)
    plt.subplot(212)
    plt.plot(words,times, color = 'r', label = "Insert Time of Probe Hash in random data")

    plt.xlabel = "Scale(n)"
    plt.ylabel = "Times(s)"
    plt.legend(loc="upper right", shadow = True)
    plt.grid()
    plt.savefig("/Users/luodian/Desktop/DSA/HashSet/HashSet/insert_comparasion.png")

def insert_random_whole():
    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/HashSet/HashSet/Open_insert.txt",words,times)
    fig = plt.figure(figsize = (10,8))
    plt.subplot(111)
    plt.plot(words, times, color = 'b', label="Insert Time of Open Hash in random data")
    yMin = min(times)
    yMax = max(times)

    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/HashSet/HashSet/Probe_insert.txt",words,times)
    plt.plot(words, times, color='g', label= "Insert Time of Probe Hash in random data")
    yMin = min(min(times),yMin)
    yMax = max(max(times),yMax)

    plt.ylim(yMin , yMax)
    plt.xlabel = "Scale(n)"
    plt.ylabel = "Times(s)"
    plt.legend(loc="upper right", shadow=True)
    plt.grid()
    plt.savefig('/Users/luodian/Desktop/DSA/HashSet/HashSet/insert_comparasion_whole.png')

def find_random_whole():
    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/HashSet/HashSet/Open_find.txt",words,times)
    fig = plt.figure(figsize = (10,8))
    plt.subplot(111)
    plt.plot(words, times, color = 'b', label="Search Time of Open Hash in random data")
    yMin = min(times)
    yMax = max(times)

    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/HashSet/HashSet/Probe_find.txt",words,times)
    plt.plot(words, times, color='g', label= "Search Time of Probe Hash in random data")
    yMin = min(min(times),yMin)
    yMax = max(max(times),yMax)

    plt.ylim(yMin , yMax)
    plt.xlabel = "Scale(n)"
    plt.ylabel = "Times(s)"
    plt.legend(loc = "upper right", shadow = True)
    plt.grid()
    plt.savefig('/Users/luodian/Desktop/DSA/HashSet/HashSet/find_comparasion.png')


def crash_open_whole():
    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/HashSet/HashSet/BKDR_open_crash.txt",words,times)
    fig = plt.figure(figsize = (10,8))
    plt.subplot(111)
    plt.plot(words, times, color = 'b', label="Crash count of Open Hash in BKDR function")
    yMin = min(times)
    yMax = max(times)

    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/HashSet/HashSet/FNV_open_crash.txt",words,times)
    plt.plot(words, times, color='g', label='Crash count of Open Hash in FNV function')
    yMin = min(min(times),yMin)
    yMax = max(max(times),yMax)

    plt.ylim(yMin , yMax)
    plt.xlabel = "Scale(n)"
    plt.ylabel = "Count(t)"
    plt.legend(loc="upper right", shadow=True)
    plt.grid()
    plt.savefig('/Users/luodian/Desktop/DSA/HashSet/HashSet/Crash_count_open.png')

def crash_probe_whole():
    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/HashSet/HashSet/BKDR_probe_crash.txt",words,times)
    fig = plt.figure(figsize = (10,8))
    plt.subplot(111)
    plt.plot(words, times, color = 'b', label="Crash count of Probe Hash in BKDR function")
    yMin = min(times)
    yMax = max(times)

    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/HashSet/HashSet/FNV_probe_crash.txt",words,times)
    plt.plot(words, times, color='g', label='Crash count of Probe Hash in FNV function')
    yMin = min(min(times),yMin)
    yMax = max(max(times),yMax)

    plt.ylim(yMin , yMax)
    plt.xlabel = "Scale(n)"
    plt.ylabel = "Count(t)"
    plt.legend(loc="upper right", shadow=True)
    plt.grid()
    plt.savefig('/Users/luodian/Desktop/DSA/HashSet/HashSet/Crash_count_probe.png')

if __name__ == "__main__":
    insert_random()
    insert_random_whole()
    find_random_whole()
    crash_open_whole()
    crash_probe_whole()
