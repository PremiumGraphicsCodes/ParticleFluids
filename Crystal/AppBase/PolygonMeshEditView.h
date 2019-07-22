#pragma once

#include "IWindow.h"
#include "PolygonMeshView.h"
#include "IntView.h"
#include "StringView.h"
#include "../Scene/PolygonMeshScene.h"
#include "../UI/Repository.h"
#include "../UI/Canvas.h"

namespace Crystal {
	namespace UI {

class PolygonMeshEditView : public IWindow
{
public:
	PolygonMeshEditView(const std::string& name, Repository* repository, Canvas* canvas);

	void show() override;

	void setValue(Scene::PolygonMeshScene* value);

	//void setVisible(const bool isVisible) { this->isVisible = isVisible; }

private:
	PolygonMeshView polygonMesh;
	IntView id;
	StringView name;
};

	}
}
