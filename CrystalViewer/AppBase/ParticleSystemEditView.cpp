#include "ParticleSystemEditView.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

ParticleSystemEditView::ParticleSystemEditView(const std::string& name, World* world, Canvas* canvas) :
	IEditCancelView(name, world, canvas),
	particleSystemView("ParticleSystem"),
	idView("Id"),
	attributeView("Attribute")
{
}

void ParticleSystemEditView::setValue(ParticleSystemScene* value)
{
	this->idView.setValue(value->getId());
	this->particleSystemView.setValue(value);
//	this->attributeView.setName(value.getAtt)
}

void ParticleSystemEditView::onEdit()
{
	auto particleSystem = getWorld()->getScenes()->findSceneById<ParticleSystemScene*>( idView.getValue() );
	particleSystem->setName(attributeView.getName());
	particleSystem->setAttribute(attributeView.getValue());
	//getWorld()->updateViewModel();
	//particleSystem->setAttribute();
}
