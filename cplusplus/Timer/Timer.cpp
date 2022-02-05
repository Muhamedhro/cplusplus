#include "Timer.h"

Timer::Timer()
	: _currentState(TimerState::NOT_RUNNING) 
{
	_id = ++_amountOfInstances;
}

Timer::~Timer()
{
	if (_currentState == TimerState::RUNNING)
	{
		Stop();
	}
	--_amountOfInstances;
}

void Timer::Start()
{
	if (_currentState == TimerState::NOT_RUNNING)
	{
		t1 = chrono::high_resolution_clock::now();
		_currentState = TimerState::RUNNING;
	}
	else
	{
		cout << "Timer with id: " << _id << " already Running!" << endl;
	}
}
void Timer::Stop()
{
	if (_currentState == TimerState::RUNNING)
	{
		t2 = chrono::high_resolution_clock::now();
		auto elapsedTimeMs = chrono::duration_cast<chrono::milliseconds>(t2 - t1);
		cout << "Timer stopped. Time elapsed: " << elapsedTimeMs.count() << endl;
		_currentState = TimerState::NOT_RUNNING;
	}
	else
	{
		cout << "Timer with id: " << _id << " not Running!" << endl;
	}
}

void Timer::Restart()
{
	t1 = chrono::high_resolution_clock::now();
	cout << "Restarted timer with id: " << _id << endl;
}

void Timer::GetCurrentTime()
{
	if (_currentState == TimerState::RUNNING)
	{
		t2 = chrono::high_resolution_clock::now();
		auto elapsedTimeMs = chrono::duration_cast<chrono::milliseconds>(t2 - t1);
		cout << "Time elapsed (ms): " << elapsedTimeMs.count() << endl;
	}
	else
	{
		cout << "Timer with id: " << _id << " not Running!" << endl;
	}
}

void Timer::DoTimerOperation(TimerOperations timerOperation)
{
	if (timerOperation == TimerOperations::START)
	{
		Start();
	}
	else if (timerOperation == TimerOperations::STOP)
	{
		Stop();
	}
	else if (timerOperation == TimerOperations::RESTART)
	{
		Restart();
	}
	else
	{
		cout << "No valid operation for timer with id: " << this->_id << '\n';
	}
}

TimerState Timer::GetCurrentState() const
{
	return this->_currentState;
}

size_t Timer::GetTimerId() const
{
	return this->_id;
}

void Timer::PrintTimerState() const
{
	cout << "Timer with id " << GetTimerId() << " is in state " << TimerStates[(int)GetCurrentState()] << '\n';
}