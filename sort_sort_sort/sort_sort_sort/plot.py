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


def suqare_alogrithms_random():
    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/RandomData/n^2_bubble_sort.txt",words,times)
    fig = plt.figure(figsize = (10,8))
    plt.subplot(111)
    plt.plot(words, times, color = 'b', label="Time of bubble sort algorithm in random data")
    yMin = min(times)
    yMax = max(times)

    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/RandomData/n^2_insertion_sort.txt",words,times)
    yMin = min(min(times),yMin)
    yMax = max(max(times),yMax)
    plt.plot(words,times, color = 'r', label = "Time of insertion sort algorithm in random data")

    # words = []
    # times = []
    # readFile("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/RandomData/sub_square_shell_sort.txt",words,times)
    # yMin = min(min(times),yMin)
    # yMax = max(max(times),yMax)
    # plt.plot(words,times, color = 'g', label = "Time of shell sort algorithm in random data")

    # plt.xlabel = "Scale(n)"
    # plt.ylabel = "Times(s)"
    # plt.legend(loc="upper right", shadow = True)
    # plt.grid()
    # plt.savefig("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/square_random_data.png")

def sup_linear_alogrithms_random():
    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/RandomData/sup_linear_quick_sort_lefist.txt",words,times)
    fig = plt.figure(figsize = (10,8))
    plt.subplot(111)
    plt.plot(words, times, color = 'b', label="Time of quick(leftist) sort algorithm in random data")
    yMin = min(times)
    yMax = max(times)

    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/RandomData/sup_linear_quick_sort_random.txt",words,times)
    yMin = min(min(times),yMin)
    yMax = max(max(times),yMax)
    plt.plot(words,times, color = 'r', label = "Time of quick(random) sort algorithm in random data")

    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/RandomData/sup_linear_heap_sort.txt",words,times)
    yMin = min(min(times),yMin)
    yMax = max(max(times),yMax)
    plt.plot(words,times, color = 'g', label = "Time of heap sort algorithm in random data")

    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/RandomData/sup_linear_merge_sort.txt",words,times)
    yMin = min(min(times),yMin)
    yMax = max(max(times),yMax)
    plt.plot(words,times, color = 'black', label = "Time of merge sort algorithm in random data")

    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/RandomData/linear_bucket_sort.txt",words,times)
    yMin = min(min(times),yMin)
    yMax = max(max(times),yMax)
    plt.plot(words,times, color = 'brown', label = "Time of bucket sort algorithm in random data")

    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/RandomData/linear_bucket_optimal_sort.txt",words,times)
    yMin = min(min(times),yMin)
    yMax = max(max(times),yMax)
    plt.plot(words,times, color = 'orange', label = "Time of bucket optimal(space) sort algorithm in random data")

    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/RandomData/linear_radix_sort.txt",words,times)
    yMin = min(min(times),yMin)
    yMax = max(max(times),yMax)
    plt.plot(words,times, color = 'pink', label = "Time of radix sort algorithm in random data")

    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/RandomData/linear_stl_sort.txt",words,times)
    yMin = min(min(times),yMin)
    yMax = max(max(times),yMax)
    plt.plot(words,times, color = 'yellow', label = "Time of stl sort algorithm in random data")

    plt.xlabel = "Scale(n)"
    plt.ylabel = "Times(s)"
    plt.legend(loc="upper right", shadow = True)
    plt.grid()
    plt.savefig("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/suplinear_random_data.png")

def quick_sort_function_random():
    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/RandomData/sup_linear_quick_sort_lefist.txt",words,times)
    fig = plt.figure(figsize = (10,8))
    plt.subplot(111)
    plt.plot(words, times, color = 'b', label="Normal Quicksort")
    yMin = min(times)
    yMax = max(times)

    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/RandomData/sup_linear_quick_sort_random.txt",words,times)
    yMin = min(min(times),yMin)
    yMax = max(max(times),yMax)
    plt.title("Comparison between Normal Quicksort and Optimal Quicksort");
    plt.plot(words,times, color = 'r', label = "Optimal Quicksort")


    plt.xlabel = "Scale(n)"
    plt.ylabel = "Times(s)"
    plt.legend(loc="upper right", shadow = True)
    plt.grid()
    plt.savefig("/Users/luodian/Desktop/quicksort_random_data.png")


def quick_sort_function_seq():
    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/SequntialData/sup_linear_quick_sort_lefist.txt",words,times)
    fig = plt.figure(figsize = (10,8))
    plt.subplot(111)
    plt.plot(words, times, color = 'b', label="Normal Quicksort")
    yMin = min(times)
    yMax = max(times)

    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/SequntialData/sup_linear_quick_sort_random.txt",words,times)
    yMin = min(min(times),yMin)
    yMax = max(max(times),yMax)
    plt.plot(words,times, color = 'r', label = "Optimal Normal Quicksort")

    plt.xlabel = "Scale(n)"
    plt.ylabel = "Times(s)"
    plt.legend(loc="upper right", shadow = True)
    plt.grid()
    plt.title("Comparison between Normal Quicksort and Optimal Quicksort");
    plt.savefig("/Users/luodian/Desktop/quicksort_sequntial_data.png")


def quick_sort_function_Rseq():
    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/ReverseSequntialData/sup_linear_quick_sort_lefist.txt",words,times)
    fig = plt.figure(figsize = (10,8))
    plt.subplot(111)
    plt.plot(words, times, color = 'b', label="Time of quick(leftist) sort algorithm in reverse sequntial data")
    yMin = min(times)
    yMax = max(times)

    words = []
    times = []
    readFile("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/ReverseSequntialData/sup_linear_quick_sort_random.txt",words,times)
    yMin = min(min(times),yMin)
    yMax = max(max(times),yMax)
    plt.plot(words,times, color = 'r', label = "Time of quick(random) sort algorithm in reverse sequntial data")

    plt.xlabel = "Scale(n)"
    plt.ylabel = "Times(s)"
    plt.legend(loc="upper right", shadow = True)
    plt.grid()
    plt.savefig("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/quicksort_Reverse_sequntial_data.png")


if __name__ == "__main__":
    # suqare_alogrithms_random();
    # sup_linear_alogrithms_random();
    # quick_sort_function_random();
    quick_sort_function_seq();
    # quick_sort_function_Rseq();
