#pragma once

#include "ObjectRepository.h"
#include "AppearanceObjectRepository.h"
#include "ViewModel.h"

namespace Crystal {
	namespace UI {

class Repository
{
public:
	Repository();

	virtual ~Repository();

	void clear();

	bool read(const std::string& filename);

	bool write(const std::string& filename) const;

	ObjectRepository* getObjects() { return &objects; }

	AppearanceObjectRepository* getAppearances() { return &appearances; }

	ViewModel toViewModel();

	Math::Box3d getBoundingBox() const;

private:	
	ObjectRepository objects;
	AppearanceObjectRepository appearances;
};
	}
}