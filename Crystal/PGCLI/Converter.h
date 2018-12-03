#pragma once

using namespace System;

namespace Crystal {
	namespace UI {
		class IModel;
	}
}

namespace PG {
	namespace CLI {

class Convereter
{
public:
	static Crystal::Math::Vector3df toCpp(PG::Core::Math::Vector3d^ src);

	static PG::Core::Math::Vector3d^ fromCpp(const Crystal::Math::Vector3df& src);
};

	}
}
