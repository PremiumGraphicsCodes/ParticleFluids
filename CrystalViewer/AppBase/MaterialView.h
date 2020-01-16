#pragma once

#include "IView.h"

#include "Vector3dView.h"

#include "FloatView.h"
#include "Float4View.h"
#include "StringView.h"

#include "../../Crystal/Graphics/Material.h"

namespace Crystal {
	namespace UI {

class MaterialView : public IView
{
public:
	explicit MaterialView(const std::string& name);

	//void onShow() override;

	void setValue(const Graphics::Material& m);

	Graphics::Material getValue() const;

private:
	Float4View ambient;
	Float4View diffuse;
	Float4View specular;
	FloatView shininess;
	StringView ambientTexture;
	StringView diffuseTexture;
	StringView specularTexture;
};
	}
}