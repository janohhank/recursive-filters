#pragma once

namespace filter{

/**
** @brief High-pass filter implementation which works on digital samples.
**
** @param ValueType the type of the alpha factor and the data.
** @author Kisházi "janohhank" János
**/
template <typename ValueType>
class HighPassFilter final{
	private:
		/*
		* The filter alpha factor.
		* How percentage of the input and output data will used.
		*/
		const ValueType alphaFactor;

		/*
		* The previous result/output value of the filter.
		*/
		ValueType previousOutputValue;

		/*
		* The previous input value.
		*/
		ValueType previousInputValue;

		/*
		* In the beginning initialize the filter with the first input value.
		*/
		bool initialized;
	public:
		/**
		** Constructs a new instance.
		**/
		HighPassFilter(
			const ValueType& alphaFactor
		) : alphaFactor(alphaFactor), initialized(false){
			//Intentionally NOOP.
		}

		/**
		** Simple destructor.
		**/
		~HighPassFilter(){
			//Intentionally NOOP.
		}

		/**
		** Filters the input data.
		**
		** y(i) = alpha * y(i - 1) + alpha * (x(i) - x(i - 1))
		**
		** where,
		** y(i) = current output value
		** x(i) = current input value
		** y(i - 1) = previous output value
		** x(i - 1) = previous input value
		** alpha = the alpha factor
		**
		** @param currentInputValue, the new value which want to be filtered.
		** @return the filtered data.
		**/
		ValueType process(const ValueType& currentInputValue){
			if(!initialized){
				previousInputValue = currentInputValue;
				previousOutputValue = currentInputValue;
				initialized = true;
				return currentInputValue;
			}

			const ValueType& result =
				alphaFactor * previousOutputValue + alphaFactor * (currentInputValue - previousInputValue)
			;

			previousOutputValue = result;
			previousInputValue = currentInputValue;

			return result;
		}
};

}