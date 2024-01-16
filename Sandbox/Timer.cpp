#include "Timer.h"

Timer::Timer(float timeout,
			 bool looping,
			 std::function<void()> timeout_function,
			 TimeUnit unit)
{
	m_looping = looping;
	m_timeout_function = timeout_function;

	if (unit == TimeUnit::SECONDS)
	{
		m_timeout_in_milliseconds = timeout * 1000.0f;
	}
	else
	{
		m_timeout_in_milliseconds = timeout;
	}
}

Timer::~Timer()
{}

void Timer::Start()
{
	m_is_stopped = false;
	m_accumulated_time_in_milliseconds = 0.0f;
}

void Timer::Update(float dt_in_milliseconds)
{
	if (m_is_stopped)
	{
		return;
	}
	
	m_accumulated_time_in_milliseconds += dt_in_milliseconds;

	if (m_accumulated_time_in_milliseconds >= m_timeout_in_milliseconds)
	{
		Stop();

		if (m_timeout_function)
		{
			m_timeout_function();
		}
	}
}

void Timer::Stop()
{
	m_is_stopped = true;
}

void Timer::Reset(float new_timeout,
				  bool looping,
				  std::function<void()> new_timeout_function,
				  TimeUnit unit)
{
	m_is_stopped = looping;

	if (new_timeout_function != nullptr)
	{
		m_timeout_function = new_timeout_function;
	}

	if (new_timeout > 0.0f)
	{
		m_timeout_in_milliseconds = new_timeout;
		
		if (unit == TimeUnit::SECONDS)
		{
			m_timeout_in_milliseconds *= 1000.0f;
		}
	}
}

bool Timer::IsRunning()
{
	return !m_is_stopped;
}

float Timer::GetAccumulatedTime(TimeUnit unit)
{
	if (unit == TimeUnit::MILLISECONDS)
	{
		return m_accumulated_time_in_milliseconds;
	}
	else
	{
		return m_accumulated_time_in_milliseconds * 1000.0f;
	}
}