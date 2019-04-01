#pragma once

using namespace System;

namespace Crystal {
	namespace UI {
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
	AppearanceObjectRepositoryAdapter(Crystal::UI::AppearanceObjectRepository* instance);

	Crystal::UI::AppearanceObjectRepository* instance;
};

	}
}