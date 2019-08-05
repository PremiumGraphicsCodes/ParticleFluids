#ifndef __CRYSTAL_GRAPHICS_BUFFER_3D_H__
#define __CRYSTAL_GRAPHICS_BUFFER_3D_H__

#include "IBuffer.h"

//#include "../Math/Vector2d.h"
#include "../Math/Vector3d.h"
#include "../Math/glm.h"

namespace Crystal {
	namespace Graphics {

template<typename T>
class Buffer3d : public IBuffer<T> {
public:
	Buffer3d() = default;

	Buffer3d(const std::vector<T>& buffer) :
		IBuffer(buffer)
	{}

	~Buffer3d() = default;

	void add(const glm::vec3& v) {
		buffer.push_back(v[0]);
		buffer.push_back(v[1]);
		buffer.push_back(v[2]);
	}

	void merge(const Buffer3d<T>& rhs) {
		buffer.insert(buffer.end(), rhs.buffer.begin(), rhs.buffer.end());
	}

	bool operator==(const Buffer3d<T>& rhs) { return buffer == rhs.buffer; }


private:
};

	}
}

#endif