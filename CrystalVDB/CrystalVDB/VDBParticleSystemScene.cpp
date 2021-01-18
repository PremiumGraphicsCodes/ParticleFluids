#include "VDBParticleSystemScene.h"

#include "VDBParticleSystemImpl.h"

#include "Converter.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

Crystal::VDB::VDBParticleSystemScene::VDBParticleSystemScene(const int id, const std::string name) :
    IShapeScene(id, name)
{
    this->impl = std::make_unique<VDBParticleSystemImpl>();
    this->presenter = std::make_unique<VDBParticleSystemPresenter>(this);
}

VDBParticleSystemScene::~VDBParticleSystemScene()
{
}

void VDBParticleSystemScene::add(const Vector3dd& position, const double radius)
{
    const auto pp = Converter::toVDB(position);
    impl->add(pp, radius);
}

Crystal::Math::Vector3dd VDBParticleSystemScene::getPosition(const int index) const
{
    openvdb::Vec3R v;
    impl->getPos(index, v);
    return Converter::fromVDB(v);
}

float VDBParticleSystemScene::getSize(const int index) const
{
    openvdb::Real radius;
    openvdb::Vec3R v;
    impl->getPosRad(index, v, radius);
    return radius;
}

void VDBParticleSystemScene::fromCrystal(const std::vector<Vector3dd>& positions, const float radius)
{
    for (const auto& p : positions) {
        this->add(p, radius);
    }
}

Box3d VDBParticleSystemScene::getBoundingBox() const
{
    const auto size = impl->size();
    if (size == 0) {
        return Box3d::createDegeneratedBox();
    }
    Box3d box(getPosition(0));
    for (int i = 0; i < size; ++i) {
        box.add(getPosition(i));
    }
    return box;
}