#pragma once

namespace Crystal {
	namespace Graphics {
		struct Material;
	}
	namespace Scene {
		class MaterialShaderScene;

class IMaterialScene
{
public:
	virtual void setMaterialBuffer(MaterialShaderScene* buffer) = 0;

	virtual void sendMaterial(const int index, const Graphics::Material& material) = 0;
};

	}
}
