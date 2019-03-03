/**
** @brief This is an example to how to use the implemented recursive filters.
**
** @author Kisházi "janohhank" János
**/

// Recursive filters.
#include "../inc/LowPassFilter.hpp"
#include "../inc/HighPassFilter.hpp"

// STD includes.
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
** Generates random linear data translated with random number (from normal distribution).
** Result is the y values from y = i * normalDist()
** @param startValue is the value from start the x values
** @param stepSize is the step value
** @param mean the mean of the normal distribution
** @param stdev the standard deviation of the normal distribution
** @param numSample is the count of the required samples size
**/
template <typename DataType>
vector<DataType> generateLinearRandomData(
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
		results.emplace_back(i * translation);
		currentValue += stepSize;
	}

	return results;
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
vector<DataType> generateSinusoidRandomData(
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
** Example usage information.
**/
void usage(char *argv[]){
	cout << "[" << argv[0] << "]" << " Requires the following arguments:"
	<< " NUM-SAMPLES" << " START-VALUE" << " STEP-SIZE" << " NORMAL-DIST-MEAN" << " NORMAL-DIST-STDEV" << " LOW-PASS-FILTER-FACTOR" << " HIGH-PASS-FILTER-FACTOR" << " MODE" << endl
	<< "	Where: " << endl
	<< "		NUM-SAMPLES ranom generated data sample size." << endl
	<< "		START-VALUE ranom generated data start value." << endl
	<< "		STEP-SIZE ranom generated data step size between values." << endl
	<< "		NORMAL-DIST-MEAN normal distribution mean." << endl
	<< "		NORMAL-DIST-MEAN normal distribution standard deviation." << endl
	<< "		LOW-PASS-FILTER-FACTOR smoothing factor, it can be [0,1]." << endl
	<< "		HIGH-PASS-FILTER-FACTOR smoothing factor, it can be [0,1]." << endl
	<< "		MODE is the random generated data mode, it can be [SINUSOID,LINEAR]." << endl;
}

/**
** Program main entry point.
** In this mini example the program can't be parametrized from console.
**/
int main(int argc, char *argv[]){
	if(argc < 9){
		usage(argv);
		return 1;
	}
	const unsigned int NUM_SAMPLES = stoi(argv[1]);
	const float START_VALUE = stof(argv[2]);
	const float STEP_SIZE = stof(argv[3]);
	const float NORMAL_DIST_MEAN = stof(argv[4]);
	const float NORMAL_DIST_STDEV = stof(argv[5]);
	const float LOW_PASS_FILTER_FACTOR = stof(argv[6]);
	const float HIGH_PASS_FILTER_FACTOR = stof(argv[7]);
	const string MODE = argv[8];

	vector<float> (*dataGenerator)(const float&, const float&, const float&, const float&, const unsigned int&);
	if(MODE == "SINUSOID"){
		dataGenerator = &generateSinusoidRandomData;
	}else if(MODE == "LINEAR"){
		dataGenerator = &generateLinearRandomData;
	}else{
		throw logic_error("Unrecognized mode type: " + MODE);
	}

	print(__FILE__,"INFO","Generating data.");
	const auto& generatedRandomData =
		dataGenerator(
			START_VALUE,
			STEP_SIZE,
			NORMAL_DIST_MEAN,
			NORMAL_DIST_STDEV,
			NUM_SAMPLES
		)
	;

	unique_ptr<LowPassFilter<float>> lowPassFilter = make_unique<LowPassFilter<float>>(LOW_PASS_FILTER_FACTOR);
	unique_ptr<HighPassFilter<float>> highPassFilter = make_unique<HighPassFilter<float>>(HIGH_PASS_FILTER_FACTOR);

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