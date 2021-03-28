#include "SparseVolumePresenter.h"

#include "SparseVolumeScene.h"
#include "../../Crystal/Scene/PointShaderScene.h"
#include "../../Crystal/Scene/SceneShader.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Space;

SparseVolumePresenter::SparseVolumePresenter(SparseVolumeScene* model) :
	model(model),
	view(nullptr)
{
}

void SparseVolumePresenter::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	{
		this->view = new PointShaderScene(model->getName());
		this->view->setShader(sceneShader->getObjectRenderer()->getPointShader());
		this->view->build(glFactory);
		sceneShader->getObjectRenderer()->addScene(this->view);
	}
	updateView();
}

void SparseVolumePresenter::removeView(SceneShader* sceneShader, GLObjectFactory& factory)
{
	this->view->release(factory);
	sceneShader->getObjectRenderer()->removeScene(this->view);
	delete this->view;
}

void SparseVolumePresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void SparseVolumePresenter::updateScreenView()
{
	PointBuffer pb;
	auto nodes = model->getShape()->getNodes();

	for (const auto& node : nodes) {
		pb.add(node.second->getPosition(), ColorRGBAf(0, 0, 0, 0), 10.0f);
	}
	/*
	const auto& resolutions = shape->getResolutions();
	for (auto ix = 0; ix < resolutions[0]; ix++) {
		for (auto iy = 0; iy < resolutions[1]; iy++) {
			for (auto iz = 0; iz < resolutions[2]; iz++) {
				const auto p = shape->getCellPosition(ix, iy, iz);
				pb.add(p, ColorRGBAf(0, 0, 0, 0), 10.0f);
				//				shape->get
			}
		}
	}
	*/
	this->view->send(pb);
	/*
	for (auto p : ps) {
		pb.add(p->getPosition(), p->getAttribute().color, p->getAttribute().size);
	}
	*/
}

void SparseVolumePresenter::updateParentIdView()
{
}

void SparseVolumePresenter::updateChildIdView()
{
}