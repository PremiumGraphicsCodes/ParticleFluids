#pragma once

#include "ObjectRepository.h"
#include "AppearanceObjectRepository.h"
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