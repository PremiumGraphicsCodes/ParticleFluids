#include "LightAddView.h"

#include "../../Crystal/Scene/World.h"
#include "Canvas.h"
#include "../Command/Command.h"
#include "../Command/Public/LightCreateLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;

LightAddView::LightAddView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	light("LAdd"),
	name("Name", "Light01")
{
	add(&light);
	add(&this->name);
}

void LightAddView::onOk()
{
	Crystal::Command::Command command(LightCreateLabels::CommandNameLabel);
	command.setArg(LightCreateLabels::PositionLabel, Vector3dd( light.position.getValue() ));
	command.setArg(LightCreateLabels::DiffuseLabel, ColorRGBAf( light.diffuse.getValue() ));
	command.setArg(LightCreateLabels::SpecularLabel, ColorRGBAf( light.specular.getValue() ));
	command.setArg(LightCreateLabels::AmbientLabel, ColorRGBAf(light.ambient.getValue()));
	command.setArg(LightCreateLabels::NameLabel, name.getValue());
	command.execute(getWorld());
	const auto newId = command.getResult(LightCreateLabels::NewIdLabel);
}
