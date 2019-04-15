#pragma once

#include "IWindow.h"

#include "Vector3dView.h"

#include "FloatView.h"
#include "Float4View.h"
#include "StringView.h"

#include "../Graphics/Material.h"

namespace Crystal {
	namespace UI {

class MaterialView : public IWindow
{
public:
	MaterialView(const std::string& name) :
		IWindow(name),
		ambient("Ambient", glm::vec4(0, 0, 0, 0)),
		diffuse("Diffuse", glm::vec4(0, 0, 0, 0)),
		specular("Specular", glm::vec4(0, 0, 0, 0)),
		shininess("Shininess", 1.0f)
	{
	}

	void show() override
	{
		ambient.show();
		diffuse.show();
		specular.show();
		shininess.show();
	}

	void setValue(const Graphics::Material& m) {
		ambient.setValue(m.getAmbient());
		diffuse.setValue(m.getDiffuse());
		specular.setValue(m.getSpecular());
		shininess.setValue(m.getShininess());
	}

	Graphics::Material getValue() const {
		Graphics::Material m;
		m.setAmbient(ambient.getValue());
		m.setDiffuse(diffuse.getValue());
		m.setSpecular(specular.getValue());
		m.setShininess(shininess.getValue());
		return m;
	}

private:
	Float4View ambient;
	Float4View diffuse;
	Float4View specular;
	FloatView shininess;
};
	}
}