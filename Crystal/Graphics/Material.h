#pragma once

#include <string>

#include "ColorRGBA.h"

namespace Crystal {
	namespace Graphics {

struct Material
{
public:
	Material() :
		shininess(1.0f),
		ambientTextureName(""),
		diffuseTextureName(""),
		specularTextureName("")
	{}

	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	float shininess;

	std::string ambientTextureName;
	std::string diffuseTextureName;
	std::string specularTextureName;
};

	}
}