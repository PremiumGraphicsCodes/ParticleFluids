#include "TimeSeriesParticleSystemReader.h"

//#include "../../Crystal/Shape/Particle.h"

#include <fstream>
#include <string>

using namespace Crystal::Math;
using namespace Crystal::Physics;

TimeSeriesParticleSystemReader::TimeSeriesParticleSystemReader() :
	step_(0),
	extension(".fsps")
{}

void TimeSeriesParticleSystemReader::step()
{
	auto filePath = directoryPath;
	filePath += "//" + std::to_string(step_) + extension;
	read(filePath);
	step_++;
}

void TimeSeriesParticleSystemReader::reset()
{
	this->directoryPath.clear();
	//this->particles.clear();
}

bool TimeSeriesParticleSystemReader::read(const std::filesystem::path& filename)
{
	std::ifstream stream(filename);
	if (!stream.is_open()) {
		return false;
	}
	/*
	for (const auto& p : particles) {
		const auto& pos = p->getPosition();
		stream << pos.x << " " << pos.y << " " << pos.z << std::endl;
	}
	*/
	return true;
}
