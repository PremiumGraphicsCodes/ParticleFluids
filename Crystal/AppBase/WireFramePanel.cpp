#include "WireFramePanel.h"

#include "WFSphereButton.h"
#include "WFCylinderButton.h"
#include "WFTorusButton.h"

using namespace Crystal::UI;

WireFramePanel::WireFramePanel(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas)
{
	add( new WFSphereButton(model, canvas) );
	add( new WFCylinderButton(model, canvas) );
	add( new WFTorusButton(model, canvas) );
}
