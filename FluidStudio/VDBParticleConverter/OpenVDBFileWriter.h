#pragma once

#include <string>
#include <openvdb/openvdb.h>

namespace Crystal {
    namespace OpenVDB {

class OpenVDBFileWriter
{
public:
    void setName(const std::string& name)
    {
        this->name = name;
    }

    void addPoint(const openvdb::Vec3R position)
    {
        this->positions.push_back(position);
    }

    void write(const std::string& filename);

private:
    std::string name;
    std::vector<openvdb::Vec3R> positions;
};

    }
}