#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <chrono>

using namespace std;

static size_t _amountOfInstances;

enum class TimerState
{
	RUNNING = 0,
	NOT_RUNNING = 1,
};

enum class TimerOperations
{
	START = 0,
	STOP = 1,
	RESTART = 2
};

const string TimerStates[] =
{
	"RUNNING",
	"NOT RUNNING"
};

class Timer
{
public:

	Timer();
	~Timer();

	size_t GetCurrentTime();

	TimerState GetCurrentState() const;
	size_t GetTimerId() const;
	void PrintTimerState() const;

	void DoTimerOperation(TimerOperations timerOperation);
	 
private:

	chrono::time_point<chrono::high_resolution_clock> t1;
	chrono::time_point<chrono::high_resolution_clock> t2;

	size_t _id;
	TimerState _currentState = TimerState::NOT_RUNNING;

	void Start();
	void Restart();
	void Stop();
};