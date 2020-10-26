#pragma once

#include <string>
#include <vector>

#include "../../Crystal/Math/Vector3d.h"

namespace Crystal {
    namespace OpenVDB {

class OpenVDBFileReader
{
public:
    OpenVDBFileReader() {}

    ~OpenVDBFileReader();

    bool open(const std::string& filename);

    void close();

    std::vector<std::string> getPointGridNames() const;

    std::vector<Math::Vector3dd> readPositions(const std::string& pointName);

private:
};

    }
}