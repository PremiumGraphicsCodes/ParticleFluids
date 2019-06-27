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

	int add(Graphics::Material* m, const std::string& name);

	MaterialObject* findObjectById(const int id) const;

	MaterialObject* findByName(const std::string& name) const;

	std::vector<MaterialObject*> getMaterials() const { return materials; }

private:
	std::vector<MaterialObject*> materials;
	int nextId;
};

	}
}