#include "MaterialAddView.h"

#include "../../Crystal/Graphics/Material.h"
#include "../../Crystal/Scene/World.h"
#include "Canvas.h"

#include "../Command/Command.h"
#include "../Command/Public/MaterialCreateLabels.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

MaterialAddView::MaterialAddView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	material("Material"),
	name("Name", "Material1")
{
	add(&material);
	add(&this->name);
}

/*
void MaterialAddView::onShow()
{
	material.show();
	name.show();
}
*/

void MaterialAddView::onOk()
{
	const auto& m = material.getValue();
	Crystal::Command::Command command(MaterialCreateLabels::CommandNameLabel);
	command.setArg(MaterialCreateLabels::AmbientLabel, Graphics::ColorRGBAf( m.ambient) );
	command.setArg(MaterialCreateLabels::DiffuseLabel, Graphics::ColorRGBAf(m.diffuse));
	command.setArg(MaterialCreateLabels::SpecularLabel, Graphics::ColorRGBAf(m.specular));
	command.setArg(MaterialCreateLabels::ShininessLabel, m.shininess);
	command.setArg(MaterialCreateLabels::TextureIdLabel, m.textureId);
	command.setArg(MaterialCreateLabels::NameLabel, name.getValue());
	command.execute(getWorld());
	const auto newId = command.getResult(MaterialCreateLabels::NewIdLabel);
}
