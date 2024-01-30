#pragma once

#include <functional>

class Timer
{
private:
	float m_accumulated_time_in_milliseconds;
	float m_timeout_in_milliseconds;
	bool m_looping;
	bool m_is_stopped;
	std::function<void()> m_timeout_function;

public:
	static enum TimeUnit { MILLISECONDS, SECONDS};

public:
	Timer(float timeout,
		  bool looping = false, 
		  std::function<void()> timeout_function = nullptr,
		  TimeUnit unit = TimeUnit::SECONDS);
	virtual ~Timer();
	void Start();
	void Update(float dt_in_milliseconds, TimeUnit unit = TimeUnit::SECONDS);
	void Stop();
	void Reset(float new_timeout = 0.0f, 
			   bool looping = false,
			   std::function<void()> timeout_function = nullptr,
			   TimeUnit unit = TimeUnit::SECONDS);
	bool IsRunning();
	float GetAccumulatedTime(TimeUnit unit = TimeUnit::MILLISECONDS);	
};