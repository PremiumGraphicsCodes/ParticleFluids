#include "Converter.h"

using namespace Crystal::OpenVDB;

openvdb::Vec3R Converter::toVDB(const Crystal::Math::Vector3dd& p)
{
    return openvdb::Vec3R(p.x, p.y, p.z);
}

std::vector<openvdb::Vec3R> Converter::toVDB(const std::vector<Crystal::Math::Vector3dd>& positions)
{
    std::vector<openvdb::Vec3R> dest(positions.size());
    for (int i = 0; i < positions.size(); ++i) {
        dest[i] = toVDB(positions[i]);
    }
    return dest;
}

Crystal::Math::Vector3df Converter::fromVDB(const openvdb::Vec3f& p)
{
    return Crystal::Math::Vector3df(p[0], p[1], p[2]);
}

Crystal::Math::Vector3dd Converter::fromVDB(const openvdb::Vec3R& p)
{
    return Crystal::Math::Vector3dd(p[0], p[1], p[2]);
}

std::vector<Crystal::Math::Vector3dd> Converter::fromVDB(const std::vector<openvdb::Vec3R>& positions)
{
    std::vector<Crystal::Math::Vector3dd> dest(positions.size());
    for (int i = 0; i < positions.size(); ++i) {
        dest[i] = fromVDB(positions[i]);
    }
    return dest;
}

openvdb::Vec3I Converter::toVDB(const std::array<int, 3>& indices)
{
    return openvdb::Vec3I(indices[0], indices[1], indices[2]);
}

std::array<unsigned int, 3> Converter::fromVDB(const openvdb::Vec3I& src)
{
    return { src[0], src[1], src[2] };
}

openvdb::Vec4I Converter::toVDB(const std::array<int, 4>& indices)
{
    return openvdb::Vec4I(indices[0], indices[1], indices[2], indices[3]);
}

