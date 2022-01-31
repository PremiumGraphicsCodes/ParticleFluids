#pragma once

#include <string>
#include <filesystem>

#include "../Math/Vector3d.h"
#include "../Graphics/ColorRGBA.h"

namespace Crystal {
	namespace IO {

struct PLYPoint
{
	PLYPoint() = default;

	explicit PLYPoint(const Math::Vector3df& position) :
		position(position)
	{}

	Math::Vector3df position;
	//Graphics::ColorRGBAuc color;
};

struct PLYFile
{
	std::vector<PLYPoint> vertices;
};

class PLYFileWriter
{
public:
	bool writeASCII(const std::filesystem::path& filename, const PLYFile& pcd);

	bool writeASCII(std::ostream& stream, const PLYFile& pcd);

	bool writeBinary(const std::filesystem::path& filename, const PLYFile& pcd);

	bool writeBinary(std::ostream& stream, const PLYFile& pcd);


private:
	//bool write(std::ostream& stream, const PCDFile::Header& header);

	//bool write(std::ostream& stream, const PCDFile::Data& data);

private:
};

	}
}