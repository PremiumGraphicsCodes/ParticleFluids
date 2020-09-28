#include "FSPSFileReader.h"

#include <fstream>

using namespace Crystal::OpenVDB;

void FSPSFileReader::read(const std::string& filename)
{
    std::ifstream stream(filename);
    double x, y, z;
    std::string str;
    while (!stream.eof()) {
        stream >> x >> y >> z;
        positions.push_back(openvdb::Vec3R(x, y, z));
    }
    stream.close();
}
