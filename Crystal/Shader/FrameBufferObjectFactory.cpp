#include "FrameBufferObjectFactory.h"

using namespace Crystal::Shader;

FrameBufferObject* FrameBufferObjectFactory::create(const int width, const int height)
{
	auto buffer = std::make_unique<FrameBufferObject>();
	buffer->build(width, height);
	buffers.push_back(std::move(buffer));
	return buffers.back().get();
}
