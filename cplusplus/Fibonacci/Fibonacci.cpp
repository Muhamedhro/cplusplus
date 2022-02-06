#include "Fibonacci.h"

// Recursief, niet efficient
size_t Fibonacci::GetFibonacciRecursive(size_t n)
{
	if (n < 2)
	{
		return n;
	}
	else
	{
		return GetFibonacciRecursive(n - 1) + GetFibonacciRecursive(n - 2);
	}
}

// Recursief, niet efficient, maar wel iets beter met OpenMP
size_t Fibonacci::GetFibonacciRecursiveParallel(size_t n)
{
	if (n < 2)
	{
		return n;
	}
	else
	{
		#pragma omp task shared(x, n)
			size_t x = GetFibonacciRecursiveParallel(n - 1);
		#pragma omp task shared(y, n)
			size_t y = GetFibonacciRecursiveParallel(n - 2);
		#pragma omp taskwait

		return x + y;
	}
}

void Fibonacci::DoFibonacciBenchmark()
{
	Timer t;
	t.DoTimerOperation(TimerOperations::START);

	cout << GetFibonacciRecursive(43) << '\n';

	t.DoTimerOperation(TimerOperations::STOP);
	t.DoTimerOperation(TimerOperations::START);

	cout << GetFibonacciRecursiveParallel(43) << '\n';

	t.DoTimerOperation(TimerOperations::STOP);
}