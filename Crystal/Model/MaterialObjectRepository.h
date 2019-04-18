#pragma once

#include "../Util/UnCopyable.h"
#include "MaterialObject.h"
#include <vector>

namespace Crystal {
	namespace Model {

class MaterialObjectRepository : private UnCopyable
{
public:
	MaterialObjectRepository();

	~MaterialObjectRepository();

	void clear();

	void add(Graphics::Material* m, const std::string& name);

	MaterialObject* findObjectById(const int id) const;

	std::vector<MaterialObject*> getMaterials() const { return materials; }

private:
	std::vector<MaterialObject*> materials;
	int nextId;
};

	}
}