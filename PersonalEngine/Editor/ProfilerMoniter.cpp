#include "ProfilerMoniter.h"
#include <math.h>
#include <vector>

ProfilerMoniter::~ProfilerMoniter()
{
}

void ProfilerMoniter::Update()
{
    BigginerProfiler::Profiler* profiler = BigginerProfiler::Profiler::GetPtr();
    const int MAX_SAMPLES = 100;

    static std::vector<double> timeData[7];
    static std::vector<double> xData;
    static int frameCount = 0;
    static bool show_lines = true;
    static bool show_fills = true;

    // 새로운 데이터 추가
    if (!profiler->GetBlock().empty()) {
        frameCount++;

        double times[7] = { 0 };
        for (const auto* block : profiler->GetBlock()) {
            std::string name = block->GetName();
            double time = block->GetSeconds() * 1000000.0; // 마이크로초 변환

            if (name == "Camera") times[0] = time;
            else if (name == "Transform") times[1] = time;
            else if (name == "Grapics") times[2] = time;
            else if (name == "player") times[3] = time;
            else if (name == "Collision") times[4] = time;
            else if (name == "Event") times[5] = time;
        }

       
        xData.push_back(static_cast<double>(frameCount));
        for (int i = 0; i < 7; ++i) {
            timeData[i].push_back(times[i]);
        }

        // 최대 샘플 수 유지
        if (xData.size() > MAX_SAMPLES) {
            xData.erase(xData.begin());
            for (int i = 0; i < 7; ++i) {
                timeData[i].erase(timeData[i].begin());
            }
        }
    }

    if (ImPlot::BeginPlot("Profiler Data (Microseconds)")) {
        // 자동 스크롤을 위한 X축 설정
        double xmin = frameCount - MAX_SAMPLES;
        double xmax = frameCount;

        ImPlot::SetupAxes("Frames", "Time (1000/s)",
            ImPlotAxisFlags_AutoFit,  // X축 자동 맞춤
            ImPlotAxisFlags_AutoFit); // Y축 자동 맞춤

        // 현재 시간 범위로 축 설정
        ImPlot::SetupAxesLimits(xmin, xmax, 0, 1200, ImPlotCond_Always);

        const char* labels[] = { "Camera", "Transform", "Graphics",
                               "Player", "Collision", "Event" };

        if (!xData.empty()) {
            ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
            for (int i = 0; i < 6; ++i) {
                if (show_fills) {
                    ImPlot::PlotShaded(labels[i], xData.data(), timeData[i].data(),
                        xData.size(), 0.0);
                }
                if (show_lines) {
                    ImPlot::PlotLine(labels[i], xData.data(), timeData[i].data(),
                        xData.size());
                }
            }
            ImPlot::PopStyleVar();
        }
        ImPlot::EndPlot();
    }

    ImGui::Checkbox("Lines", &show_lines);
    ImGui::SameLine();
    ImGui::Checkbox("Fills", &show_fills);
}