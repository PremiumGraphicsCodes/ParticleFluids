#include "IMVPFluidScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

IMVPFluidScene::IMVPFluidScene(const int id, const std::string& name) :
	IParticleSystemScene(id, name),
	pressureCoe(10000.0),
	viscosityCoe(50.0)
{
	this->controller = std::make_unique<MVPFluidScenePresenter>(this);
}

IMVPFluidScene::~IMVPFluidScene()
{
	clearParticles();
}

void IMVPFluidScene::clearParticles()
{
	for (auto p : particles) {
		delete p;
	}
	particles.clear();
}

Box3dd IMVPFluidScene::getBoundingBox() const
{
	if (particles.empty()) {
		return Box3dd::createDegeneratedBox();
	}
	Box3d bb(particles.front()->getPosition());
	for (auto p : particles) {
		bb.add(p->getPosition());
	}
	return bb;
}

std::vector<Vector3dd> IMVPFluidScene::getPositions() const
{
	std::vector<Vector3dd> positions;
	for (auto p : particles) {
		positions.push_back(p->getPosition());
	}
	return positions;
}

void IMVPFluidScene::removeDegeneratedVolumes()
{
	std::list<MVPVolumeParticle*> vps;
	for (auto v : particles) {
		if (v->getMassParticles().empty()) {
			vps.push_back(v);
		}
	}
	for (auto v : vps) {
		remove(v);
		delete v;
	}
}
