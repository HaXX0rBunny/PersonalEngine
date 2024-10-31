#pragma once
#include <map>
#include "imgui/implot.h"
#include "../Utility/Profiler.h"
class ProfilerMoniter
{
    ProfilerMoniter() = default;
    ProfilerMoniter(const ProfilerMoniter& other) = delete;
    const ProfilerMoniter& operator=(const ProfilerMoniter& other) = delete;
    ~ProfilerMoniter();
public:
    static ProfilerMoniter* GetInstance() {
        static ProfilerMoniter Instance;  // ½Ì±ÛÅæ ÆÐÅÏ »ç¿ë
        return &Instance;
    }
	void Update();
    void Clear();

};

