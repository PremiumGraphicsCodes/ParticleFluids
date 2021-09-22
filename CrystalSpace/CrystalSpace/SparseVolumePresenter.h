#pragma once

#include "../../CrystalViewer/Scene/IPresenter.h"
#include "../../Crystal/Graphics/ColorMap.h"

namespace Crystal {
	namespace Scene{
		class PointShaderScene;
	}
	namespace Space {
		class SparseVolumeScene;

class SparseVolumePresenter : public Scene::IPresenter
{
public:
	explicit SparseVolumePresenter(SparseVolumeScene* model);

	void createView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void removeView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

	void setColorMap(const Graphics::ColorMap& colorMap) { this->colorMap = colorMap; }

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

private:
	Scene::PointShaderScene* view;
	SparseVolumeScene* model;
	Graphics::ColorMap colorMap;
	//PointShaderScene* parentIdView;
	//PointShaderScene* childIdView;
};

	}
}