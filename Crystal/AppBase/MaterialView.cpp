#include "MaterialView.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

MaterialView::MaterialView(const std::string& name) :
	IWindow(name),
	ambient("Ambient", glm::vec4(0, 0, 0, 0)),
	diffuse("Diffuse", glm::vec4(0, 0, 0, 0)),
	specular("Specular", glm::vec4(0, 0, 0, 0)),
	shininess("Shininess", 1.0f)
{
}

void MaterialView::show()
{
	ambient.show();
	diffuse.show();
	specular.show();
	shininess.show();
}

void MaterialView::setValue(const Material& m)
{
	ambient.setValue(m.getAmbient());
	diffuse.setValue(m.getDiffuse());
	specular.setValue(m.getSpecular());
	shininess.setValue(m.getShininess());
}

Material MaterialView::getValue() const
{
	Graphics::Material m;
	m.setAmbient(ambient.getValue());
	m.setDiffuse(diffuse.getValue());
	m.setSpecular(specular.getValue());
	m.setShininess(shininess.getValue());
	return m;
}
