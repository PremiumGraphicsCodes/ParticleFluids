#include "PCDFileExporter.h"

#include "ObjectRepository.h"

#include "../IO/PCDFileWriter.h"

using namespace Crystal::Math;
using namespace Crystal::IO;
using namespace Crystal::Model;

bool PCDFileExporter::exportPCD(const std::experimental::filesystem::path& filePath, ObjectRepository& objects)
{
	const auto& positions = objects.getParticleSystems()->getAllVertices();
	PCDFile pcd;
	pcd.header.points = positions.size();
	pcd.header.width = positions.size();
	pcd.data.positions = std::vector<Vector3dd>(positions.begin(), positions.end());
	PCDFileWriter writer;
	return writer.write(filePath, pcd);
}