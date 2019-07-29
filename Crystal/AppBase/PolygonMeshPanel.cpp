#include "PolygonMeshPanel.h"

#include "PMSphereButton.h"
#include "PMBoxView.h"
#include "PMQuadButton.h"

#include "ControlPanel.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;

PolygonMeshPanel::PolygonMeshPanel(const std::string& name, Repository* model, Canvas* canvas, ControlPanel* control) :
	IPanel(name, model, canvas),
	box("PMBox")
{
	box.setFunction([=]() { control->setWindow(new PMBoxView(getRepository(), canvas)); });

//	add( new PMSphereButton(model, canvas) );
//	add( box );
//	add( new PMQuadButton(model, canvas) );
}


void PolygonMeshPanel::show()
{
	box.show();
}
