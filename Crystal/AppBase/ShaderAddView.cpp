#include "ShaderAddView.h"
#include "ShaderView.h"

#include "imgui.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

ShaderAddView::ShaderAddView(const std::string& name, RootScene* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	shader("Shader", model, canvas)
{
	//ImGui::InputTextMultiline()
}

void ShaderAddView::show()
{
	shader.show();
	IOkCancelView::show();
}

void ShaderAddView::onOk()
{

}