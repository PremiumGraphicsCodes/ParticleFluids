
#include "ParticleSystemEditView.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

ParticleSystemEditView::ParticleSystemEditView(const std::string& name, World* repository, Canvas* canvas) :
	IWindow(name),
	world(repository),
	canvas(canvas),
	particleSystemView("ParticleSystem"),
	idView("Id"),
	attributeView("Attribute"),
	edit("Edit")
{
	edit.setFunction([=] { onEdit(); });
}

void ParticleSystemEditView::onShow()
{
	particleSystemView.show();
	idView.show();
	attributeView.show();
	edit.show();
}

void ParticleSystemEditView::setValue(ParticleSystemScene* value)
{
	this->idView.setValue(value->getId());
	//this->name.setValue(value->getName());
}

void ParticleSystemEditView::onEdit()
{
	auto particleSystem = world->getObjects()->findSceneById<ParticleSystemScene*>( idView.getValue() );
	particleSystem->setName(attributeView.getName());
	particleSystem->setAttribute(attributeView.getValue());
	world->updateViewModel();
	//particleSystem->setAttribute();
}
