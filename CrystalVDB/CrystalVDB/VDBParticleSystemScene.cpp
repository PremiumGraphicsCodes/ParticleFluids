#include "VDBParticleSystemScene.h"

#include "VDBParticleSystemImpl.h"

#include "Converter.h"

#include <openvdb/points/PointConversion.h>

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBParticleSystemScene::VDBParticleSystemScene() :
    VDBParticleSystemScene(-1, "")
{}

VDBParticleSystemScene::VDBParticleSystemScene(const int id, const std::string name) :
    IParticleSystemScene(id, name)
{
    this->impl = std::make_unique<VDBParticleSystemImpl>();
    this->presenter = std::make_unique<VDBParticleSystemPresenter>(this);
}

VDBParticleSystemScene::~VDBParticleSystemScene()
{
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
    const auto positions = getPositions();
    Box3dd box(positions.front());
    for (int i = 0; i < size; ++i) {
        box.add(positions[i]);
    }
    return box;
}

std::vector<Vector3dd> VDBParticleSystemScene::getPositions() const
{
    std::vector<Vector3dd> positions;
    const auto ps = impl->getPositions();
    for (int i = 0; i < impl->size(); ++i) {
        positions.emplace_back( Converter::fromVDB(ps[i]) );
    }
    return positions;
}

void VDBParticleSystemScene::resetImpl()
{
    this->impl = std::make_unique<VDBParticleSystemImpl>();
}

void VDBParticleSystemScene::addFloatAttribute(const std::string& name)
{
    this->impl->addFloatAttribute(name);
}

void VDBParticleSystemScene::setFloatAttribute(const std::string& name, const std::vector<float>& values)
{
    this->impl->setFloatAttributes(name, values);
}

std::vector<float> VDBParticleSystemScene::getFloatAttribute(const std::string& name)
{
    return this->impl->getFloatAttributes(name);
}

bool VDBParticleSystemScene::hasAttribute(const std::string& name)
{
    return this->impl->hasAttribute(name);
}

std::vector<std::string> VDBParticleSystemScene::getAttributeNames() const
{
    const auto names = this->impl->getAttributeNames();
    std::vector<std::string> results;
    for (const auto& n : names) {
        results.push_back(n);
    }
    return results;
}

std::vector<std::string> VDBParticleSystemScene::getFloatAttributeNames() const
{
    const auto names = this->impl->getAttributeNames();
    std::vector<std::string> results;
    for (const auto& n : names) {
        if (n == "P") {
            continue;
        }
        results.push_back(n);
    }
    return results;

}

