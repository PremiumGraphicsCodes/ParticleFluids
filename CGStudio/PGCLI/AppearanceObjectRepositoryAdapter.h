#pragma once

using namespace System;

namespace Crystal {
	namespace Model {
		class AppearanceObjectRepository;
	}
}

namespace PG {
	namespace CLI {
		ref class MaterialObjectRepositoryAdapter;

public ref class AppearanceObjectRepositoryAdapter
{
public:
	~AppearanceObjectRepositoryAdapter();

	MaterialObjectRepositoryAdapter^ Material();

internal:
	AppearanceObjectRepositoryAdapter(Crystal::Model::AppearanceObjectRepository* instance);

	Crystal::Model::AppearanceObjectRepository* instance;
};

	}
}