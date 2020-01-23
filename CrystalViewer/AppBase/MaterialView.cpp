#include "MaterialView.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
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

void MaterialView::setValue(const Material& m)
{
	ambient.setValue(m.ambient);
	diffuse.setValue(m.diffuse);
	specular.setValue(m.specular);
	shininess.setValue(m.shininess);

	ambientTexture.setValue(m.ambientTextureName);
	diffuseTexture.setValue(m.diffuseTextureName);
	specularTexture.setValue(m.specularTextureName);
}

Material MaterialView::getValue() const
{
	Graphics::Material m;
	m.ambient = ambient.getValue();
	m.diffuse = diffuse.getValue();
	m.specular = specular.getValue();
	m.shininess = shininess.getValue();
	
	m.ambientTextureName = ambientTexture.getValue();
	m.diffuseTextureName = diffuseTexture.getValue();
	m.specularTextureName = specularTexture.getValue();
	return m;
}
