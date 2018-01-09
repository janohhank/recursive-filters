#pragma once

namespace filter{

/**
** @brief Simple high-pass filter implementation.
**
** @param ValueType the type of the alpha factor and the data.
** @author Kisházi "janohhank" János
**/
template <typename ValueType>
class HighPassFilter{
	private:
		/*
		* The filter alpha factor.
		* How percentage of the input and output data will used.
		*/
		ValueType alphaFactor;

		/*
		* The previous result/output value of the filter.
		*/
		ValueType previousOutputValue;

		/*
		* The previous input value.
		*/
		ValueType previousInputValue;
	public:
		/**
		** Constructs a new instance.
		**/
		HighPassFilter(const ValueType alphaFactor){
			this->alphaFactor = alphaFactor;
			this->previousOutputValue = 0.0;
			this->previousInputValue = 0.0;
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
		ValueType process(const ValueType currentInputValue){
			const ValueType result =
				alphaFactor * previousOutputValue + alphaFactor * (currentInputValue - previousInputValue)
			;

			previousOutputValue = result;
			previousInputValue = currentInputValue;

			return result;
		}
};

}
