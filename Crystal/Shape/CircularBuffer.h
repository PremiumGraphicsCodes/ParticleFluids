#pragma once

namespace Crystal {
	namespace Shape {

template<typename T>
class CircularBuffer
{
public:
	CircularBuffer() {};

	explicit CircularBuffer(size_t size) :
		buffer(size),
		size(size)
	{}

	T operator[](size_t index) { return buffer[getActualIndex(index)]; }

	T& operator[](size_t index) { return &buffer[getActualIndex(index); ] }

	void set(size_t index, T value) { buffer[getActualIndex()] = value; }

	T get(size_t index) { return buffer[getActualIndex()]; }

private:
	size_t getActualIndex() const { return index % size; }

	std::vector<T> buffer;
	size_t size;
};
	}
}