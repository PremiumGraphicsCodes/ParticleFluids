#include "SceneViewModel.h"

using namespace Crystal::Scene;

void SceneViewModel::clear()
{
	for (auto& pb : pointBuffers) {
		pb.release();
	}
	for (auto& lb : lineBuffers) {
		lb.release();
	}
	for (auto& tb : triangleBuffers) {
		tb.release();
	}
	pointBuffers.clear();
	lineBuffers.clear();
	triangleBuffers.clear();
}
