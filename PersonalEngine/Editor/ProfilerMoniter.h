#pragma once
#include <map>
#include "imgui/implot.h"
class ProfilerMoniter
{

public:
	void Update();
    template <typename T>
    inline T RandomRange(T min, T max);
};

template<typename T>
inline T ProfilerMoniter::RandomRange(T min, T max)
{

 
            T scale = rand() / (T)RAND_MAX;
            return min + scale * (max - min);


}
