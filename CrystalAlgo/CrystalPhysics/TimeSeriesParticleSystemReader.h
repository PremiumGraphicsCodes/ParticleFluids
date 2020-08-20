#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Scene/IAnimator.h"

#include <filesystem>

namespace Crystal {
	namespace Physics {

class TimeSeriesParticleSystemReader : public Scene::IAnimator
{
public:
	TimeSeriesParticleSystemReader();

	void setDirectryPath(const std::filesystem::path& directoryPath) { this->directoryPath = directoryPath; }

	//void add(Shape::IParticle* particle);

	void step() override;

	void reset();

private:
	bool read(const std::filesystem::path& filename);

	std::vector<Math::Vector3dd> positions;

	std::filesystem::path directoryPath;

	std::string extension;

	unsigned int step_;
};

	}
}