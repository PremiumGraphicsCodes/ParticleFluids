#pragma once

#include "ObjectRepository.h"
#include "AppearanceObjectRepository.h"
#include "ViewModel3d.h"

namespace Crystal {
	namespace UI {

class Model
{
public:
	Model();

	virtual ~Model();

	void clear();

	bool read(const std::string& filename);

	bool write(const std::string& filename) const;

	ObjectRepository* getObjects() { return &objects; }

	AppearanceObjectRepository* getAppearances() { return &appearances; }

	ViewModel3d toViewModel();

	Math::Box3d getBoundingBox() const;

private:	
	ObjectRepository objects;
	AppearanceObjectRepository appearances;
};
	}
}