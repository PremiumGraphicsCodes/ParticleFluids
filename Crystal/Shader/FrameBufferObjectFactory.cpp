#include "FrameBufferObjectFactory.h"

using namespace Crystal::Shader;

void FrameBufferObjectFactory::clear()
{
	/*
	for (auto& b : buffers) {
		b->clear();
	}
	*/
	buffers.clear();
}


FrameBufferObject* FrameBufferObjectFactory::create(const int width, const int height)
{
	buffers.push_back(std::make_unique<FrameBufferObject>());
	buffers.back()->build(width, height);
	return buffers.back().get();
}
