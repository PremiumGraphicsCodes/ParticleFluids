#include "MVPParticleBuilder.h"

#include "../../../Crystal/Math/Gaussian3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Physics;

void MVPParticleBuilder::buildTable(const int unum, const int vnum, const int wnum)
{
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
				c.value = 0.0f;
				cells[u][v][w] = c;
			}
		}
	}
}