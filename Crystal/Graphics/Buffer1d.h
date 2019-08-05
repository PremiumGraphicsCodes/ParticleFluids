#ifndef __CRYSTAL_GRAPHICS_BUFFER_1D_H__
#define __CRYSTAL_GRAPHICS_BUFFER_1D_H__

#include "IBuffer.h"

namespace Crystal {
	namespace Graphics {

template<typename T>
class Buffer1d : public IBuffer<T>
{
public:
	Buffer1d() = default;

	Buffer1d(const std::vector<T>& buffer) :
		IBuffer(buffer)
	{}

	~Buffer1d() = default;

	void add(const T v) { buffer.push_back(v); }

	void merge(const Buffer1d<T>& rhs) {
		buffer.insert(buffer.end(), rhs.buffer.begin(), rhs.buffer.end());
	}

private:
};

	}
}

#endif