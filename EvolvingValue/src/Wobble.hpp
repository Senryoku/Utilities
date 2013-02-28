#pragma once

#include "EvolvingValue.hpp"

class Wobble : public EvolvingValue<float> {
	public:
	/**
	 * Starting Value, Target Value, Force, Friction, Initial Speed (Default : 0.f)
	**/
	Wobble(float value, float target, float force, float friction, float initialSpeed = 0.f) :
		EvolvingValue<float>(value, true),
		_initialValue(value),
		_initialSpeed(initialSpeed),
		_target(target),
		_force(force),
		_friction(friction),
		_speed(initialSpeed)
	{
	}
	
	float reset() {
		_value = _initialValue;
		_speed = _initialSpeed;
	}
	
	float step() {
		_speed = (_speed + ((_target - _value)/2.f) * _force) * (1.f - _friction);
		_value += _speed;
	}
	
	private:
	const float	_initialValue; // Allow the reset() method
	const float	_initialSpeed;
	float		_target;
	float		_force;
	float		_friction;
	float		_speed;
};
