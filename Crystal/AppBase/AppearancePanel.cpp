#include "AppearancePanel.h"

#include "MaterialAddButton.h"
#include "LightAddButton.h"
#include "ImageAddButton.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;


AppearancePanel::AppearancePanel(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas)
{
	add( new LightAddButton("Light", model, canvas) );
	add( new MaterialAddButton("Material", model, canvas) );
	add(new ImageAddButton("Image", model, canvas));
}
