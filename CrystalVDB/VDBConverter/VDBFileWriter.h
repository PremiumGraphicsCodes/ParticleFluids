#pragma once

#include <string>
#include "../../Crystal/Math/Vector3d.h"

namespace Crystal {
    namespace VDB {

class VDBFileWriter
{
public:
    ~VDBFileWriter();

    bool open(const std::string& filePath);

    void close();

    void write(const std::string& name, const std::vector<Math::Vector3dd>& positions) const;

private:
};

    }
}