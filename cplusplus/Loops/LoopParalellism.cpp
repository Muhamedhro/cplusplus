#include "LoopParalellism.h"

void LoopParalellism::InitOMP()
{
	//omp_set_thread_num(THREADS_AVAILABLE); // set number of threads in "parallel" blocks
}

void LoopParalellism::NormalForLoop()
{
	for (size_t i = 0; i < LOOP_RUNS; i++)
	{
		// Doe iets doms en lichts
		++i;
		--i;
	}
}
void LoopParalellism::ParallelForLoop()
{
	#pragma omp parallel
	#pragma omp for
		for (size_t i = 0; i < LOOP_RUNS; i++)
		{
			// Doe iets doms en lichts
			++i;
			--i;
		}
}
void LoopParalellism::NormalWhileLoop()
{
	size_t i = 0;
	while (i < LOOP_RUNS)
	{
		// Doe iets doms en lichts
		++i;
	}
}
void LoopParalellism::ParallelWhileLoop()
{
	size_t i = 0;
	#pragma omp parallel
		while (i < LOOP_RUNS)
		{
			// Doe iets doms en lichts
			++i;
		}
}
void LoopParalellism::IntellectuallySuperiorForLoop()
{
	for (size_t i = LOOP_RUNS; i--; )
	{
		// Doe iets doms en lichts
		++i;
		--i;
	}
}
void LoopParalellism::DoLoopBenchmark()
{
	cout << "Loop benchmarking, doing " << LOOP_RUNS << " iterations per loop." << endl;

	Timer t;
	t.DoTimerOperation(TimerOperations::START);

	NormalForLoop();

	t.DoTimerOperation(TimerOperations::STOP);
	cout << "Normal for loop ended" << endl;

	t.DoTimerOperation(TimerOperations::START);

	ParallelForLoop();

	t.DoTimerOperation(TimerOperations::STOP);
	cout << "Parallel for loop ended" << endl;

	t.DoTimerOperation(TimerOperations::START);

	NormalWhileLoop();

	t.DoTimerOperation(TimerOperations::STOP);
	cout << "Normal while loop ended" << endl;

	t.DoTimerOperation(TimerOperations::START);

	ParallelWhileLoop();

	t.DoTimerOperation(TimerOperations::STOP);
	cout << "Parallel while loop ended" << endl;

	t.DoTimerOperation(TimerOperations::START);

	IntellectuallySuperiorForLoop();

	t.DoTimerOperation(TimerOperations::STOP);
	cout << "Intellectually superior for loop ended" << endl;
}