#include "CSSampleView.h"

#include "../../Crystal/Graphics/ColorRGBA.h"
#include "../Scene/ParticleSystemScene.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

CSSampleView::CSSampleView(const std::string& name, World* world, Canvas* canvas) :
	IOkCancelView(name, world, canvas)
{
};

void CSSampleView::onOk()
{

}