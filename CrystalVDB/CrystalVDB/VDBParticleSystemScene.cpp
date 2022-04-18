#include "VDBParticleSystemScene.h"

#include "VDBParticleSystemImpl.h"

#include "Converter.h"

#include <openvdb/points/PointConversion.h>

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBParticleSystemScene::VDBParticleSystemScene(const int id, const std::string name) :
    IParticleSystemScene(id, name)
{
    this->impl = std::make_unique<VDBParticleSystemImpl>();
    this->presenter = std::make_unique<VDBParticleSystemPresenter>(this);
}

VDBParticleSystemScene::~VDBParticleSystemScene()
{
}

void VDBParticleSystemScene::resize(const size_t count)
{
    this->impl->resize(count);
}

void VDBParticleSystemScene::create(const std::vector<Vector3dd>& positions)
{
    std::vector<openvdb::Vec3f> coords;
    for (const auto& p : positions) {
        coords.push_back(Converter::toVDB(p));
    }

    const auto transform = openvdb::math::Transform::createLinearTransform();
    //auto ptr = openvdb::points::createPointDataGrid<openvdb::points::NullCodec, openvdb::points::PointDataGrid>(coords, transform);
    auto ptr = openvdb::points::createPointDataGrid<openvdb::points::NullCodec, openvdb::points::PointDataGrid>(coords, *transform);

    impl->setPtr(ptr);
    //this->impl->setPtr()
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

/*
void VDBParticleSystemScene::fromCrystal(const std::vector<Vector3dd>& positions, const float radius)
{
    for (const auto& p : positions) {
        this->add(p, radius);
    }
}
*/

Box3dd VDBParticleSystemScene::getBoundingBox() const
{
    const auto size = impl->size();
    if (size == 0) {
        return Box3dd::createDegeneratedBox();
    }
    Box3dd box(getPosition(0));
    for (int i = 0; i < size; ++i) {
        box.add(getPosition(i));
    }
    return box;
}

std::vector<Vector3dd> VDBParticleSystemScene::getPositions() const
{
    std::vector<Vector3dd> positions;
    for (int i = 0; i < impl->size(); ++i) {
        positions.emplace_back( getPosition(i) );
    }
    return positions;
}

void VDBParticleSystemScene::resetImpl()
{
    this->impl = std::make_unique<VDBParticleSystemImpl>();
}
