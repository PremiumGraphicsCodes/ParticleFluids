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
	impl->getPtr();
	/*
	const auto size = impl->size();// getShape()->getParticles();
	PointBuffer pb;
	for (int i = 0; i < size; ++i) {
		openvdb::Vec3R v;
		impl->getPos(i, v);
		pb.add(Converter::fromVDB(v), ColorRGBAf(1, 1, 1, 1), 1.0f);
	}

	this->view->setVisible(model->isVisible());
	*/
}

void VDBVolumePresenter::updateParentIdView()
{
}

void VDBVolumePresenter::updateChildIdView()
{
}