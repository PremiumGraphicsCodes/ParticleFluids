#pragma once

#include <string>
#include "../../Crystal/Math/Vector3d.h"

namespace Crystal {
    namespace OpenVDB {

class OpenVDBFileWriter
{
public:
    void setName(const std::string& name)
    {
        this->name = name;
    }

    void addPoint(const Math::Vector3dd& position)
    {
        this->positions.push_back(position);
    }

    bool write(const std::string& filename) const;

private:
    std::string name;
    std::vector<Math::Vector3dd> positions;
};

    }
}