#pragma once

#include "imgui.h"
#include "implot.h"
#include "implot_internal.h"
#include <thread>

#ifdef __linux__ 
//linux code goes here

#elif _WIN32
// windows code goes here
#include "windows.h"
//#include "TCHAR.h"
#include "pdh.h"
#else

#endif



namespace MyApp
{
    const unsigned int GIGA = 1000000000;
    const unsigned int MEGA = 1000000;
    const unsigned int KILO = 1000;

    struct ResourceAvailability
    {
        static PDH_HCOUNTER cpuTotal;
        DWORDLONG totalVirtualMemory;
        DWORDLONG virtualMemoryInUse;
        DWORDLONG virtualMemoryAvailable;

        DWORDLONG totalPhysicalMemory;
    };

    struct MachineStatistics
    {
        unsigned int processorThreads = 0;

        static PDH_HQUERY cpuQuery;

        ResourceAvailability resourceAvailability;
    };


    void RenderUI();


}
