#include <vector>
#include "Profiler.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "imgui_sdl.h"
#include "imgui_internal.h"
#include <string>
#include "FlameGraph.h"
#include <iostream>
#include <io.h>


//FlameGraph::FlameGraph()
//{
//	ImGui::Begin("Profiler");
//
//	static FrameMap* Snapshot;
//	static std::vector<float>* FrameTimes;
//	//take snapshot of all current frame data.
//	if (ImGui::Button("take snapshot"))
//	{
//		//mem copy?
//		Snapshot = &(ProfilerSystem::Instance().GetFrameDate());
//		FrameTimes = &(ProfilerSystem::Instance().GetFrameTimes());
//	}
//	ImGui::SameLine();
//	static bool LiveFlameGraph = true;
//	ImGui::Checkbox("Live Flame Graph", &LiveFlameGraph);
//	if (LiveFlameGraph)
//	{
//		selectedFrame = -1;
//	}
//	static int range[2] = { 0, 100 };
//
//	if (FrameTimes && FrameTimes->size() > 100)
//	{
//		ImGui::SliderInt2("Frame Range", range, 0, FrameTimes->size());
//		if (range[0] >= range[1])
//			range[0] = range[1] - 1;
//		/*ImGui::SliderInt("Frame Range", &range[0], 0, FrameTimes->size());
//		if (range[0] <10)
//			range[0] =10;*/
//		std::vector<float> subData(FrameTimes->cbegin() + range[0], FrameTimes->cbegin() + range[1]);
//		//vector<float> subData(FrameTimes->cbegin() + range[0]-10, FrameTimes->cbegin() + range[0]);
//
//		int tempHistSelection = ImGui::MyPlotHistogram("Frame data", subData.data(), subData.size());
//		if (tempHistSelection != -1)
//		{
//			LiveFlameGraph = false;
//			selectedFrame = tempHistSelection;
//		}
//		ImGuiIO io = ImGui::GetIO();
//		//cout << t << endl;
//		//get mouse in hostogram
//		ImRect rect = { ImGui::GetItemRectMin(), ImGui::GetItemRectMax() };
//		if (rect.Contains(io.MousePos))
//		{
//			if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
//			{
//				std::cout << selectedFrame << std::endl;
//			}
//		}
//
//	}
//
//
//	//float GraphWindowWidth = ImGui::CalcItemWidth();
//	FrameMap& previousFrame = ProfilerSystem::Instance().GetLastFrameData();
//	if (!LiveFlameGraph && selectedFrame != -1)
//	{
//		previousFrame.clear();
//		for (auto const [SampleName, samples] : *Snapshot)
//		{
//			previousFrame[SampleName].push_back(samples[range[0] + selectedFrame]);
//		}
//	}
//	else
//	{
//		LiveFlameGraph = false;
//	}
//	//ImGui::PlotHistogram("FrameTimes")
//	ImGui::LabelText("Frame Date Count", std::to_string(previousFrame.size()).c_str());
//	//ImGui::LabelText("Graph Window Width", std::to_string(GraphWindowWidth).c_str());
//	//ImGui::RenderFrame({ 10,20 }, { 100,50 }, ImGui::GetColorU32(ImGuiCol_FrameBg), true, GImGui->Style.FrameRounding);
//	ImDrawList* drawlist = ImGui::GetCurrentWindow()->DrawList;
//	ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();//pos of screen top left
//	ImVec2 canvas_sz = ImGui::GetContentRegionAvail();   // Resize canvas to what's available
//	if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
//	if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
//	ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);
//	drawlist->PushClipRect(canvas_p0, canvas_p1, true);
//
//
//	uint64_t totalframeTime = 0;
//	std::vector<uint64_t> SampleTimes;
//	std::vector<float> SampleWidths;
//	std::vector<std::string> SampleNames;
//	for (auto const& [SampleName, samples] : previousFrame)
//	{
//		totalframeTime += samples[0]->functionTime + 1;
//		SampleTimes.push_back(samples[0]->functionTime + 1);
//		SampleNames.push_back(SampleName);
//	}
//	float MinBlockWith = canvas_sz.x / totalframeTime;// GraphWindowWidth / totalframeTime;
//	for (int i = 0; i < SampleTimes.size(); i++)
//	{
//		SampleWidths.push_back(SampleTimes[i] * MinBlockWith);
//	}
//
//	//ImGui::LabelText("Total window width", std::to_string(GraphWindowWidth).c_str());
//	ImGui::LabelText("Total Frame Time", std::to_string(totalframeTime).c_str());
//	ImGui::LabelText("Window Width / total frame Time", std::to_string(MinBlockWith).c_str());
//	float TotalBlockWidthSoFar = 0;
//
//	int sampleCount = previousFrame.size();
//	//ImGui::SliderInt("Iterations", &sampleCount, 1, 10);
//	//sampleCount = 2;
//	//MinBlockWith = GraphWindowWidth / sampleCount;
//
//	const ImU32 col_outline_base = ImGui::GetColorU32(ImGuiCol_PlotHistogram) & 0x7FFFFFFF;
//	const ImU32 col_base = ImGui::GetColorU32(ImGuiCol_PlotHistogram) & 0x77FFFFFF;
//
//	//float f = 5.0f + 5.0f;
//
//	for (int i = 0; i < sampleCount; i++)
//	{
//		float ThisBlockWidth = SampleWidths[i];
//		//if (ThisBlockWidth == 0)
//			//ThisBlockWidth = MinBlockWith;
//
//		const ImVec2 minPos = ImVec2(canvas_p0.x + TotalBlockWidthSoFar, canvas_p0.y + 100);
//		//float a = canvas_sz.x - (canvas_p1.x - (canvas_p1.x*i))
//		const ImVec2 maxPos = ImVec2(canvas_p0.x + TotalBlockWidthSoFar + ThisBlockWidth, canvas_p0.y + 200);
//		drawlist->AddRectFilled(
//			minPos,
//			maxPos,
//			col_base,
//			GImGui->Style.FrameRounding);
//
//		drawlist->AddRect(minPos, maxPos, col_outline_base);
//
//		ImGui::RenderText(ImVec2(minPos.x + 10, minPos.y + 10), SampleNames[i].c_str());
//		ImGui::RenderText(ImVec2(minPos.x + 10, minPos.y + 20), std::to_string(SampleTimes[i] - 1).c_str());
//
//
//		TotalBlockWidthSoFar += ThisBlockWidth;
//	}
//	drawlist->PopClipRect();
//
//	ImGui::End();
//}
//
//	
//
//FlameGraph::~FlameGraph()
//{
//
//}
