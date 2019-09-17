#include "Matrix4dView.h"

#include "imgui.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void Matrix4dView::onShow()
{
	//ImGui::SameLine(); Ç≈ìØàÍçsÇ…Ç»ÇÈÅD

	ImGui::InputDouble("00", &value[0][0]);
	ImGui::InputDouble("01", &value[0][1]);
	ImGui::InputDouble("02", &value[0][2]);
	ImGui::InputDouble("03", &value[0][3]);

	ImGui::InputDouble("10", &value[1][0]);
	ImGui::InputDouble("11", &value[1][1]);
	ImGui::InputDouble("12", &value[1][2]);
	ImGui::InputDouble("13", &value[1][3]);

	ImGui::InputDouble("20", &value[2][0]);
	ImGui::InputDouble("21", &value[2][1]);
	ImGui::InputDouble("22", &value[2][2]);
	ImGui::InputDouble("23", &value[2][3]);

	ImGui::InputDouble("30", &value[3][0]);
	ImGui::InputDouble("31", &value[3][1]);
	ImGui::InputDouble("32", &value[3][2]);
	ImGui::InputDouble("33", &value[3][3]);
}
