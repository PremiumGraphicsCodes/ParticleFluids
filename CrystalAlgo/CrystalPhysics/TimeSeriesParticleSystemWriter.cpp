#include "TimeSeriesParticleSystemWriter.h"

#include "../../Crystal/Shape/Particle.h"

#include <fstream>
#include <string>

using namespace Crystal::Physics;
using namespace Crystal::Shape;

TimeSeriesParticleSystemWriter::TimeSeriesParticleSystemWriter() :
	step_(0),
	extension(".fsps")
{}

void TimeSeriesParticleSystemWriter::add(IParticle* particle)
{
	this->particles.push_back(particle);
}

void TimeSeriesParticleSystemWriter::step()
{
	auto filePath = directoryPath;
	filePath += std::to_string(step_) + extension;
	write(filePath);
	step_++;
}

void TimeSeriesParticleSystemWriter::reset()
{
	directoryPath.clear();
	this->particles.clear();
}

bool TimeSeriesParticleSystemWriter::write(const std::filesystem::path& filename)
{
	std::ofstream stream(filename);
	if (!stream.is_open()) {
		return false;
	}
	for (const auto& p : particles) {
		const auto& pos = p->getPosition();
		stream << pos.x << " " << pos.y << " " << pos.z << std::endl;
	}
	return true;
}
