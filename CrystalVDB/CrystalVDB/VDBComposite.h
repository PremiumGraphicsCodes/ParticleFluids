#pragma once

namespace Crystal {
	namespace VDB {
		class VDBVolumeScene;

class VDBComposite
{
public:
	/*
	enum class Operator {
		CSG_UNION,
		CSG_INTERSECTION,
		CSG_DIFFEFENCE
	};
	*/

	void csgUnion(const VDBVolumeScene* lhs, const VDBVolumeScene* rhs);

	void csgIntersection(const VDBVolumeScene* lhs, const VDBVolumeScene* rhs);

	void csgDifference(const VDBVolumeScene* lhs, const VDBVolumeScene* rhs);
};

	}
}