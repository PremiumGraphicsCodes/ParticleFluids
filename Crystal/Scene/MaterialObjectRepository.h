#pragma once

#include "../Util/UnCopyable.h"
#include "MaterialScene.h"
#include <vector>

namespace Crystal {
	namespace Model {

class MaterialObjectRepository : private UnCopyable
{
public:
	MaterialObjectRepository();

	~MaterialObjectRepository();

	void clear();

	int add(Graphics::Material* m, const std::string& name);

	MaterialScene* findObjectById(const int id) const;

	MaterialScene* findByName(const std::string& name) const;

	std::vector<MaterialScene*> getMaterials() const { return materials; }

private:
	std::vector<MaterialScene*> materials;
	int nextId;
};

	}
}