#include "LightEditButton.h"

using namespace Crystal::UI;

LightEditButton::LightEditButton(Repository* model, Canvas* canvas) :
	IPopupButton("LightEdit", model, canvas),
	id("Id", 0),
	light("Light"),
	name("Name", "")
{
}
