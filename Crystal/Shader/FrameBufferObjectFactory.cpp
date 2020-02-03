#include "FrameBufferObjectFactory.h"

using namespace Crystal::Shader;

std::unique_ptr<FrameBufferObject> FrameBufferObjectFactory::create(const int width, const int height)
{
	auto buffer = std::make_unique<FrameBufferObject>();
	buffer->build(width, height);
	return std::move(buffer);
}
