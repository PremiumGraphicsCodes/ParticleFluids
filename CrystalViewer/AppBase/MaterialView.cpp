#include "MaterialView.h"

#include "../../Crystal/Scene/MaterialScene.h"
#include "../../Crystal/Scene/TextureScene.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

MaterialView::MaterialView(const std::string& name) :
	IView(name),
	ambient("Ambient", glm::vec4(0, 0, 0, 0)),
	diffuse("Diffuse", glm::vec4(0, 0, 0, 0)),
	specular("Specular", glm::vec4(0, 0, 0, 0)),
	shininess("Shininess", 1.0f),
	ambientTexture("AmbientTexture"),
	diffuseTexture("DiffuseTexture"),
	specularTexture("SpecularTexture")
{
	add(&ambient);
	add(&diffuse);
	add(&specular);
	add(&shininess);
	add(&ambientTexture);
	add(&diffuseTexture);
	add(&specularTexture);
}

void MaterialView::setValue(MaterialScene* m)
{
	ambient.setValue(m->getMaterial()->ambient);
	diffuse.setValue(m->getMaterial()->diffuse);
	specular.setValue(m->getMaterial()->specular);
	shininess.setValue(m->getMaterial()->shininess);

	if (m->getAmbientTexture()) {
		ambientTexture.setValue(m->getAmbientTexture()->getName());
	}
	if (m->getDiffuseTexture()) {
		diffuseTexture.setValue(m->getDiffuseTexture()->getName());
	}
	if (m->getSpecularTexture()) {
		specularTexture.setValue(m->getSpecularTexture()->getName());
	}
}