#pragma once

namespace filter{

/**
** @brief Simple low-pass filter implementation.
**
** @param ValueType the type of the alpha factor and the data.
** @author Kisházi "janohhank" János
**/
template <typename ValueType>
class LowPassFilter final{
	private:
		/*
		* The filter alpha factor.
		* How percentage of the input and output data will used.
		*/
		const ValueType alphaFactor;

		/*
		* The previous result value of the filter.
		*/
		ValueType previousOutputValue;
	public:
		/**
		** Constructs a new instance.
		**/
		LowPassFilter(
			const ValueType& alphaFactor
		) : alphaFactor(alphaFactor){
			//Intentionally NOOP.
		}

		/**
		** Simple destructor.
		**/
		~LowPassFilter(){
			//Intentionally NOOP.
		}

		/**
		** Initialize the filter with the first input value.
		** @param firstInputValue the first measured input value.
		**/
		void initializeFilter(
			const ValueType& firstInputValue
		){
			previousOutputValue = firstInputValue;
		}

		/**
		** Filters the input data.
		**
		** y(i) = x(i) * alpha + (1 - alpha) * y(i - 1)
		**
		** where,
		** y(i) = current output value
		** x(i) = current input value
		** y(i - 1) = previous output value
		** alpha = the alpha factor
		**
		** @param currentInputValue, the new value which want to be filtered.
		** @return the filtered data.
		**/
		ValueType process(const ValueType& currentInputValue){
			const ValueType& result =
				currentInputValue * alphaFactor + (1.0 - alphaFactor) * previousOutputValue;

			previousOutputValue = result;

			return result;
		}
};

}