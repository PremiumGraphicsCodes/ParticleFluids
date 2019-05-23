#include "PolygonMeshPanel.h"

#include "PMSphereButton.h"
#include "PMBoxButton.h"
#include "PMPlaneButton.h"

#include "PolygonMeshTreeList.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;

PolygonMeshPanel::PolygonMeshPanel(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas)
{
	add( new PMSphereButton(model, canvas) );
	add( new PMQuadButton(model, canvas) );
	add( new PMQuadButton(model, canvas) );

	add(new PolygonMeshTreeList("Polygons", model, canvas));
}
