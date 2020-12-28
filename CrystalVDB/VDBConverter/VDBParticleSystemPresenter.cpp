#include "VDBParticleSystemPresenter.h"

#include "VDBParticleSystem.h"

#include "../../Crystal/Scene/SceneShader.h"
#include "../../Crystal/Scene/PointShaderScene.h"
#include "ParticleSystemImpl.h"
#include "Converter.h"
//#include "PointShaderScene.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;
using namespace Crystal::VDB;

VDBParticleSystemPresenter::VDBParticleSystemPresenter(VDBParticleSystem* model) :
	IPresenter(),
	model(model),
	view(nullptr),
	parentIdView(nullptr),
	childIdView(nullptr)
{
}

void VDBParticleSystemPresenter::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	{
		this->view = new PointShaderScene(model->getName());
		this->view->setShader(sceneShader->getObjectRenderer()->getPointShader());
		this->view->build(glFactory);
		sceneShader->getObjectRenderer()->addScene(this->view);
	}

	{
		this->parentIdView = new PointShaderScene(model->getName());
		this->parentIdView->setShader(sceneShader->getObjectRenderer()->getPointShader());
		this->parentIdView->build(glFactory);
		sceneShader->getParentIdRenderer()->addScene(this->parentIdView);
	}

	{
		this->childIdView = new PointShaderScene(model->getName());
		this->childIdView->setShader(sceneShader->getObjectRenderer()->getPointShader());
		this->childIdView->build(glFactory);
		sceneShader->getChildIdRenderer()->addScene(this->childIdView);
	}
	updateView();
}

void VDBParticleSystemPresenter::removeView(SceneShader* sceneShader, GLObjectFactory& factory)
{
	this->view->release(factory);
	sceneShader->getObjectRenderer()->removeScene(this->view);
	delete this->view;

	this->parentIdView->release(factory);
	sceneShader->getParentIdRenderer()->removeScene(this->parentIdView);
	delete this->parentIdView;

	this->childIdView->release(factory);
	sceneShader->getParentIdRenderer()->removeScene(this->childIdView);
	delete this->childIdView;
}

void VDBParticleSystemPresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void VDBParticleSystemPresenter::updateScreenView()
{
	auto impl = model->getImpl();
	const auto size = impl->size();// getShape()->getParticles();
	PointBuffer pb;
	for (int i = 0; i < size; ++i) {
		openvdb::Vec3R v;
		impl->getPos(i, v);
		pb.add(Converter::fromVDB(v), ColorRGBAf(1,1,1,1), 1.0f);
	}

	this->view->setVisible(model->isVisible());
}

void VDBParticleSystemPresenter::updateParentIdView()
{
}

void VDBParticleSystemPresenter::updateChildIdView()
{
}