#include "ParticleSystemEditView.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

ParticleSystemEditView::ParticleSystemEditView(const std::string& name, World* repository, Canvas* canvas) :
	IWindow(name),
	world(repository),
	particleSystem("ParticleSystem"),
	id("Id"),
	name("Name"),
	edit("Edit")
{
	edit.setFunction([=] { onEdit(); });
}

void ParticleSystemEditView::onShow()
{
	particleSystem.show();
	id.show();
	name.show();
	edit.show();
}

void ParticleSystemEditView::setValue(ParticleSystemScene* value)
{
	this->id.setValue(value->getId());
	this->name.setValue(value->getName());
}

void ParticleSystemEditView::onEdit()
{
	auto particleSystem = world->getObjects()->findSceneById<ParticleSystemScene*>( id.getValue() );
	particleSystem->setName(name.getValue());
}
