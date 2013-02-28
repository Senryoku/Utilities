#pragma once

#include "EvolvingValue.hpp"
#include <climits>

/**
 * Guarantees _min <= _value < _max
 * @todo More tests with exotic values...
**/
class Counter : public EvolvingValue<int> {
	public:
	Counter(int value = 0, int min = 0, int max = INT_MAX, unsigned int step = 1) :
		EvolvingValue<int>(value, false),
		_min(min),
		_max(max),
		_step(step)
	{
		if(_min > _max) {
			int tmp = _min;
			_min = _max;
			_max = tmp;
		}
		
		if(_value < _min || _value > _max)
			_value = _min;
	}
	
	int step() {
		incr();
		return _value;
	}
	
	int incr() {
		_value += _step;
		if(_value >= _max) {
			int r = _value / _max;
			_value = ((_value - _min) % (_max - _min)) + _min;
			return r;
		} else return 0;
	}
	
	int decr() {
		_value -= _step;
		if(_value < _min) {
			int diff = _value - _min;
			_value = _max - ((-diff) % (_max - _min));
			return (diff/_min) + 1;
		} else return 0;
	}
	
	private:
	unsigned int	_step;
	int				_min;
	int				_max;
};

