#include "LightRenderer.h"

using namespace Crystal::Scene;

LightRenderer::LightRenderer()
{
}

bool LightRenderer::build(IRenderer* parent)
{
	for (int i = 0; i < 8; ++i) {
		const auto prefix = "lights[" + std::to_string(i) + "]";
		parent->addUniform(prefix + ".position");
		parent->addUniform(prefix + ".La");
		parent->addUniform(prefix + ".Ld");
		parent->addUniform(prefix + ".Ls");
	}
	return true;
}
