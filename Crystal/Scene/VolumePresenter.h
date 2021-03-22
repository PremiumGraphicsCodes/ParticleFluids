#pragma once

#include "IPresenter.h"

namespace Crystal {
	namespace Scene {
		class VolumeScene;
		class PointShaderScene;

class VolumePresenter : public IPresenter
{
public:
	explicit VolumePresenter(VolumeScene* model);

	void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void removeView(SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

private:
	PointShaderScene* view;
	VolumeScene* model;
	//PointShaderScene* parentIdView;
	//PointShaderScene* childIdView;
};

	}
}