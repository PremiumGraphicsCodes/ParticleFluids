#include "PhotonPresenter.h"

//#include "ParticleSystemScene.h"
#include "PhotonScene.h"
#include "Photon.h"

#include "../../Crystal/Scene/SceneShader.h"
#include "../../Crystal/Scene/PointShaderScene.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;
//using namespace Crystal::Graphics;
using namespace Crystal::Photon;

PhotonPresenter::PhotonPresenter(PhotonScene* model) :
	view(nullptr),
	model(model)
{
}

void PhotonPresenter::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	{
		this->view = new PointShaderScene(model->getName());
		this->view->setShader(sceneShader->getObjectRenderer()->getPointShader());
		this->view->build(glFactory);
		sceneShader->getObjectRenderer()->addScene(this->view);
	}

	updateView();
}

void PhotonPresenter::removeView(SceneShader* sceneShader, GLObjectFactory& factory)
{
	this->view->release(factory);
	sceneShader->getObjectRenderer()->removeScene(this->view);
	delete this->view;
}

void PhotonPresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void PhotonPresenter::updateScreenView()
{
	const auto& ps = model->getPhotons();
	PointBuffer pb;
	for (auto p : ps) {
		pb.add(p->getPosition(), p->getColor(), p->getSize());
	}

	//this->view->setBlend(this->doBlend);
	this->view->send(pb);
	this->view->setVisible(model->isVisible());
}

void PhotonPresenter::updateParentIdView()
{
}

void PhotonPresenter::updateChildIdView()
{
}