#!/urs/bin/python
# -*- coding: UTF-8 -*-
import os
import matplotlib.pyplot as plt

words = []
times = []

def readFile(fileName):
	file = open(fileName);
	print "Name of file: ",file.name
	scale = ""
	time = ""
	for line in file.readlines():
		index = line.find(' ',0,len(line));
		scale = line[0:index];
		words.append(int(scale))
		time = line[index + 1:-1]
		times.append(float(time))
	file.close()

def plotGraph():
	words = []
	times = []
	readFile("SkipList.txt")
	fig = plt.figure(1)
	plt.subplot(111)
	plt.plot(words,times,color = 'b',label = "Time of SkipList")
	words = []
	times = []
	readFile("List.txt")
	plt.plot(words,times,color = 'g',label = 'Time of List')
	plt.xlabel = "Scale(n)"
	plt.ylabel = "Times(s)"
	plt.legend(loc = "upper right",shadow = True)
	plt.grid()
	plt.show()

if __name__ == "__main__":
	plotGraph()




		

