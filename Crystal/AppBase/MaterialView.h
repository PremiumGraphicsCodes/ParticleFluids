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
	explicit MaterialView(const std::string& name);

	void onShow() override;

	void setValue(const Graphics::Material& m);

	Graphics::Material getValue() const;

private:
	Float4View ambient;
	Float4View diffuse;
	Float4View specular;
	FloatView shininess;
};
	}
}