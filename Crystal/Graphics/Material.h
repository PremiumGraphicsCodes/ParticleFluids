#ifndef __CRYSTAL_GRAPHICS_MATERIAL_H__
#define __CRYSTAL_GRAPHICS_MATERIAL_H__

#include <list>
#include <string>
#include <memory>

#include "ColorRGBA.h"
//#include "Texture.h"

namespace Crystal {
	namespace Graphics {


class Material
{
public:
	Material() :
		shininess(1.0f)
	{}

	~Material()
	{}

public:

	void setAmbient(const glm::vec4& a) { this->ambient = a; }

	glm::vec4 getAmbient() const { return ambient; }

	void setDiffuse(const glm::vec4& d) { this->diffuse = d; }

	glm::vec4 getDiffuse() const { return diffuse; }

	void setSpecular(const glm::vec4& s) { this->specular = s; }

	glm::vec4 getSpecular() const { return specular; }

	void setShininess(const float s) { this->shininess = s; }

	float getShininess() const { return shininess; }

	int getTextureId() const { return textureId; }

	void setTextureId(const int id) { this->textureId = id; }

	Material* clone() const {
		Material* m = new Material();
		m->ambient = this->ambient;
		m->diffuse = this->diffuse;
		m->specular = this->specular;
		m->shininess = this->shininess;
		m->textureId = this->textureId;
		return m;
	}

private:

	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	float shininess;

	int textureId;
};

	}
}


#endif