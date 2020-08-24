#pragma once

#include "IController.h"

namespace Crystal {
	namespace Scene {
		class VolumeScene;
		class PointShaderScene;

class VolumeController : public IPresenter
{
public:
	explicit VolumeController(VolumeScene* model);

	void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

private:
	VolumeScene* model;
	PointShaderScene* view;
	PointShaderScene* parentIdView;
	PointShaderScene* childIdView;
};

	}
}