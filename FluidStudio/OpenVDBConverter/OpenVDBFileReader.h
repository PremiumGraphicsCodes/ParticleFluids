#pragma once

#include <string>
#include <vector>

#include <openvdb/openvdb.h>

namespace Crystal {
    namespace OpenVDB {

        class OpenVDBFileReader
        {
        public:
            bool read(const std::string& filename);

            std::vector<openvdb::Vec3R> getPositions() const { return positions; }

        private:
            std::vector<openvdb::Vec3R> positions;
            std::vector<openvdb::Index32> indices;
        };

    }
}