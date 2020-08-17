#include "TimeSeriesParticleSystemWriter.h"

#include "../../Crystal/Shape/Particle.h"

#include <fstream>

using namespace Crystal::Physics;
using namespace Crystal::Shape;

void TimeSeriesParticleSystemWriter::add(IParticle* particle)
{
	this->particles.push_back(particle);
}

void TimeSeriesParticleSystemWriter::step()
{

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
