#include "ShaderView.h"

#include "imgui.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

ShaderView::ShaderView(const std::string& name, World* model, Canvas* canvas) :
	IPanel(name, model, canvas)
{
}

void ShaderView::show()
{
	ImGui::InputTextMultiline("VSSource", "Hello", 100, ImVec2(100, 100));
}

void ShaderView::setValue(const ShaderScene& scene)
{
	vsSource = scene.getVertexShaderSource();
	fsSource = scene.getFragmentShaderSource();
}
