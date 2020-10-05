#pragma once

#include <memory>

namespace Crystal {
	namespace OpenVDB {
		class VolumeImpl;

class Volume
{
public:
	Volume();

	explicit Volume(std::unique_ptr<VolumeImpl> impl) :
		impl(std::move(impl))
	{}

	~Volume() {}

	const VolumeImpl* getImpl() { return impl.get(); }

private:
	std::unique_ptr<VolumeImpl> impl;
};
	}
}