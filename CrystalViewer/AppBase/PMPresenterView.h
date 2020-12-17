#pragma once

#include "IView.h"
#include "ComboBox.h"

namespace Crystal {
	namespace Scene {
		class PolygonMeshScene;
		class World;
	}
	namespace UI {

class PMPresenterView : public IView
{
public:
	explicit PMPresenterView(const std::string& name);

	void setPresenter(Scene::PolygonMeshScene* scene, Scene::World* world);

private:
	ComboBox presenterView;
};
	}
}