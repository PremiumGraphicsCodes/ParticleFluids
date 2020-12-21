#pragma once

#include "IPMPresenter.h"

namespace Crystal {
	namespace Scene {
		class PolygonMeshScene;
		class LineShaderScene;

class PMAsWFPresenter : public IPMPresenter
{
public:
	explicit PMAsWFPresenter(PolygonMeshScene* model);

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