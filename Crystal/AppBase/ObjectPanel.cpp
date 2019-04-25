#include "ObjectPanel.h"

#include "ParticleSystemPanel.h"
#include "WireFramePanel.h"
#include "PolygonMeshPanel.h"

using namespace Crystal::UI;

ObjectPanel::ObjectPanel(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas)
{
	add(new ParticleSystemPanel("Particle", model, canvas));
	add(new WireFramePanel("WireFrame", model, canvas));
	add(new PolygonMeshPanel("Polygon", model, canvas));
}