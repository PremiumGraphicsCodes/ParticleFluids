#pragma once

#include "IWindow.h"

#include "Vector3dView.h"
#include "Float4View.h"
#include "StringView.h"
#include "../Graphics/PointLight.h"

namespace Crystal {
	namespace UI {

class LightView : public IWindow
{
public:
	LightView(const std::string& name) :
		IWindow(name),
		position("Position", Math::Vector3dd(0, 0, 0)),
		ambient("Ambient", glm::vec4(0, 0, 0, 0)),
		diffuse("Diffuse", glm::vec4(0, 0, 0, 0)),
		specular("Specular", glm::vec4(0, 0, 0, 0))
	{
	}

	void show() override{
		position.show();
		ambient.show();
		diffuse.show();
		specular.show();
	}

	void setValue(const Graphics::PointLight& value)
	{
		this->position.setValue(value.getPosition());
		this->ambient.setValue(value.getAmbient());
		this->diffuse.setValue(value.getDiffuse());
		this->specular.setValue(value.getSpecular());
	}

	Graphics::PointLight getValue() const {
		Graphics::PointLight l = Graphics::PointLight();
		l.setPosition(position.getValue());
		l.setAmbient(ambient.getValue());
		l.setDiffuse(diffuse.getValue());
		l.setSpecular(specular.getValue());
		return l;
	}


private:
	Vector3dView position;
	Float4View ambient;
	Float4View diffuse;
	Float4View specular;
};

	}
}