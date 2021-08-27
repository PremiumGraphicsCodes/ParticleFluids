#include <vector>

namespace Crystal {
	namespace Util {

template<typename T>
class Array3d
{
public:
	Array3d(const size_t unum, const size_t vnum, const size_t wnum) {
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

private:
	std::vector<std::vector<std::vector<T>>> values;
};

	}
}