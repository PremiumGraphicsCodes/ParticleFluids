#include "RendererRepository.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

RendererRepository::RendererRepository() :
	pointRenderer(new PointRenderer()),
	wireRenderer(new LineRenderer()),
	smoothRenderer(new SmoothRenderer()),
	triagleRenderer(new TriangleRenderer())
{}

RendererRepository::~RendererRepository()
{
	delete pointRenderer;
	delete wireRenderer;
	delete smoothRenderer;
	delete triagleRenderer;
}

ShaderBuildStatus RendererRepository::build(GLObjectFactory& factory)
{
	ShaderBuildStatus status;
	const auto prStatus = pointRenderer->build(factory);
	const auto wrStatus = wireRenderer->build(factory);
	const auto trStatus = triagleRenderer->build(factory);
	const auto smStatus = smoothRenderer->build(factory);

	status.add(prStatus);
	status.add(wrStatus);
	status.add(trStatus);
	status.add(smStatus);
	return status;
}

void RendererRepository::release(GLObjectFactory& factory)
{
	pointRenderer->release(factory);
	wireRenderer->release(factory);
	//smoothRenderer->release(factory);
	triagleRenderer->release(factory);
}
