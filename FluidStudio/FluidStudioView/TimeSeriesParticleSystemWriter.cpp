#include "TimeSeriesParticleSystemWriter.h"

#include "../../Crystal/Shape/Particle.h"

#include "../OpenVDBConverter/OpenVDBFileWriter.h"

#include <fstream>
#include <string>

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Shape;
using namespace Crystal::OpenVDB;

TimeSeriesParticleSystemWriter::TimeSeriesParticleSystemWriter() :
	step_(0),
	extension(".vdb")
{}

void TimeSeriesParticleSystemWriter::add(IParticle* particle)
{
	this->particles.push_back(particle);
}

void TimeSeriesParticleSystemWriter::step()
{
	auto filePath = directoryPath;
	filePath += "//" + std::to_string(step_) + extension;
	write(filePath);
	step_++;
}

void TimeSeriesParticleSystemWriter::reset()
{
	this->directoryPath.clear();
	this->particles.clear();
}

bool TimeSeriesParticleSystemWriter::write(const std::filesystem::path& filename)
{
	std::vector<Vector3dd> positions;
	for (const auto& p : particles) {
		const auto& pos = p->getPosition();
		positions.push_back(pos);
	}

	OpenVDBFileWriter writer;
	const auto isOk = writer.open(filename.string());
	if (!isOk) {
		return false;
	}
	writer.write("Fluid", positions);
	writer.close();
	/*
	std::ofstream stream(filename);
	if (!stream.is_open()) {
		return false;
	}
	for (const auto& p : particles) {
		const auto& pos = p->getPosition();
		stream << pos.x << " " << pos.y << " " << pos.z << std::endl;
	}
	return true;
	*/
}
