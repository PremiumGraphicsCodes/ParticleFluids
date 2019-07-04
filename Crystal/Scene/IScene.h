#pragma once

#include <list>
#include <string>
#include "SceneType.h"

#include "../Math/Box3d.h"

namespace Crystal {
	namespace UI {
		class SceneViewModel;
		class SceneIdViewModel;
	}
	namespace Model {

class IScene
{
public:
	IScene();

	explicit IScene(const int id);

	IScene(const int id, const std::string& name);

	virtual ~IScene() {};

	void clear() {
		for (const auto& c : children) {
			c->clear();
		}
		children.clear();
		onClear();
	}

	void setName(const std::string& name) { this->name = name; }

	std::string getName() const { return name; }

	int getId() const { return id; }

	bool isVisible() const { return _isVisible; }

	void setVisible(const bool b) { this->_isVisible = b; }

	//void setVisible(const bool b) { this->_isVisible = b; }

	bool _isVisible;

	virtual bool isNull() const = 0;

	virtual SceneType getType() const = 0;

	bool isSelected() const { return _isSelected; }

	void setSelected(bool b) { this->_isSelected = b; }

	void addScene(IScene* scene) {
		scene->parent = this;
		this->children.push_back(scene);
	}

	IScene* findSceneById(int id);

	IScene* findSceneByName(const std::string& name);

	virtual void addViewModel(UI::SceneViewModel& viewModel) const {};

	virtual void addViewModel(UI::SceneIdViewModel& viewModel) const {};

	virtual void getBoundingBox(Math::Box3d& box) const {}

	bool isRoot() const { return parent == nullptr; }

	IScene* getParent() const { return parent; }

	std::list<IScene*> getChildren() const { return children; }

	bool isLeaf() const { return children.empty(); }

protected:
	virtual void onClear() = 0;

protected:
	std::string name;
	int id;
	bool _isSelected;
	std::list<IScene*> children;
	IScene* parent;
};
	}
}