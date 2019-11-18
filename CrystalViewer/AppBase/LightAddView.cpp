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
	const auto& l = light.getValue();

	Crystal::Command::Command command(LightCreateLabels::CommandNameLabel);
	command.setArg(LightCreateLabels::PositionLabel, Vector3dd( l.getPosition() ));
	command.setArg(LightCreateLabels::DiffuseLabel, ColorRGBAf( l.getDiffuse()));
	command.setArg(LightCreateLabels::SpecularLabel, ColorRGBAf( l.getSpecular()));
	command.setArg(LightCreateLabels::AmbientLabel, ColorRGBAf(l.getAmbient()));
	command.setArg(LightCreateLabels::NameLabel, name.getValue());
	command.execute(getWorld());
	const auto newId = command.getResult(LightCreateLabels::NewIdLabel);
}
