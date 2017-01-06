#include <thread>

/**
 * Barrier
 * Simple thread synchronization tool : threads wait until
 * 'count' threads have reached the barrier.
**/
class Barrier
{
public:
	explicit Barrier(std::size_t count) : 
		_init_count{count}
		_count{count}
	{
	}

	void wait()
	{
		std::unique_lock<std::mutex> lock{_mutex};
		if (--_count == 0) // The last thread has caught up
		{
			_cv.notify_all(); // Awake all waiting threads
			reset();
		} else {
			_cv.wait(lock); // Wait for the others
		}
	}

	inline void reset()
	{
		_count = _init_count;
	}

private:
	std::mutex				_mutex;
	std::condition_variable	_cv;
	const std::size_t		_init_count;	///< Number of threads to synchronize
	std::size_t				_count;			///< How many threads are we still waiting for
};
