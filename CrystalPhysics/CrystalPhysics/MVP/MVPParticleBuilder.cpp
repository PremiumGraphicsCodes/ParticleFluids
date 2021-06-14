#include "MVPParticleBuilder.h"

#include "../../../Crystal/Math/Gaussian3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Physics;

void MVPParticleBuilder::buildTable(const int unum, const int vnum, const int wnum)
{
	Gaussian3d gaussian(0.5);

	cells.resize(unum);
	for (int u = 0; u < unum; ++u) {
		cells[u].resize(vnum);
		for (int v = 0; v < vnum; ++v) {
			cells[wnum].resize(wnum);
			for (int w = 0; w < wnum; ++w) {
				Cell c;
				c.position.x = (u / (float)unum) - 0.5;
				c.position.y = (v / (float)vnum) - 0.5;
				c.position.z = (v / (float)wnum) - 0.5;
				c.length.x = 1.0 / (float)unum;
				c.length.y = 1.0 / (float)vnum;
				c.length.z = 1.0 / (float)wnum;
				c.value = gaussian.getValue(c.position.x, c.position.y, c.position.z);
				cells[u][v][w] = c;
			}
		}
	}
}

/*
float MVPParticleBuilder::calculateWeight(const float a, const float r)
{
	return 1.0 / (2.0 * a) * (2.0 * r * exp(-a * r * r) - r * r * exp(a * r * r));
}
*/

float MVPParticleBuilder::calculateWeight(const float r, const float dr)
{
	Gaussian3d gaussian(0.5);
	float v = 0.0;
	for (auto rr = 0.0; rr < r; rr += dr) {
		v += gaussian.getValue(rr); //* 4.0 / 3.0 * PI * rr * rr * rr;
	}
	return v;
}