#pragma once

#include "LightObject.h"
#include <vector>

namespace Crystal {
	namespace UI {

class LightRepository
{
public:
	LightRepository();

	~LightRepository();

	void clear();

	void add(Graphics::PointLight* l, const std::string& name);

	std::vector<LightObject> getLights() const { return lights; }

private:
	std::vector<LightObject> lights;
	int nextId;
};
	}
}