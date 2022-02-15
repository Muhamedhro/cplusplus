
#include "App.h"


MEMORYSTATUSEX GetMemInfo()
{
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    return memInfo;
}

DWORDLONG GetTotalVirtualMemory()
{
    MEMORYSTATUSEX memInfo = GetMemInfo();
    DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;
    return totalVirtualMem;
}

DWORDLONG GetTotalVirtualMemoryInUse()
{
    MEMORYSTATUSEX memInfo = GetMemInfo();
    DWORDLONG virtualMemUsed = memInfo.ullTotalPageFile - memInfo.ullAvailPageFile;
    return virtualMemUsed;
}

DWORDLONG GetTotalVirtualMemoryAvailable()
{
    return GetMemInfo().ullAvailPageFile;
}

DWORDLONG GetTotalPhysicalMemory()
{
    return GetMemInfo().ullTotalPhys;
}

void PlotCpuUsage()
{
    // TODO: Implementeren
}

void PlotRamUsage()
{
    // TODO: Implementeren
}


//void CollectCpuData()
//{
//    PdhOpenQuery(NULL, NULL, &MyApp::cpuStat.cpuQuery);
//    // You can also use L"\\Processor(*)\\% Processor Time" and get individual CPU values with PdhGetFormattedCounterArray()
//    PdhAddEnglishCounter(MyApp::cpuStat.cpuQuery, L"\\Processor(_Total)\\% Processor Time", NULL, &MyApp::cpuAvailability.cpuTotal);
//    PdhCollectQueryData(MyApp::cpuStat.cpuQuery);
//}
//
//double GetCpuUsage()
//{
//    PDH_FMT_COUNTERVALUE counterVal;
//
//    PdhCollectQueryData(MyApp::cpuStat.cpuQuery);
//    PdhGetFormattedCounterValue(MyApp::cpuAvailability.cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);
//    return counterVal.doubleValue;
//}

// Uit de imgui demo gejat
void MakeDockable()
{
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", nullptr, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Options"))
        {
            // Disabling fullscreen would allow the window to be moved to the front of other windows,
            // which we can't undo at the moment without finer window depth/z control.
            ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
            ImGui::MenuItem("Padding", NULL, &opt_padding);
            ImGui::Separator();

            if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
            if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
            if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
            if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
            if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
            ImGui::Separator();
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }
}

void MyApp::RenderUI()
{

    MakeDockable();

    // Begin functionaliteit: variabelen te tonen
    // Vars worden met een frequentie geupdate, daar zorgt gui code voor onder water
    

    MachineStatistics machineStat;

    machineStat.processorThreads = std::thread::hardware_concurrency();
    machineStat.resourceAvailability.totalVirtualMemory = GetTotalVirtualMemory();
    machineStat.resourceAvailability.totalPhysicalMemory = GetTotalPhysicalMemory();
    machineStat.resourceAvailability.virtualMemoryInUse = GetTotalVirtualMemoryInUse();
    machineStat.resourceAvailability.virtualMemoryAvailable = GetTotalVirtualMemoryAvailable();
    //CollectCpuData();

    ImGui::Begin("CPU Statistics");

    if (ImGui::GetIO().Framerate > 118)
    {
        ImGui::Text("Framerate: %f (nice)", ImGui::GetIO().Framerate);
    }
    else
    {
        ImGui::Text("Framerate: %f", ImGui::GetIO().Framerate);
    }
    
    ImGui::Text("Aantal processor threads: %i", machineStat.processorThreads);

    // TODO: memory waarden lijken niet echt te kloppen
    if (ImGui::TreeNode("Virtual memory"))
    {
        static bool plotVirtualMemory = false;
        ImGui::Checkbox("Plot statistics", &plotVirtualMemory);

        ImGui::Text("Totaal virtueel geheugen: %lu Bytes (%f MB)",
            machineStat.resourceAvailability.totalVirtualMemory,
            (float)machineStat.resourceAvailability.totalVirtualMemory / MyApp::MEGA);

        ImGui::Text("Virtueel geheugen in gebruik: %lu Bytes (%f MB)",
            machineStat.resourceAvailability.virtualMemoryInUse,
            (float)machineStat.resourceAvailability.virtualMemoryInUse / MyApp::MEGA);

        ImGui::Text("Vrij virtuel geheugen: %lu Bytes (%f MB)",
            machineStat.resourceAvailability.virtualMemoryAvailable,
            (float)machineStat.resourceAvailability.virtualMemoryAvailable / MyApp::MEGA);

        if (plotVirtualMemory)
        {
            //TODO: plotten
        }

        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Physical memory"))
    {
        static bool plotPhysicalMemory = false;
        ImGui::Checkbox("Plot statistics", &plotPhysicalMemory);

        ImGui::Text("Totaal fysiek geheugen: %lu Bytes (%f GB)",
            machineStat.resourceAvailability.totalPhysicalMemory,
            (float)machineStat.resourceAvailability.totalPhysicalMemory / MyApp::GIGA);

        if (plotPhysicalMemory)
        {
            // TODO: plotten
            /*
            static int offset = 0;
            offset = (offset + 1) % 100;
             
            ImPlot::CreateContext();

            if (ImPlot::BeginPlot("Fysiek geheugen"))
            {
                ImGui::Text("%.3f Totaal fysiek geheugen", data[offset]);
                MyImPlot::Sparkline("##spark", data, 100, 0, 11.0f, offset, ImPlot::GetColormapColor(row), ImVec2(-1, 35));
                ImPlot::EndPlot();
            }

            ImPlot::DestroyContext();
            */
        }

        ImGui::TreePop();
    }





    //ImGui::Text("Totaal CPU in gebruik: %li", GetCpuUsage());

    


    ImGui::End();



    ImGui::End();



    //ImGui::ShowDemoWindow();

}

