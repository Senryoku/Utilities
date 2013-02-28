#pragma once

template<typename T>
class EvolvingValue {
	public:
	EvolvingValue(T value = T(), bool automaticStep = false) :
		_value(value),
		_automaticStep(automaticStep)
	{
	}
	/**
	 * Define the behavior of special getters (like implicit convertion),
	 * if set to true, a step() should be performed for each get
	**/
	inline void setAutomaticStep(bool B = true) {
		_automaticStep = B;
	}
	
	inline bool isAutomatic() const { return _automaticStep; }
	
	/**
	 * Getter without any side-effect (Guaranteed !)
	**/
	inline const T& getValue() const { return _value; }
	
	/** 
	 * Define implicit convertion to T
	**/
	operator T() {
		if(isAutomatic())
			step();
		return _value;
	}
	
	/**
	 * The actual magic
	 * Performs one step and return the current value
	**/
	virtual T step() =0;
	
	protected:
	bool	_automaticStep;
	T		_value;
};
