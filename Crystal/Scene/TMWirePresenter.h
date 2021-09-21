#pragma once

#include "ITMPresenter.h"

namespace Crystal {
	namespace Scene {
		class TriangleMeshScene;
		class LineShaderScene;

class TMWirePresenter : public ITMPresenter
{
public:
	explicit TMWirePresenter(TriangleMeshScene* model);

	void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void removeView(SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

	LineShaderScene* getView() { return view; }

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

	LineShaderScene* view;
};

	}
}