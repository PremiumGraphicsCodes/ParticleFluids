#pragma once

namespace Crystal {
	namespace Scene {

		class WireFrameEdge
		{
		public:
			WireFrameEdge() {}

			WireFrameEdge(const int originId, const int destId) :
				originId(originId),
				destId(destId)
			{}

			int originId;
			int destId;
		};

	}
}