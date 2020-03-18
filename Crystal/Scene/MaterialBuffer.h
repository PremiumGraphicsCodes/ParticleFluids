#pragma once

#include "IRenderer.h"

#include "../Graphics/Material.h"
#include "../Shader/ShaderObject.h"

namespace Crystal {
	namespace Scene {

class MaterialBuffer
{
public:
	void add(const Graphics::Material& m);

	void send(Shader::ShaderObject* shader);

private:
	std::vector<Graphics::Material> materials;
};

	}
}