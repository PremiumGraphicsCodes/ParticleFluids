#include "AppearancePanel.h"

#include "MaterialAddButton.h"
#include "LightAddButton.h"
#include "ImageAddButton.h"

#include "LightTreeList.h"
#include "MaterialTreeList.h"
#include "ImageTreeList.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;


AppearancePanel::AppearancePanel(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas)
{
	add( new LightAddButton("LightAdd", model, canvas) );
	add( new LightTreeList("Lights", model, canvas) );

	add( new MaterialAddButton("MaterialAdd", model, canvas) );
	add(new MaterialTreeList("Materials", model, canvas));

	add(new ImageAddButton("Image", model, canvas));
	add(new ImageTreeList("Image", model, canvas));

}
