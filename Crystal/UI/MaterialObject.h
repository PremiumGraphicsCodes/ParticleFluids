#pragma once

#include "IObject.h"
#include "../Graphics/Material.h"

namespace Crystal {
	namespace UI {

class MaterialObject : public IObject
{
public:
	MaterialObject(const int id, const std::string& name, Graphics::Material* material) :
		IObject(id, name),
		material(material)
	{}

	~MaterialObject() {};

	Graphics::Material* getMaterial() const { return material; }

private:
	Graphics::Material* material;
};

	}
}