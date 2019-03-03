#!/usr/bin/python
# This script can read the RecursiveFilters C++ example result files
# and plots the data points.
#
# Plots the original data and high/low pass filtered datapoints with interpolated curves.
#
# @author Kishazi "janohhank" Janos

import os
import numpy
import argparse
import matplotlib.pyplot
import scipy.interpolate

parser = argparse.ArgumentParser(description="Filtered data points plotter.")
parser.add_argument("--originalData",required=True,type=str,help="Path of the original data text file.")
parser.add_argument("--lowPassFilteredData",required=True,type=str,help="Path of the low pass filtered data text file.")
parser.add_argument("--highPassFilteredData",required=True,type=str,help="Path of the high pass filtered data text file.")
parser.add_argument("--numSamples",required=True,type=float,help="Sample size of the generated data.")
parser.add_argument("--startValue",required=True,type=float,help="Data generation start value.")
parser.add_argument("--stepSize",required=True,type=float,help="Data generation step size.")

args = parser.parse_args()
originalDataFilePath = args.originalData
lowPassFilteredDataFilePath = args.lowPassFilteredData
highPassFilteredDataFilePath = args.highPassFilteredData
startValue = args.startValue
stepSize = args.stepSize
numSamples = args.numSamples
endValue = startValue + numSamples * stepSize

if os.path.isfile(originalDataFilePath) is False:
	raise Exception("The input path does not denote a file: " + originalDataFilePath)
if os.path.isfile(lowPassFilteredDataFilePath) is False:
	raise Exception("The input path does not denote a file: " + lowPassFilteredDataFilePath)
if os.path.isfile(highPassFilteredDataFilePath) is False:
	raise Exception("The input path does not denote a file: " + highPassFilteredDataFilePath)

print("[" + __file__ + "]" + "[INFO]" + " Parsing result data files.")

originalData = []
with open(originalDataFilePath, "r") as originalDataFile:
	for line in originalDataFile:
		for value in line.split(","):
			if not value:
				continue
			originalData.append(value)

lowPassFilteredData = []
with open(lowPassFilteredDataFilePath, "r") as lowPassFilteredFile:
	for line in lowPassFilteredFile:
		for value in line.split(","):
			if not value:
				continue
			lowPassFilteredData.append(value)

highPassFilteredData = []
with open(highPassFilteredDataFilePath, "r") as highPassFilteredFile:
	for line in highPassFilteredFile:
		for value in line.split(","):
			if not value:
				continue
			highPassFilteredData.append(value)

if(len(originalData) != numSamples) or (len(lowPassFilteredData) != numSamples) or (len(highPassFilteredData) != numSamples):
	raise Exception("The results text files doesn\'t contains enough data.")

print("[" + __file__ + "]" + "[INFO]" + " Creating plot.")

xValues = numpy.arange(startValue, endValue, stepSize)

dataInterpolationFunction = scipy.interpolate.interp1d(xValues, originalData, kind="quadratic")
smoothOriginalData = dataInterpolationFunction(xValues)

dataInterpolationFunction = scipy.interpolate.interp1d(xValues, lowPassFilteredData, kind="quadratic")
smoothLowPassFilteredData = dataInterpolationFunction(xValues)

dataInterpolationFunction = scipy.interpolate.interp1d(xValues, highPassFilteredData, kind="quadratic")
smoothHighPassFilteredData = dataInterpolationFunction(xValues)

matplotlib.pyplot.plot(xValues, smoothOriginalData, label="OriginalData")
matplotlib.pyplot.plot(xValues, smoothLowPassFilteredData, label="LowPassFilteredData")
matplotlib.pyplot.plot(xValues, smoothHighPassFilteredData, label="HighPassFilteredData")
matplotlib.pyplot.xlabel("Samples with " + str(stepSize) + " stepsize.")
matplotlib.pyplot.ylabel("Random generated data points.")
matplotlib.pyplot.title("Recursive filters.")
matplotlib.pyplot.legend()
matplotlib.pyplot.show()