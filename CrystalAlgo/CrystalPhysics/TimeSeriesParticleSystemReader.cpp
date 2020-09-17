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
	this->step_ = 0;
	this->directoryPath.clear();
	//this->particles.clear();
}

bool TimeSeriesParticleSystemReader::read(const std::filesystem::path& filename)
{
	positions.clear();

	std::ifstream stream(filename);
	if (!stream.is_open()) {
		return false;
	}
	while (!stream.eof()) {
		Vector3dd p;
		stream >> p.x >> p.y >> p.z;
		positions.push_back(p);
	}
	/*
	std::string str;
	while (std::getline(stream, str)) {
		Vector3dd p;
		stream >> p.x >> p.y >> p.z;

	}
	*/
	return true;
}
