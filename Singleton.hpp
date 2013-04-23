#pragma once

/** 
 * @brief Abstract class for singleton pattern
**/
template<typename C>
class Singleton {
	public:
	/**
	 * I think this could be could be set as private without
	 * any harm...
	 * @return The instance of C
	**/
	inline static C& getInstance() {
		// Being declared as static, I will be consistant over the getInstance() calls
		// and destroyed at the end of the program.
		static C I;
		return I;
	}
	
	protected:
	// Prevents construction...
	Singleton() {}
	// ...as well as copy construction...
	Singleton(const C& Copy) {}
	Singleton& operator=(const C& Copy) {}
	// ...or premature destruction.
	virtual ~Singleton() {}
};