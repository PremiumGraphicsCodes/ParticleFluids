#include "SelectionPanel.h"
#include "ObjectSelectButton.h"
#include "PositionSelectButton.h"
#include "FaceSelectButton.h"
#include "FaceGroupSelectButton.h"
#include "SphereRegionSelectButton.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;


SelectionPanel::SelectionPanel(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas)
{
	add(new ObjectSelectButton("Object", model, canvas));
	add(new PositionSelectButton("Position", model, canvas));
	add(new FaceSelectButton("Face", model, canvas));
	add(new FaceGroupSelectButton("FaceGroup", model, canvas));
	add(new SphereRegionSelectButton("SphereRegion", model, canvas));
}
