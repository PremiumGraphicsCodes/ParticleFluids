#include "MaterialAddView.h"

#include "../../Crystal/Graphics/Material.h"
#include "../../Crystal/Scene/World.h"
#include "Canvas.h"

#include "../Command/Command.h"
#include "../Command/Public/MaterialCreateLabels.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

MaterialAddView::MaterialAddView(const std::string& name, World* world, Canvas* canvas) :
	IOkCancelView(name, world, canvas),
	materialView("Material"),
	nameView("Name", "Material1")
{
	add(&materialView);
	add(&nameView);
}

void MaterialAddView::onOk()
{
	const auto& m = materialView.getValue();
	Crystal::Command::Command command(MaterialCreateLabels::CommandNameLabel);
	command.setArg(MaterialCreateLabels::AmbientLabel, Graphics::ColorRGBAf( m.ambient) );
	command.setArg(MaterialCreateLabels::DiffuseLabel, Graphics::ColorRGBAf(m.diffuse));
	command.setArg(MaterialCreateLabels::SpecularLabel, Graphics::ColorRGBAf(m.specular));
	command.setArg(MaterialCreateLabels::ShininessLabel, m.shininess);
	command.setArg(MaterialCreateLabels::AmbientTextureNameLabel, m.ambientTextureName);
	command.setArg(MaterialCreateLabels::DiffuseTextureNameLabel, m.diffuseTextureName);
	command.setArg(MaterialCreateLabels::SpecularTextureNameLabel, m.specularTextureName);
	command.setArg(MaterialCreateLabels::NameLabel, nameView.getValue());
	command.execute(getWorld());
	const auto newId = command.getResult(MaterialCreateLabels::NewIdLabel);
}
