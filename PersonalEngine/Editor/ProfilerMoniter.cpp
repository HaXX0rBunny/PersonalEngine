#include "ProfilerMoniter.h"
#include <math.h>
#include <vector>
#include "../Utility/InputProcess.h"
ProfilerMoniter::~ProfilerMoniter()
{
}

void ProfilerMoniter::Update()
{
	// F1 키로 토글
    if (Keystate::keystateF1 == GL_TRUE) {
        isEnabled = !isEnabled;
        if (!isEnabled) {
            Clear();
        }
        Keystate::keystateF1 = GL_FALSE;
    }

	// 활성화된 상태일 때만 프로파일러 업데이트
	if (!isEnabled) return;
	// 새로운 데이터 추가
	if (!profiler->GetBlock().empty()) {
		frameCount++;

		double times[9] = { 0 };
		for (const auto* block : profiler->GetBlock()) {
			std::string name = block->GetName();
			double time = block->GetSeconds() * 1000000.0; // 마이크로초 변환

			if (name == "Camera") times[0] = time;
			else if (name == "Transform") times[1] = time;
			else if (name == "Grapics") times[2] = time;
			else if (name == "player") times[3] = time;
			else if (name == "Collision") times[4] = time;
			else if (name == "Event") times[5] = time;
			else if (name == "Editor") times[6] = time;
			else if (name == "GOM") times[7] = time;
			else if (name == "Logic") times[8] = time;
		}


		xData.push_back(static_cast<double>(frameCount));
		for (int i = 0; i < 9; ++i) {
			timeData[i].push_back(times[i]);
		}

		// 최대 샘플 수 유지
		if (xData.size() > MAX_SAMPLES) {
			xData.erase(xData.begin());
			for (int i = 0; i < 9; ++i) {
				timeData[i].erase(timeData[i].begin());
			}
		}
	}
	if (ImGui::Begin("Profiler", &isEnabled)) {
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
								   "Player", "Collision", "Event","Editor","GOM","Logic" };

			if (!xData.empty()) {
				ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
				for (int i = 0; i < 9; ++i) {
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
		ImGui::End();
	}
}

void ProfilerMoniter::Clear()
{
	// 모든 데이터 벡터 초기화
	xData.clear();
	for (int i = 0; i < 9; ++i) {
		timeData[i].clear();
	}

	// 프레임 카운트 리셋
	frameCount = 0;

	// 벡터 용량 최적화 (선택사항)
	xData.shrink_to_fit();
	for (int i = 0; i < 9; ++i) {
		timeData[i].shrink_to_fit();
	}

}
