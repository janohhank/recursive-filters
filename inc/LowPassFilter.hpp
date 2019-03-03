#pragma once

namespace filter{

/**
** @brief Low-pass filter implementation which works on digital samples.
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

		/*
		* In the beginning initialize the filter with the first input value.
		*/
		bool initialized;
	public:
		/**
		** Constructs a new instance.
		**/
		LowPassFilter(
			const ValueType& alphaFactor
		) : alphaFactor(alphaFactor), initialized(false){
			//Intentionally NOOP.
		}

		/**
		** Simple destructor.
		**/
		~LowPassFilter(){
			//Intentionally NOOP.
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
			if(!initialized){
				previousOutputValue = currentInputValue;
				initialized = true;
				return currentInputValue;
			}

			const ValueType& result =
				currentInputValue * alphaFactor + (1.0 - alphaFactor) * previousOutputValue;

			previousOutputValue = result;

			return result;
		}
};

}