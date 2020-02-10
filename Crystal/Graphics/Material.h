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
		ambient(0.0f, 0.0f, 0.0f, 0.0f),
		diffuse(0.0f, 0.0f, 0.0f, 0.0f),
		specular(0.0f, 0.0f, 0.0f, 0.0f),
		ambientTexId(0),
		diffuseTexId(0),
		specularTexId(0)
	{}

	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	float shininess;

	int ambientTexId;
	int diffuseTexId;
	int specularTexId;
};

	}
}