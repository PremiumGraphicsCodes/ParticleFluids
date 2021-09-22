#pragma once

#include "IPresenter.h"
#include "Crystal/Graphics/ColorMap.h"

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

	void setColorMap(const Graphics::ColorMap& colorMap) { this->colorMap = colorMap; }

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

private:
	PointShaderScene* view;
	VolumeScene* model;
	Graphics::ColorMap colorMap;
};

	}
}