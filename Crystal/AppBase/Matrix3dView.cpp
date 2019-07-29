#include "Matrix3dView.h"

#include "imgui.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void Matrix3dView::show()
{
	ImGui::InputDouble("00", &value[0][0]);
	//ImGui::SameLine();
	ImGui::InputDouble("01", &value[0][1]);
	//ImGui::SameLine();
	ImGui::InputDouble("02", &value[0][2]);

	//ImGui::SameLine();
	ImGui::InputDouble("10", &value[1][0]);
	//ImGui::SameLine();
	ImGui::InputDouble("11", &value[1][1]);
	//ImGui::SameLine();
	ImGui::InputDouble("12", &value[1][2]);

	//ImGui::SameLine();
	ImGui::InputDouble("20", &value[2][0]);
	//ImGui::SameLine();
	ImGui::InputDouble("21", &value[2][1]);
	//ImGui::SameLine();
	ImGui::InputDouble("22", &value[2][2]);
}
