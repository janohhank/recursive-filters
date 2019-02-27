#!/usr/bin/python
#
#
#
#
# @author Kishazi "janohhank" Janos

import numpy
import argparse
import matplotlib.pyplot
import scipy.interpolate

parser = argparse.ArgumentParser(description='')
parser.add_argument('--originalData',required=True,type=str,help='')
parser.add_argument('--lowPassFilteredData',required=True,type=str,help='')
parser.add_argument('--highPassFilteredData',required=True,type=str,help='')
parser.add_argument('--stepSize',required=False,type=float,help='')

args = parser.parse_args()
originalDataFilePath = args.originalData
lowPassFilteredDataFilePath = args.lowPassFilteredData
highPassFilteredDataFilePath = args.highPassFilteredData
stepSize = args.stepSize

numSamples = 250
startValue = 0.1
stepSize = 0.1
endValue = startValue + numSamples * stepSize

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

xValues = numpy.arange(startValue, endValue, stepSize)

dataInterpolationFunction = scipy.interpolate.interp1d(xValues, originalData, kind='quadratic')
smoothOriginalData = dataInterpolationFunction(xValues)

dataInterpolationFunction = scipy.interpolate.interp1d(xValues, lowPassFilteredData, kind='quadratic')
smoothLowPassFilteredData = dataInterpolationFunction(xValues)

dataInterpolationFunction = scipy.interpolate.interp1d(xValues, highPassFilteredData, kind='quadratic')
smoothHighPassFilteredData = dataInterpolationFunction(xValues)

matplotlib.pyplot.plot(xValues, smoothOriginalData, label='OriginalData')
matplotlib.pyplot.plot(xValues, smoothLowPassFilteredData, label='LowPassFilteredData')
matplotlib.pyplot.plot(xValues, smoothHighPassFilteredData, label='HighPassFilteredData')
matplotlib.pyplot.xlabel("Samples")
matplotlib.pyplot.ylabel("Random sinusoid data")
matplotlib.pyplot.legend()
matplotlib.pyplot.show()