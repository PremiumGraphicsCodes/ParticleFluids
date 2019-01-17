#pragma once

#include "../Graphics/Material.h"
#include <vector>

namespace Crystal {
	namespace UI {

class MaterialRepository
{
public:
	MaterialRepository();

	~MaterialRepository();

	void clear();

	void add(Graphics::Material* m);

	std::vector<Graphics::Material*> getMaterials() const { return materials; }

private:
	std::vector<Graphics::Material*> materials;
};

	}
}