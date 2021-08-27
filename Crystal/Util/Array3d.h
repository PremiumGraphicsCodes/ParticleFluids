#pragma once

#include <vector>

namespace Crystal {
	namespace Util {

template<typename T>
class Array3d
{
public:
	explicit Array3d(const std::array<size_t, 3>& resolutions) :
		Array3d(resolutions[0], resolutions[1], resolutions[2])
	{
	}

	Array3d(const size_t unum, const size_t vnum, const size_t wnum)
	{
		resolutions[0] = unum;
		resolutions[1] = vnum;
		resolutions[2] = wnum;

		values.resize(unum);
		for (int i = 0; i < unum; ++i) {
			values[i].resize(vnum);
			for (int j = 0; j < vnum; ++j) {
				values[i][j].resize(wnum);
			}
		}
	}

	void set(int i, int j, int k, T value) {
		values[i][j][k] = value;
	}

	T get(int i, int j, int k) const {
		return values[i][j][k];
	}

	const std::array<size_t, 3>& getResolutions() const { return resolutions; }

private:
	std::vector<std::vector<std::vector<T>>> values;
	std::array<size_t, 3> resolutions;
};

	}
}