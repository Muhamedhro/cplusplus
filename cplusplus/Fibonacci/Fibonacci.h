#pragma once

#include <iostream>
#include <omp.h>

#include "../Timer/Timer.h"

class Fibonacci
{
public:
	size_t GetFibonacciRecursive(size_t n);
	size_t GetFibonacciRecursiveParallel(size_t n);
	void DoFibonacciBenchmark();

private:

};