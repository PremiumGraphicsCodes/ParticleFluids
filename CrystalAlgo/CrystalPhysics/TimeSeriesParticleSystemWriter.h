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
	void add(Shape::IParticle* particle);

	void step() override;

private:
	bool write(const std::filesystem::path& filename);

	std::vector<Shape::IParticle*> particles;

};
	}
}