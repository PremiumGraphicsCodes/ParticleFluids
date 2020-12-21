#include "MaterialPresenter.h"

#include "MaterialScene.h"
#include "SceneShader.h"
//#include "PointShaderScene.h"
#include "SmoothShaderScene.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;

MaterialPresenter::MaterialPresenter(MaterialScene* model) :
	view(nullptr)
{
}

void MaterialPresenter::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	/*
	{
		this->view = new MaterialShaderScene(model->getName());
		this->view->setShader(sceneShader->getObjectRenderer()->getPointShader());
		this->view->build(glFactory);
		sceneShader->getObjectRenderer()->addScene(this->view);
	}
	updateView();
	*/
}

void MaterialPresenter::removeView(SceneShader* sceneShader, GLObjectFactory& factory)
{
	/*
	this->view->release(factory);
	sceneShader->getObjectRenderer()->removeScene(this->view);
	delete this->view;
	*/
}

void MaterialPresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void MaterialPresenter::updateScreenView()
{
	this->view->sendMaterial(0, *model->getMaterial());
	/*
	const auto& ps = model->getShape()->getParticles();
	PointBuffer pb;
	for (auto p : ps) {
		pb.add(p->getPosition(), p->getAttribute().color, p->getAttribute().size);
	}

	this->view->setBlend(this->doBlend);
	this->view->send(pb);
	this->view->setVisible(model->isVisible());
	*/
}

void MaterialPresenter::updateParentIdView()
{
}

void MaterialPresenter::updateChildIdView()
{
}