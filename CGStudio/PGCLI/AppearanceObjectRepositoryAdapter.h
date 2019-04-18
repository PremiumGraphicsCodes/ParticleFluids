#pragma once

using namespace System;

namespace Crystal {
	namespace Model {
		class AppearanceObjectRepository;
	}
}

namespace PG {
	namespace CLI {

public ref class AppearanceObjectRepositoryAdapter
{
public:
	AppearanceObjectRepositoryAdapter();

	~AppearanceObjectRepositoryAdapter();

internal:
	AppearanceObjectRepositoryAdapter(Crystal::Model::AppearanceObjectRepository* instance);

	Crystal::Model::AppearanceObjectRepository* instance;
};

	}
}