#pragma once

#include "VDBVolumeScene.h"

namespace Crystal {
	namespace VDB {

class VDBFilter
{
public:
	void setSource(VDBVolumeScene* src) { this->src = src; }

	void median(int width, int iteration);

	//std::unique_ptr<VDBVolumeScene> getFiltered() { return std::move(filtered); }

private:
	VDBVolumeScene* src = nullptr;
	//std::unique_ptr<VDBVolumeScene> filtered;
};

	}
}