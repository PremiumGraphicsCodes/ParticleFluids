#include "PolygonMeshPanel.h"
#include "../Math/Vector3d.h"
#include "../UI/Repository.h"
#include "../UI/Canvas.h"
#include "../Shape/PolygonMeshBuilder.h"
#include "../Graphics/ColorRGBA.h"
#include "imgui.h"
#include "IPopupButton.h"

#include "PMSphereButton.h"
#include "PMBoxButton.h"
#include "PMPlaneButton.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;

PolygonMeshPanel::PolygonMeshPanel(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas)
{
	add( new PMSphereButton(model, canvas) );
	add( new PMBoxButton(model, canvas) );
	add( new PMPlaneButton(model, canvas) );
}
