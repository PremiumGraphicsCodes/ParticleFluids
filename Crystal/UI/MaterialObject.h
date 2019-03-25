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

	void move(const Math::Vector3dd& v) override { ; }

	void transform(const Math::Matrix3dd& m) { ; }

	void transform(const Math::Matrix4dd& m) { ; }

	bool isNull() const { return material == nullptr; }

private:
	Graphics::Material* material;
};

	}
}