#pragma once

#include "ObjectRepository.h"
#include "LightRepository.h"
#include "MaterialRepository.h"
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

	ObjectRepository* getRepository() { return &objects; }

	LightRepository* getLights() { return &lights; }

	MaterialRepository* getMaterials() { return &materials; }

	virtual ViewModel3d toViewModel() const;

	virtual Math::Box3d getBoundingBox() const;

private:	
	ObjectRepository objects;
	LightRepository lights;
	MaterialRepository materials;
};
	}
}