#include "DetailsPanel.h"
#include "Bitmap.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "imgui_sdl.h"
#include "imgui_internal.h"

DetailsPanel::DetailsPanel(std::vector<Bitmap*>* hier)
{
	this->hier = hier;

}

DetailsPanel::~DetailsPanel()
{

}

void DetailsPanel::Update()
{
	if (selectedObjDeets == nullptr)
	{
		return;
	}
	ImGui::Begin("Details Panel");

	if (ImGui::Button("Close"))
	{
		selectedObjDeets = nullptr;
		ImGui::End();
		return;
	}

	static char buffer[32] = "";
	sprintf_s(buffer, std::to_string(selectedObjDeets->GetOBJPosX()).c_str());
	

	ImGui::Text("X: ");
	ImGui::SameLine();
	ImGui::InputText("##Xinput", buffer, 32, ImGuiInputTextFlags_CharsDecimal);
	int valasintX = 0;
	if (buffer[0] != '\0')
	{
		valasintX = std::stoi(buffer);
	}
	selectedObjDeets->SetOBJPosX(valasintX);

	sprintf_s(buffer, std::to_string(selectedObjDeets->GetOBJPosY()).c_str());
	ImGui::Text("Y: ");
	ImGui::SameLine();
	ImGui::InputText("##Yinput", buffer, 32, ImGuiInputTextFlags_CharsDecimal);
	int valasintY = 0;
	if (buffer[0] != '\0')
	{
		valasintY = std::stoi(buffer);
	}
	selectedObjDeets->SetOBJPosY(valasintY);

	if (selectedObjDeets != *hier->cbegin())
	{
		if (ImGui::Button("Delete"))
		{
			auto it = std::find(hier->begin(), hier->end(), selectedObjDeets);
			hier->erase(it);
			delete selectedObjDeets;
			selectedObjDeets = nullptr;
		}
	}

	ImGui::End();
}

void DetailsPanel::ChangeObj(Bitmap* objChangeto)
{
	selectedObjDeets = objChangeto;
}
