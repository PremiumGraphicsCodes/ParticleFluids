#pragma once

#include <string>
#include "SceneType.h"

#include "../Math/Vector3d.h"
#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"

#include <list>

namespace Crystal {
	namespace Model {

class IScene
{
public:
	IScene() :
		id(-1),
		_isVisible(false),
		_isSelected(false)
	{}

	explicit IScene(const int id) :
		id(id),
		_isVisible(true),
		_isSelected(false)
	{}

	IScene(const int id, const std::string& name) :
		id(id),
		name(name),
		_isVisible(true),
		_isSelected(false)
	{}

	virtual ~IScene() {};

	void clear() {
		for (const auto& c : children) {
			c->clear();
		}
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

	void addScene(IScene* scene) { this->children.push_back(scene); }

	IScene* findSceneById(int id);

	IScene* findSceneByName(const std::string& name);

protected:
	virtual void onClear() = 0;

private:
	std::string name;
	int id;
	bool _isSelected;
	std::list<IScene*> children;
};
	}
}