#pragma once

using namespace System;

namespace Crystal {
	namespace Model {
		class LightObjectRepository;
	}
}

namespace PG {
	namespace CLI {

public ref class LightObjectRepositoryAdapter
{
public:
	LightObjectRepositoryAdapter();

	~LightObjectRepositoryAdapter();

	int Add(PG::Core::Graphics::PointLight^ light);

internal:
	LightObjectRepositoryAdapter(Crystal::Model::LightObjectRepository* instance);

	Crystal::Model::LightObjectRepository* instance;
};

	}
}