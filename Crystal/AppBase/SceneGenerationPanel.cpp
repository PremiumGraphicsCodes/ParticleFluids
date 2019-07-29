#include "SceneGenerationPanel.h"

#include "ParticleSystemPanel.h"
#include "WireFramePanel.h"
#include "PolygonMeshPanel.h"

#include "MaterialAddButton.h"
#include "LightAddButton.h"
#include "TextureAddButton.h"
#include "ColorMapView.h"

#include "../Graphics/ColorHSV.h"

using namespace Crystal::Graphics;
using namespace Crystal::UI;

SceneGenerationPanel::SceneGenerationPanel(const std::string& name, Repository* model, Canvas* canvas, ControlPanel* control) :
	IPanel(name, model, canvas)
{
	add(new ParticleSystemPanel("", model, canvas, control));
	add(new WireFramePanel("", model, canvas));
	add(new PolygonMeshPanel("", model, canvas, control));

	add(new LightAddButton("LightAdd", model, canvas));
	add(new MaterialAddButton("MaterialAdd", model, canvas));
	add(new TextureAddButton("Texture", model, canvas));

	ColorMap colorMap(0.0, 1.0, 360);
	for (int i = 0; i < 360; ++i) {
		ColorHSV hsv(i, 1.0, 1.0);
		colorMap.setColor(i, hsv.toColorRGBA());
	}
	add(new ColorMapView("ColorMap", colorMap));

}