#include "TextureShaderBuffer.h"

#include "../Shader/GLObjectFactory.h"
#include "../Graphics/Imagef.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

bool TextureShaderBuffer::build(GLObjectFactory& factory)
{
	for (int i = 0; i < 8; ++i) {
		factory.getTextureFactory()->createTextureObject("SmoothTex01", Imagef(512, 512));
	}
	return false;
}
