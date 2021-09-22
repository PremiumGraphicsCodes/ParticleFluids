#pragma once

#include "ITMPresenter.h"
#include "Crystal/Graphics/ColorRGBA.h"

namespace Crystal {
	namespace Scene {
		class TriangleMeshScene;
		class TriangleShaderScene;

class TMSurfacePresenter : public ITMPresenter
{
public:
	explicit TMSurfacePresenter(TriangleMeshScene* model);

	void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void removeView(SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

	TriangleShaderScene* view;
	Graphics::ColorRGBAf color;
};

	}
}