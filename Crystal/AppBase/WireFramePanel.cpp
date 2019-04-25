#include "WireFramePanel.h"

#include "WFBoxButton.h"
#include "WFSphereButton.h"
#include "WFCylinderButton.h"
#include "WFConeButton.h"
#include "WFTorusButton.h"

#include "WireFrameTreeList.h"

using namespace Crystal::UI;

WireFramePanel::WireFramePanel(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas)
{
	add( new WFBoxButton(model, canvas) );
	add( new WFSphereButton(model, canvas) );
	add( new WFCylinderButton(model, canvas) );
	add( new WFConeButton(model, canvas) );
	add( new WFTorusButton(model, canvas) );

	add(new WireFrameTreeList("WireFrames", model, canvas));

}
