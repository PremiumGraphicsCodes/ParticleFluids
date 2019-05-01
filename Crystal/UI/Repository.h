#pragma once

#include "../Model/ObjectRepository.h"
#include "../Model/AppearanceObjectRepository.h"
#include "../Shader/OpenGLObjectRepository.h"
#include "ViewModel.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace UI {

class Repository : private UnCopyable
{
public:
	Repository();

	~Repository();

	void clear();

	bool read(const std::string& filename);

	bool write(const std::string& filename) const;

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