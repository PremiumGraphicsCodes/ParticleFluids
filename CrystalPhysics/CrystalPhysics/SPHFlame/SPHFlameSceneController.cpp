#include "SPHFlameSceneController.h"

#include "SPHFlameScene.h"
#include "SPHFlameParticle.h"

#include "../../../Crystal/Graphics/ColorHSV.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

SPHFlameSceneController::SPHFlameSceneController(SPHFlameScene* model) :
	model(model),
	view(nullptr),
	colorMap(300.0, 400.0, 270)
{
	for (int i = 0; i < 270; ++i) {
		ColorHSV hsv(i, 1.0, 1.0);
		ColorRGBAf c(hsv.toColorRGBf(), 0.0f);
		colorMap.setColor(269 - i, c);
	}

	//colorMap = Graphics::ColorMap::
}

void SPHFlameSceneController::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	{
		this->view = new PointShaderScene(model->getName());
		this->view->setShader(sceneShader->getObjectRenderer()->getPointShader());
		this->view->build(glFactory);
		sceneShader->getObjectRenderer()->addScene(this->view);
	}
	updateView();
}

void SPHFlameSceneController::updateView()
{
	const auto& ps = model->getParticles();
	PointBuffer pb;
	for (auto p : ps) {
		const auto c = colorMap.getColor(p->getTemperature());
		pb.add(p->getPosition(), c, 50.0);
		/*
		const auto& pts = p->getPoints();
		for (auto pp : pts) {
			pb.add(pp->getPosition(), glm::vec4(1, 1, 1, 1), 2.0);
		}
		*/
	}
	pb.setMatrix(Math::Matrix4dd());
	this->view->send(pb);

}