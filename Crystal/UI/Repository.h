#pragma once

#include "../Scene/Scene.h"
#include "../Scene/SceneFactory.h"
#include "../Shader/OpenGLObjectRepository.h"
#include "../Scene/ViewModel.h"
#include <filesystem>

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace UI {

class Repository : private UnCopyable
{
public:
	Repository();

	~Repository();

	void clear();

	bool importFile(const std::experimental::filesystem::path& filename);

	bool exportFile(const std::experimental::filesystem::path& filePath);

	Model::Scene* getObjects() { return &objects; }

	Model::Scene* getItems() { return &items; }

	Model::SceneFactory* getObjectFactory() { return &objectFactory; }
	
	Model::SceneFactory* getItemFactory() { return &itemFactory; }

	Shader::OpenGLObjectRepository* getShaders() { return &shaders; }

	ViewModel toViewModel();

	Math::Box3d getBoundingBox() const;

private:	
	Model::Scene objects;
	Model::Scene items;

	Model::SceneFactory objectFactory;
	Model::SceneFactory itemFactory;

	Shader::OpenGLObjectRepository shaders;
};
	}
}