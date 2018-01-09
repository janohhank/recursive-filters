/**
** @brief This simple example use the already implemented recursive filters.
**
** @author Kisházi "janohhank" János
**/

//Recursive filters.
#include "../inc/LowPassFilter.hpp"
#include "../inc/HighPassFilter.hpp"

//STD includes.
#include <map>
#include <random>
#include <iostream>
#include <iomanip>

using namespace filter;

std::vector<double> generateData(){
	std::random_device random_device{};
	std::mt19937 generator{random_device()};

	const double mean = 5.0;
	const double stddev = 5.0;
	std::normal_distribution<double> normalDistribution{mean, stddev};

	std::vector<double> data;
	for(unsigned int n = 0; n < 200; ++n){
		data.emplace_back(normalDistribution(generator));
	}

	return data;
}

int main(){
	std::unique_ptr<LowPassFilter<double>> lowPassFilter = std::make_unique<LowPassFilter<double>>(0.2);
	std::unique_ptr<HighPassFilter<double>> highPassFilter = std::make_unique<HighPassFilter<double>>(0.6);

	const auto data = generateData();

	std::map<int, int> originalDataHistogram;
	for(const auto& element : data){
		++originalDataHistogram[std::round(element)];
	}

	std::map<int, int> lowPassFilteredDataHistogram;
	for(auto iterator = originalDataHistogram.cbegin(); iterator != originalDataHistogram.cend(); ++iterator){
		lowPassFilteredDataHistogram.emplace(
			iterator->first,
			std::round(
				lowPassFilter->process(static_cast<double>(iterator->second))
			)
		);
	}

	std::map<int, int> highPassFilteredDataHistogram;
	for(auto iterator = originalDataHistogram.cbegin(); iterator != originalDataHistogram.cend(); ++iterator){
		highPassFilteredDataHistogram.emplace(
			iterator->first,
			std::round(
				lowPassFilter->process(static_cast<double>(iterator->second))
			)
		);
	}

	std::cout << "-------------------------------------------------------------------------" << std::endl;
	for(const auto& element : originalDataHistogram){
		std::cout << std::setw(2) << element.first << ' ' << std::string(element.second, '*') << std::endl;
	}

	std::cout << "-------------------------------------------------------------------------" << std::endl;
	for(const auto& element : lowPassFilteredDataHistogram){
		std::cout << std::setw(2) << element.first << ' ' << std::string(element.second, '*') << std::endl;
	}

	std::cout << "-------------------------------------------------------------------------" << std::endl;
	for(const auto& element : highPassFilteredDataHistogram){
		std::cout << std::setw(2) << element.first << ' ' << std::string(element.second, '*') << std::endl;
	}

	return 0;
}
