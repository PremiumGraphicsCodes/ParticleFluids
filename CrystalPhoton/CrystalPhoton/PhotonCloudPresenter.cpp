#include "PhotonCloudPresenter.h"

//#include "ParticleSystemScene.h"
#include "PhotonCloudScene.h"
#include "Photon.h"

#include "../../CrystalScene/Scene/SceneShader.h"
#include "../../CrystalScene/Scene/PointShaderScene.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;
//using namespace Crystal::Graphics;
using namespace Crystal::Photon;

PhotonCloudPresenter::PhotonCloudPresenter(PhotonCloudScene* model) :
	view(nullptr),
	model(model)
{
}

void PhotonCloudPresenter::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	{
		this->view = new PointShaderScene(model->getName());
		this->view->setShader(sceneShader->getObjectRenderer()->getPointShader());
		this->view->build(glFactory);
		sceneShader->getObjectRenderer()->addScene(this->view);
	}

	updateView();
}

void PhotonCloudPresenter::removeView(SceneShader* sceneShader, GLObjectFactory& factory)
{
	this->view->release(factory);
	sceneShader->getObjectRenderer()->removeScene(this->view);
	delete this->view;
}

void PhotonCloudPresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void PhotonCloudPresenter::updateScreenView()
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

void PhotonCloudPresenter::updateParentIdView()
{
}

void PhotonCloudPresenter::updateChildIdView()
{
}