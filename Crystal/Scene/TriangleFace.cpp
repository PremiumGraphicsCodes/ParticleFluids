#include "TriangleFace.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;

void TriangleFace::translate(const Vector3dd& vec)
{
	for (auto& v : vertices) {
		v += vec;
	}
}
