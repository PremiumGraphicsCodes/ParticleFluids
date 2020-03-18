#pragma once

#include "../Graphics/Material.h"
#include "../Shader/ShaderObject.h"

namespace Crystal {
	namespace Scene {

class MaterialShaderBuffer
{
public:
	void add(const Graphics::Material& m);

	std::vector<Graphics::Material> getMaterials() const { return materials; }
	
private:
	std::vector<Graphics::Material> materials;
};

	}
}