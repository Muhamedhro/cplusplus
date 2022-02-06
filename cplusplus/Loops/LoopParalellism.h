#pragma once

#include <omp.h>
#include <thread>

#include "../Timer/Timer.h"

const size_t LOOP_RUNS = 5000000000;	// 5 miljard
const unsigned int THREADS_AVAILABLE = std::thread::hardware_concurrency();

class LoopParalellism
{
public:
	void InitOMP();
	void NormalForLoop();
	void ParallelForLoop();
	void NormalWhileLoop();
	void ParallelWhileLoop();
	void IntellectuallySuperiorForLoop();
	void DoLoopBenchmark();

private:




};