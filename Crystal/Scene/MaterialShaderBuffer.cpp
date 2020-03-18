#include "MaterialShaderBuffer.h"

#include "../Graphics/Material.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

namespace {
	constexpr char* materialIdLabel = "materialId";
}

void MaterialShaderBuffer::add(const Material& m)
{
	this->materials.push_back(m);
}

