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
	ambientTexture("AmbientTex", std::string()),
	diffuseTexture("DiffuseTex", std::string()),
	specularTexture("SpecularTex", std::string())
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

	//ambientTexture.setValue(m.a)
}

Material MaterialView::getValue() const
{
	Graphics::Material m;
	m.ambient = (ambient.getValue());
	m.diffuse = (diffuse.getValue());
	m.specular = (specular.getValue());
	m.shininess = (shininess.getValue());
	return m;
}
