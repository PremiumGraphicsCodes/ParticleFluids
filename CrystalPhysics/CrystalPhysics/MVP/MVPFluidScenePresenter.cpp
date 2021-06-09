#include "MVPFluidScenePresenter.h"

#include "MVPFluidScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

MVPFluidScenePresenter::MVPFluidScenePresenter(IMVPFluidScene* model) :
	model(model),
	view(nullptr),
	mode(Mode::Density)
{
	colorMap = ColorMap(0.8f, 1.2f, ColorTable::createDefaultTable(270));
}

void MVPFluidScenePresenter::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	{
		this->view = new PointShaderScene(model->getName());
		this->view->setShader(sceneShader->getObjectRenderer()->getPointShader());
		this->view->build(glFactory);
		sceneShader->getObjectRenderer()->addScene(this->view);
	}
	updateView();
}

void MVPFluidScenePresenter::updateView()
{
	const auto& ps = model->getParticles();
	PointBuffer pb;
	for (auto p : ps) {
		ColorRGBAf c;
		if (mode == Mode::Uniform) {
			c = glm::vec4(1, 1, 1, 0.25);
		}
		else if (mode == Mode::Density) {
			c = colorMap.getInterpolatedColor(p->getDensity());
		}
		else {
			assert(false);
		}
		pb.add(p->getPosition(), c, 10.0);
		/*
		const auto& pts = p->getPoints();
		for (auto pp : pts) {
			pb.add(pp->getPosition(), glm::vec4(1, 1, 1, 1), 2.0);
		}
		*/
	}
	pb.setMatrix(Math::Matrix4dd());
//	this->view->setBlend(true);
	this->view->send(pb);
}