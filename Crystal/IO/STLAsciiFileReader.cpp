#include "STLASCIIFileReader.h"

#include "Helper.h"


using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::IO;

bool STLASCIIFileReader::read(const std::filesystem::path& filePath)
{
	std::ifstream stream(filePath);
	if (!stream.is_open()) {
		return false;
	}
	return read(stream);
}

bool STLASCIIFileReader::read(std::istream& stream)
{
	std::string str = Helper::read<std::string>(stream);

	if (str != "solid") {
		return false;
	}

	std::getline(stream, str);

	stl.header = str;

	str = Helper::read<std::string>(stream);
	while (str != "endsolid") {
		if (str != "facet") {
			return false;
		}
		str = Helper::read<std::string>(stream);
		if (str != "normal") {
			return false;
		}

		const auto& normal = Helper::readVector<double>(stream);

		stream >> str;
		if (str != "outer") {
			return false;
		}

		stream >> str;
		if (str != "loop") {
			return false;
		}

		std::array<Vector3dd, 3> vertices;
		for (int i = 0; i < 3; ++i) {
			stream >> str;
			if (str != "vertex") {
				return false;
			}

			vertices[i] = Helper::readVector<double>(stream);
		}

		stl.faces.push_back(TriangleFace(Triangle3d(vertices), normal));

		str = Helper::read<std::string>(stream);
		if (str != "endloop") {
			return false;
		}

		str = Helper::read<std::string>(stream);
		if (str != "endfacet") {
			return false;
		}

		str = Helper::read<std::string>(stream);
	}

	return stream.good();
}
