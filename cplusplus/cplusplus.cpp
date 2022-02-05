// cplusplus.cpp : Defines the entry point for the application.
//

#pragma once

#include <iostream>
#include <string>

#include "Timer/Timer.h"

using namespace std;

int main()
{
	Timer t;
	t.DoTimerOperation(TimerOperations::START);
	t.PrintTimerState();

	Timer t2;
	t2.DoTimerOperation(TimerOperations::START);
	t2.PrintTimerState();

	Timer t3;
	t3.DoTimerOperation(TimerOperations::START);
	t3.PrintTimerState();

	Timer t4;
	t4.DoTimerOperation(TimerOperations::START);
	t4.PrintTimerState();

	cin.get();
	return 0;
}
