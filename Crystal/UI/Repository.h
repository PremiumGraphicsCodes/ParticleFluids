#pragma once

#include "../Scene/ObjectRepository.h"
#include "../Scene/AppearanceObjectRepository.h"
#include "../Shader/OpenGLObjectRepository.h"
#include "ViewModel.h"
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

	Model::ObjectRepository* getObjects() { return &objects; }

	Model::ObjectRepository* getItems() { return &items; }

	Model::AppearanceObjectRepository* getAppearances() { return &appearances; }

	Shader::OpenGLObjectRepository* getShaders() { return &shaders; }

	ViewModel toViewModel();

	Math::Box3d getBoundingBox() const;

private:	
	Model::ObjectRepository objects;
	Model::ObjectRepository items;
	Model::AppearanceObjectRepository appearances;
	Shader::OpenGLObjectRepository shaders;

};
	}
}