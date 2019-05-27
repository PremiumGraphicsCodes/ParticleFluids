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
	ambient.setValue(m.ambient);
	diffuse.setValue(m.diffuse);
	specular.setValue(m.specular);
	shininess.setValue(m.shininess);
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
