#pragma once

#include <memory>

#include "../../Crystal/Util/UnCopyable.h"

namespace Crystal {
	namespace OpenVDB {
		class VolumeImpl;

class Volume : private UnCopyable
{
public:
	Volume();

	//explicit Volume(std::unique_ptr<VolumeImpl> impl);

	~Volume();

	VolumeImpl* getImpl() { return impl; }

private:
	VolumeImpl* impl;
};
	}
}