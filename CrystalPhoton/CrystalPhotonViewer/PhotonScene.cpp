#include "PhotonScene.h"
#include "Photon.h"

#include "../../Crystal/Scene/ParticleSystemPresenter.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Photon;

PhotonScene::PhotonScene(const int id, const std::string& name) :
	IParticleSystemScene(id, name)
{
	//presenter = std::make_unique<ParticleSystemPresenter>(this);
}

Box3d PhotonScene::getBoundingBox() const
{
	if (photons.empty()) {
		return Box3d::createDegeneratedBox();
	}
	Box3d bb(photons.front()->getPosition());
	for (auto p : photons) {
		bb.add(p->getPosition());
	}
	return bb;
}

std::vector<Vector3dd> PhotonScene::getPositions() const
{
	std::vector<Vector3dd> positions;
	for (auto p : photons) {
		positions.push_back(p->getPosition());
	}
	return positions;
}