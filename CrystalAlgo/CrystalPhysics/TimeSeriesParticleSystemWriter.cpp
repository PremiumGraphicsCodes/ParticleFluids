#include "TimeSeriesParticleSystemWriter.h"

using namespace Crystal::Physics;
using namespace Crystal::Shape;

void TimeSeriesParticleSystemWriter::add(IParticle* particle)
{
	this->particles.push_back(particle);
}

bool TimeSeriesParticleSystemWriter::write(const std::filesystem::path& filename)
{
	return false;
}
