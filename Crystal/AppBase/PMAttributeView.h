#pragma once

#include "IPopupButton.h"
#include "FloatView.h"
#include "Float4View.h"
#include "StringView.h"

#include "../UI/PolygonMeshAttribute.h"

namespace Crystal {
	namespace UI {

class PMAttributeView : public IWindow
{
public:
	PMAttributeView(const std::string& name) :
		IWindow(name),
		ambient("Ambient", glm::vec4(1, 0, 0, 0)),
		specular("Specular", glm::vec4(0, 0, 0, 0)),
		diffuse("Diffuse", glm::vec4(0, 1, 0, 0)),
		shininess("Shininess", 1.0f),
		nameView("Name", "PolygonMesh")
	{
	}

	void show() override
	{
		ambient.show();
		diffuse.show();
		specular.show();
		shininess.show();
		nameView.show();
	}

	UI::PolygonMeshAttribute getValue() const {
		UI::PolygonMeshAttribute attr;
		Graphics::Material m;
		m.setAmbient( ambient.getValue() );
		m.setDiffuse( diffuse.getValue() );
		m.setSpecular( specular.getValue() );
		m.setShininess( shininess.getValue() );
		attr.material = m;
		return attr;
	}

	std::string getName() const { return nameView.getValue(); }

private:
	Float4View ambient;
	Float4View diffuse;
	Float4View specular;
	FloatView shininess;
	StringView nameView;
};

	}
}

