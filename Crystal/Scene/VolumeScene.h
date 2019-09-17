#pragma once

#include <vector>
#include <functional>
#include "../../Crystal/Math/Box3d.h"
#include "../../Crystal/Shape/Particle.h"
#include "../../Crystal/Util/UnCopyable.h"

namespace Crystal {
	namespace Scene {

		class Volume : private UnCopyable
		{
		public:
			Volume(const int unum, const int vnum, const int wnum, const Math::Box3d& box);

			void set(const int u, const int v, const int w, const double value);

			void add(const std::function<double(double)>& function);

			int getUNum() const { return unum; }

			int getVNum() const { return vnum; }

			int getWNum() const { return wnum; }

			Math::Vector3dd getPosition(const int i, const int j, const int k) const { return nodes[i][j][k].getPosition(); }

			double getValue(const int i, const int j, const int k) const { return nodes[i][j][k].getAttribute(); }

			Math::Box3d getBoundingBox() const { return boundingBox; }

			//std::vector<Shape::Particle<double>> toParticles() const;

		private:
			std::vector< std::vector< std::vector< Shape::Particle<double> > > > nodes;
			const int unum;
			const int vnum;
			const int wnum;
			const Math::Box3d boundingBox;
		};

	}
}