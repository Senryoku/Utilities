#pragma once

#ifdef TARGET_OS_MAC
	#error "unsupported"
#elif defined __linux__
	#include <pthread.h>
#elif defined _WIN32 || defined _WIN64
	#include <windows.h>
#else
	#error "unknown platform"
#endif

class Thread {
	public:
	typedef void (*entry_point)(void* arg);
	
	private:
};
