#include "KFBoundaryScenePresenter.h"

#include "KFBoundaryScene.h"
#include "KFBoundaryParticle.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

KFBoundaryScenePresenter::KFBoundaryScenePresenter(KFBoundaryScene* model) :
	model(model),
	view(nullptr)
{}

void KFBoundaryScenePresenter::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	{
		this->view = new PointShaderScene(model->getName());
		this->view->setShader(sceneShader->getObjectRenderer()->getPointShader());
		this->view->build(glFactory);
		sceneShader->getObjectRenderer()->addScene(this->view);
	}
	updateView();
}

void KFBoundaryScenePresenter::updateView()
{
	const auto& ps = model->getParticles();
	PointBuffer pb;
	for (auto p : ps) {
		pb.add(p->getPosition(), glm::vec4(1, 1, 1, 0.25), 10.0);
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