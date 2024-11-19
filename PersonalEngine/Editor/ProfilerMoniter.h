#pragma once
#include <map>
#include "imgui/implot.h"
#include "../Utility/Profiler.h"
#include <vector>
class ProfilerMoniter
{
    BigginerProfiler::Profiler* profiler = BigginerProfiler::Profiler::GetPtr();
    const int MAX_SAMPLES = 100;

    std::vector<double> timeData[9];
    std::vector<double> xData;
    int frameCount = 0;
    bool show_lines = true;
    bool show_fills = true;
    bool isEnabled;
    ProfilerMoniter(const ProfilerMoniter& other) = delete;
    const ProfilerMoniter& operator=(const ProfilerMoniter& other) = delete;
    ~ProfilerMoniter();
    ProfilerMoniter() : frameCount(0), show_lines(true), show_fills(true), isEnabled(false) {
        // ∫§≈Õ πÃ∏Æ «“¥Á
        xData.reserve(MAX_SAMPLES);
        for (int i = 0; i < 9; ++i) {
            timeData[i].reserve(MAX_SAMPLES);
        }
    }
public:

    static ProfilerMoniter* GetInstance() {
        static ProfilerMoniter Instance;  // ΩÃ±€≈Ê ∆–≈œ ªÁøÎ
        return &Instance;
    }
	void Update();

    void Clear();

};

