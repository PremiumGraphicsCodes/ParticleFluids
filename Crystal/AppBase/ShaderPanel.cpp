#include "ShaderPanel.h"
#include "TextureAddButton.h"
#include "TextureTreeList.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

ShaderPanel::ShaderPanel(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas)
{
	add(new TextureAddButton("TextureAdd", model, canvas));
	add(new TextureTreeList("Textures", model, canvas));
}


