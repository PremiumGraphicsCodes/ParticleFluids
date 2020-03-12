#pragma once

#include <list>
#include <string>
#include "SceneType.h"

#include "../Math/Box3d.h"
#include "../Graphics/Camera.h"
#include "../Shader/GLObjectFactory.h"

namespace Crystal {
	namespace Shader {
		class IShaderCommand;
	}
	namespace Scene {
		class SceneIdViewModel;
		class SceneRenderer;

class IScene
{
public:
	IScene();

	explicit IScene(const int id);

	IScene(const int id, const std::string& name);

	virtual ~IScene();

	void clear();

	void setName(const std::string& name) { this->name = name; }

	std::string getName() const { return name; }

	int getId() const { return id; }

	bool isVisible() const { return _isVisible; }

	void setVisible(const bool b) { this->_isVisible = b; }

	//void setVisible(const bool b) { this->_isVisible = b; }

	bool _isVisible;

	bool _isPickable;

	bool isPickable() const { return _isPickable; }

	virtual SceneType getType() const = 0;

	void addScene(IScene* scene);

	IScene* findSceneById(int id);

	IScene* findSceneByName(const std::string& name);

	void deleteSceneById(int id);

	template<class T>
	T findSceneById(int id) { return static_cast<T>( findSceneById(id) ); }

	template<class T>
	T findSceneByName(const std::string& name) { return static_cast<T>(findSceneByName(name)); }

	std::list<IScene*> findScenes(SceneType type);

	virtual void send(SceneIdViewModel& parentIdViewModel, SceneIdViewModel& childIdViewModel) const {}

	virtual Math::Box3d getBoundingBox() const { return Math::Box3d::createDegeneratedBox(); }

	bool isRoot() const { return parent == nullptr; }

	IScene* getParent() const { return parent; }

	IScene* getRoot();

	std::list<IScene*> getChildren() const { return children; }

	bool isLeaf() const { return children.empty(); }

	void build(Shader::GLObjectFactory& factory);

	virtual void send();

	void render(SceneRenderer* renderer);

protected:
	virtual void onClear() = 0;

	virtual void onBuild(Shader::GLObjectFactory& factory) {};

	virtual void onSend() {};

	virtual void onRender(SceneRenderer* renderer) {};

protected:
	std::string name;
	int id;
	std::list<IScene*> children;
	IScene* parent;
};
	}
}