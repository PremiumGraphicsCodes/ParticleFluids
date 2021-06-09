#include "SPHFlameScenePresenter.h"

#include "SPHFlameScene.h"
#include "SPHFlameParticle.h"

#include "../../../Crystal/Graphics/ColorHSV.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

SPHFlameScenePresenter::SPHFlameScenePresenter(SPHFlameScene* model) :
	model(model),
	view(nullptr)
{
	const ColorTable table = ColorTable::createDefaultTable(270);
	colorMap = ColorMap(300.0f, 400.0f, table);
}

void SPHFlameScenePresenter::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	{
		this->view = new PointShaderScene(model->getName());
		this->view->setShader(sceneShader->getObjectRenderer()->getPointShader());
		this->view->build(glFactory);
		sceneShader->getObjectRenderer()->addScene(this->view);
	}
	updateView();
}

void SPHFlameScenePresenter::updateView()
{
	const auto& ps = model->getParticles();
	PointBuffer pb;
	for (auto p : ps) {
		ColorRGBAf c;
		if (mode == Mode::Temperature) {
			c = colorMap.getColor(p->getTemperature());
		}
		else if (mode == Mode::Fuel) {
//			c = colorMap.getColor(p->get)
		}
		else {
			assert(false);
		}
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