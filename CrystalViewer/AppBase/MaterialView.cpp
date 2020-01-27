#include "MaterialView.h"

#include "../../Crystal/Scene/MaterialScene.h"
#include "../../Crystal/Scene/TextureScene.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

MaterialView::MaterialView(const std::string& name) :
	IView(name),
	ambientView("Ambient", glm::vec4(0, 0, 0, 0)),
	diffuseView("Diffuse", glm::vec4(0, 0, 0, 0)),
	specularView("Specular", glm::vec4(0, 0, 0, 0)),
	shininessView("Shininess", 1.0f),
	ambientTextureView("AmbientTexture"),
	diffuseTextureView("DiffuseTexture"),
	specularTextureView("SpecularTexture")
{
	add(&ambientView);
	add(&diffuseView);
	add(&specularView);
	add(&shininessView);
	add(&ambientTextureView);
	add(&diffuseTextureView);
	add(&specularTextureView);
}

void MaterialView::setValue(MaterialScene* m)
{
	ambientView.setValue(m->getMaterial()->ambient);
	diffuseView.setValue(m->getMaterial()->diffuse);
	specularView.setValue(m->getMaterial()->specular);
	shininessView.setValue(m->getMaterial()->shininess);

	if (m->getAmbientTexture()) {
		ambientTextureView.setValue(m->getAmbientTexture()->getName());
	}
	if (m->getDiffuseTexture()) {
		diffuseTextureView.setValue(m->getDiffuseTexture()->getName());
	}
	if (m->getSpecularTexture()) {
		specularTextureView.setValue(m->getSpecularTexture()->getName());
	}
}