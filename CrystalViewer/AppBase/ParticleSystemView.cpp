#include "ParticleSystemView.h"

#include "../Scene/ParticleSystemScene.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

ParticleSystemView::ParticleSystemView(const std::string& name) :
	IWindow(name),
	particleCount("Particles")
{}

void ParticleSystemView::onShow()
{
	particleCount.show();
}

void ParticleSystemView::setValue(ParticleSystemScene* value)
{
	//particleCount.setValue(value->getIParticles().size());
}
