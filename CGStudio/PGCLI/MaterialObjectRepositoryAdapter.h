#pragma once

using namespace System;

namespace Crystal {
	namespace Model {
		class MaterialObjectRepository;
	}
}

namespace PG {
	namespace CLI {

public ref class MaterialObjectRepositoryAdapter
{
public:
	MaterialObjectRepositoryAdapter();

	~MaterialObjectRepositoryAdapter();

	int Add(PG::Core::Graphics::Material^ material);

internal:
	MaterialObjectRepositoryAdapter(Crystal::Model::MaterialObjectRepository* instance);

	Crystal::Model::MaterialObjectRepository* instance;
};

	}
}