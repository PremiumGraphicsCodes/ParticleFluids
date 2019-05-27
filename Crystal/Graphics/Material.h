#pragma once

#include <list>
#include <string>
#include <memory>

#include "ColorRGBA.h"
//#include "Texture.h"

namespace Crystal {
	namespace Graphics {


struct Material
{
public:
	Material() :
		shininess(1.0f)
	{}

	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	float shininess;

	int textureId;
};

	}
}