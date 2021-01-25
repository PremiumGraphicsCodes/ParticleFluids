#pragma once

#include <string>
#include <vector>

#include "../../Crystal/Math/Vector3d.h"

namespace Crystal {
    namespace VDB {

class VDBFileReader
{
public:
    VDBFileReader() {}

    ~VDBFileReader();

    bool open(const std::string& filename);

    void close();

    void readMetaData();

    std::vector<std::string> getPointNames() const { return pointNames; }

    std::vector<Math::Vector3dd> readPositions(const std::string& pointName);

private:
    std::vector<std::string> pointNames;
    std::vector<std::string> floatGridNames;
};

    }
}