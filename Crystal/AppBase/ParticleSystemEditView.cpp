#include "ParticleSystemEditView.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

ParticleSystemEditView::ParticleSystemEditView(const std::string& name, Repository* repository, Canvas* canvas) :
	IWindow(name),
	particleSystem("ParticleSystem"),
	id("Id"),
	name("Name"),
	edit("Edit")
{
}

void ParticleSystemEditView::show()
{
	particleSystem.show();
	id.show();
	name.show();
	edit.show();
}

void ParticleSystemEditView::setValue(ParticleSystemScene* value)
{
	this->particleSystem.setValue(value->getShape());
	this->id.setValue(value->getId());
	this->name.setValue(value->getName());
}

void ParticleSystemEditView::onEdit()
{

}
