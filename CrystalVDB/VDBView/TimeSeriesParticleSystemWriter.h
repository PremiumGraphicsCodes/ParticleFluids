#pragma once

#include "../../Crystal/Scene/IAnimator.h"

#include <filesystem>

namespace Crystal {
	namespace Shape {
		class IParticle;
	}
	namespace Physics {

class TimeSeriesParticleSystemWriter : public Scene::IAnimator
{
public:
	TimeSeriesParticleSystemWriter();

	void setDirectryPath(const std::filesystem::path& directoryPath) { this->directoryPath = directoryPath; }

	void add(Shape::IParticle* particle);

	void step() override;

	void reset();

private:
	bool write(const std::filesystem::path& filename);

	std::vector<Shape::IParticle*> particles;

	std::filesystem::path directoryPath;

	std::string extension;

	unsigned int step_;
};
	}
}