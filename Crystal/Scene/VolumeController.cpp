#include "VolumeController.h"

#include "VolumeScene.h"
#include "SceneShader.h"
#include "PointShaderScene.h"
#include "../Shader/GLObjectFactory.h"

using namespace Crystal::Scene;
using namespace Crystal::Shader;
using namespace Crystal::Graphics;

VolumeController::VolumeController(VolumeScene* model) :
	model(model),
	view(nullptr),
	parentIdView(nullptr),
	childIdView(nullptr)
{}

void VolumeController::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	{
		this->view = new PointShaderScene(model->getName());
		this->view->setShader(sceneShader->getObjectRenderer()->getPointShader());
		this->view->build(glFactory);
		sceneShader->getScene()->screen.add(this->view);
	}

	{
		this->parentIdView = new PointShaderScene(model->getName());
		this->parentIdView->setShader(sceneShader->getObjectRenderer()->getPointShader());
		this->parentIdView->build(glFactory);
		sceneShader->getScene()->parentId.add(this->parentIdView);
	}

	{
		this->childIdView = new PointShaderScene(model->getName());
		this->childIdView->setShader(sceneShader->getObjectRenderer()->getPointShader());
		this->childIdView->build(glFactory);
		sceneShader->getScene()->childId.add(this->childIdView);
	}
	updateView();
}

void VolumeController::updateView()
{

}

void VolumeController::updateScreenView()
{
	PointBuffer pb;

	const auto& resolutions = model->getShape()->getResolutions();
	for (int i = 0; i < resolutions[0]; ++i) {
		for (int j = 0; j < resolutions[1]; ++j) {
			for (int k = 0; k < resolutions[2]; ++k) {
				const auto& position = model->getShape()->getCellPosition(i, j, k);
				pb.add(position, ColorRGBAf(1, 1, 1, 1), 1.0f);
				//model->getShape()->getValue(i, j, k);
			}
		}
	}
	pb.setMatrix(model->getMatrix());
	this->view->send(pb);
}

void VolumeController::updateParentIdView()
{
	const auto objectId = model->getId();
	int particleId = 0;
	PointBuffer parentIdBuffer;
	parentIdBuffer.setMatrix(model->getMatrix());

	const auto& resolutions = model->getShape()->getResolutions();
	for (int i = 0; i < resolutions[0]; ++i) {
		for (int j = 0; j < resolutions[1]; ++j) {
			for (int k = 0; k < resolutions[2]; ++k) {
				DrawableID parentDid(objectId);
				const auto& position = model->getShape()->getCellPosition(i, j, k);
				parentIdBuffer.add(position, parentDid.toColor(), 1.0f);
			}
		}
	}
	parentIdView->send(parentIdBuffer);
}

void VolumeController::updateChildIdView()
{
	const auto objectId = model->getId();
	int particleId = 0;
	PointBuffer buffer;
	buffer.setMatrix(model->getMatrix());
	const auto& resolutions = model->getShape()->getResolutions();
	for (int i = 0; i < resolutions[0]; ++i) {
		for (int j = 0; j < resolutions[1]; ++j) {
			for (int k = 0; k < resolutions[2]; ++k) {
				DrawableID childDid(particleId++);
				DrawableID parentDid(objectId);
				const auto& position = model->getShape()->getCellPosition(i, j, k);
				buffer.add(position, childDid.toColor(), 1.0f);
			}
		}
	}
	childIdView->send(buffer);
}