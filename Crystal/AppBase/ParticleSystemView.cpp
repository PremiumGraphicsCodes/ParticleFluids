#include "ParticleSystemView.h"

#include "../Shape/ParticleSystem.h"

using namespace Crystal::Shape;
using namespace Crystal::UI;

ParticleSystemView::ParticleSystemView(const std::string& name) :
	IWindow(name),
	particleCount("Particles")
{}

void ParticleSystemView::onShow()
{
	particleCount.show();
}

void ParticleSystemView::setValue(IParticleSystem* value)
{
	particleCount.setValue(value->getIParticles().size());
}
