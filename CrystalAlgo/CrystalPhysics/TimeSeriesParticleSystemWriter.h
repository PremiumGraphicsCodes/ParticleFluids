#pragma once

#include <filesystem>

namespace Crystal {
	namespace Shape {
		class IParticle;
	}
	namespace Physics {

class TimeSeriesParticleSystemWriter
{
public:
	void add(Shape::IParticle* particle);

	bool write(const std::filesystem::path& filename);

private:
	std::vector<Shape::IParticle*> particles;

};
	}
}