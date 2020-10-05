#pragma once

#include <memory>

namespace Crystal {
	namespace OpenVDB {
		class VolumeImpl;

class Volume
{
public:
	Volume();

	~Volume() {}

private:
	std::unique_ptr<VolumeImpl> impl;
};
	}
}