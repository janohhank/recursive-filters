/**
** @brief This simple example use the implemented recursive filters.
**
** @author Kisházi "janohhank" János
**/

//Recursive filters.
#include "../inc/LowPassFilter.hpp"
#include "../inc/HighPassFilter.hpp"

//STD includes.
#include <map>
#include <memory>
#include <random>
#include <fstream>
#include <iostream>

using namespace std;
using namespace filter;

/**
** Standard output log helper function.
** @param file is the source file path, usually the __FILE__
** @param type is the type of the log message, for example INFO or ERROR
** @param message the log message in a string
**/
void print(
	const string& file,
	const string& type,
	const string& message
){
	cout << "[" << file << "]" << "[" << type << "]" << " " << message << endl;
}

/**
** Generates random sinusoid data translated with random number (from normal distribution).
** Result is the y values from y = sin(x) * normalDist()
** @param startValue is the value from start the x values
** @param stepSize is the step value
** @param mean the mean of the normal distribution
** @param stdev the standard deviation of the normal distribution
** @param numSample is the count of the required samples size
**/
template <typename DataType>
vector<DataType> generateRandomData(
	const DataType& startValue,
	const DataType& stepSize,
	const DataType& mean,
	const DataType& stdev,
	const unsigned int& numSamples
){
	random_device rd;
	mt19937 random(rd());
	normal_distribution<DataType> normalDistribution(mean, stdev);

	DataType currentValue = startValue;
	vector<DataType> results;
	for(unsigned int i = 0; i < numSamples; ++i){
		const auto& translation = normalDistribution(random);
		results.emplace_back(sin(currentValue) * translation);
		currentValue += stepSize;
	}

	return results;
}

/**
** Program main entry point.
** In this mini example the program can't be parametrized from console.
**/
int main(){
	const unsigned int NUM_SAMPLES = 250;

	print(__FILE__,"INFO","Generating data.");
	const auto& generatedRandomData =
		generateRandomData<float>(
			0.1f,
			0.1f,
			5.0f,
			3.0f,
			NUM_SAMPLES
		)
	;

	unique_ptr<LowPassFilter<double>> lowPassFilter = make_unique<LowPassFilter<double>>(0.2);
	unique_ptr<HighPassFilter<double>> highPassFilter = make_unique<HighPassFilter<double>>(0.8);

	print(__FILE__,"INFO","Low pass filtering.");
	vector<float> lowPassFilteredData;
	for(const auto& data : generatedRandomData){
		lowPassFilteredData.emplace_back(lowPassFilter->process(data));
	}

	print(__FILE__,"INFO","High pass filtering.");
	vector<float> highPassFilteredData;
	for(const auto& data : generatedRandomData){
		highPassFilteredData.emplace_back(highPassFilter->process(data));
	}

	print(__FILE__,"INFO","Saving results.");
	ofstream originalDataFile("originalData.txt");
	ofstream lowPassFilteredDataFile("lowPassFilteredData.txt");
	ofstream highPassFilteredDataFile("highPassFilteredData.txt");
	for(unsigned int i = 0; i < NUM_SAMPLES; ++i){
		originalDataFile << generatedRandomData[i] << ",";
		lowPassFilteredDataFile << lowPassFilteredData[i] << ",";
		highPassFilteredDataFile << highPassFilteredData[i] << ",";
	}

	originalDataFile.close();
	lowPassFilteredDataFile.close();
	highPassFilteredDataFile.close();

	print(__FILE__,"INFO","Results are saved: originalData.txt | lowPassFilteredData.txt | highPassFilteredData.txt");

	return 0;
}