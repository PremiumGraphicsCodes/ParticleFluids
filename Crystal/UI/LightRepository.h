#pragma once

#include "../Graphics/PointLight.h"
#include <vector>

namespace Crystal {
	namespace UI {

class LightRepository
{
public:
	LightRepository();

	~LightRepository();

	void clear();

	void add(Graphics::PointLight* l);

	std::vector<Graphics::PointLight*> getLights() const { return lights; }

private:
	std::vector<Graphics::PointLight*> lights;
};
	}
}