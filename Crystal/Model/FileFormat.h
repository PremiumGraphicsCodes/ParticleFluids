#pragma once

#include <experimental/filesystem>

namespace Crystal {
	namespace Model {

enum class FileFormat
{
	STL_ASCII,
	STL_BINARY,
	OBJ,
	PCD,
	NONE,
};

static FileFormat getFileFormat(const std::experimental::filesystem::path& path)
{
	const auto& ext = path.extension();
	if (ext == ".obj") {
		return FileFormat::OBJ;
	}
	else if (ext == ".stl") {
		return FileFormat::STL_ASCII;
	}
	else if (ext == ".pcd") {
		return FileFormat::PCD;
	}
	else {
		assert(false);
		return FileFormat::NONE;
	}
}
	}
}