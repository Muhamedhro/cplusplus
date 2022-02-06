// cplusplus.cpp : Defines the entry point for the application.
//

#pragma once

#include <iostream>
#include <string>

#include "Timer/Timer.h"
#include "Fibonacci/Fibonacci.h"
#include "Loops/LoopParalellism.h"

using namespace std;

int main()
{
	Fibonacci fib;
	fib.DoFibonacciBenchmark();

	LoopParalellism lp;
	lp.DoLoopBenchmark();

	cout << "Press enter to exit" << endl;
	cin.get();
	return 0;
}
