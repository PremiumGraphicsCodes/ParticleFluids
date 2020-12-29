#include "VDBVolumePresenter.h"

#include "VDBVolume.h"

#include "../../Crystal/Scene/SceneShader.h"
#include "../../Crystal/Scene/PointShaderScene.h"
#include "VDBVolume.h"
#include "VolumeImpl.h"
#include "Converter.h"
//#include "PointShaderScene.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;
using namespace Crystal::VDB;

VDBVolumePresenter::VDBVolumePresenter(VDBVolume* model) :
	IPresenter(),
	model(model),
	view(nullptr)
{
}

void VDBVolumePresenter::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	{
		this->view = new PointShaderScene(model->getName());
		this->view->setShader(sceneShader->getObjectRenderer()->getPointShader());
		this->view->build(glFactory);
		sceneShader->getObjectRenderer()->addScene(this->view);
	}
	updateView();
}

void VDBVolumePresenter::removeView(SceneShader* sceneShader, GLObjectFactory& factory)
{
	this->view->release(factory);
	sceneShader->getObjectRenderer()->removeScene(this->view);
	delete this->view;
}

void VDBVolumePresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void VDBVolumePresenter::updateScreenView()
{
	auto impl = model->getImpl();
	auto grid = impl->getPtr();
	auto transform = grid->transform();
	PointBuffer pb;
	for (auto iter = grid->cbeginValueOn(); iter; ++iter) {
		auto coord = transform.indexToWorld(iter.getCoord());
		auto value = *iter;
		pb.add(Converter::fromVDB(coord), ColorRGBAf(1, 1, 1, 1), 1.0f);
	}
	this->view->send(pb);
	this->view->setVisible(true);
	//this->view->send(pb);
}

void VDBVolumePresenter::updateParentIdView()
{
}

void VDBVolumePresenter::updateChildIdView()
{
}