#include "MVPVolumeConverter.h"

#include "Crystal/Shape/ParticleSystem.h"
#include "CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"
#include "Crystal/Util/Array3d.h"
#include <algorithm>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;
using namespace Crystal::Physics;

void MVPVolumeConverter::build(const std::vector<MVPVolumeParticle*>& volumeParticles, const int res, const double threshold)
{
	if (volumeParticles.empty()) {
		return;
	}
	std::vector<Vector3dd> vps;
	std::vector<Vector3dd> massParticles;
	for (auto vp : volumeParticles) {
		vps.push_back(vp->getPosition());
		const auto mps = vp->getMassParticles();
		for (auto mp : mps) {
			massParticles.push_back(mp->getPosition());
		}
	}
	const auto radius = volumeParticles.front()->getRadius();
	buildVolumes(vps, radius, res);
	buildMasses(massParticles, radius);
}

void MVPVolumeConverter::buildVolumes(const std::vector<Vector3dd>& positions, const float radius, const int res)
{
	if (positions.empty()) {
		return;
	}
	const auto r = radius;
	//const auto l = r * 2.0f;

	const auto tableSize = static_cast<int>(positions.size());
	this->sparseVolume = std::make_unique<SparseVolumef>(Vector3df(radius), tableSize);

	for (int i = 0; i < positions.size(); ++i) {
		auto vp = positions[i];
		const auto index = this->sparseVolume->toIndex(vp);
		for (int i = -res; i <= res; ++i) {
			for (int j = -res; j <= res; ++j) {
				for (int k = -res; k <= res; ++k) {
					std::array<int, 3> ix = { index[0] + i, index[1] + j, index[2] + k };
					if (!this->sparseVolume->exists(ix)) {
						this->sparseVolume->createNode(ix);
					}
				}
			}
		}
		auto n = this->sparseVolume->findNode(index);
		n->setValue(1);
	}
}

void MVPVolumeConverter::buildMasses(const std::vector<Vector3dd>& massParticles, const double radius)
{
	if (massParticles.empty()) {
		return;
	}

	ParticleSystem<float> ps(massParticles, 0.0f);
	auto pts = ps.getIParticles();


	auto res = 1;
	for (auto mp : massParticles) {
		const auto index = this->sparseVolume->toIndex(mp);
		for (int i = -res; i <= res; ++i) {
			for (int j = -res; j <= res; ++j) {
				for (int k = -res; k <= res; ++k) {
					std::array<int, 3> ix = { index[0] + i, index[1] + j, index[2] + k };
					auto n = this->sparseVolume->findNode(index);
					if (n != nullptr) {
						n->setValue(n->getValue() + 1);
					}
				}
			}
		}
	}
}