#include "RendererRepository.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

RendererRepository::RendererRepository() :
	pointRenderer(std::make_unique<PointRenderer>()),
	wireRenderer(std::make_unique<LineRenderer>()),
	smoothRenderer(std::make_unique<SmoothRenderer>()),
	triagleRenderer(std::make_unique<TriangleRenderer>()),
	onScreenRenderer(std::make_unique<OnScreenRenderer>())
{
}

RendererRepository::~RendererRepository()
{
}

ShaderBuildStatus RendererRepository::build(GLObjectFactory& factory)
{
	ShaderBuildStatus status;
	const auto prStatus = pointRenderer->build(factory);
	const auto wrStatus = wireRenderer->build(factory);
	const auto trStatus = triagleRenderer->build(factory);
	const auto smStatus = smoothRenderer->build(factory);
	const auto osStatus = onScreenRenderer->build(factory);

	status.add(prStatus);
	status.add(wrStatus);
	status.add(trStatus);
	status.add(smStatus);
	status.add(osStatus);
	return status;
}

void RendererRepository::release(GLObjectFactory& factory)
{
	pointRenderer->release(factory);
	wireRenderer->release(factory);
	smoothRenderer->release(factory);
	triagleRenderer->release(factory);
	onScreenRenderer->release(factory);
}
