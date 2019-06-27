#pragma once

#include "LightObject.h"
#include <vector>

namespace Crystal {
	namespace Model {

class LightObjectRepository
{
public:
	LightObjectRepository();

	~LightObjectRepository();

	void clear();

	void add(Graphics::PointLight* l, const std::string& name);

	LightObject* findObjectById(const int id) const;

	std::vector<LightObject*> getLights() const { return lights; }

private:
	std::vector<LightObject*> lights;
	int nextId;
};
	}
}