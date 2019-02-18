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
	Crystal::UI::AppearanceObjectRepository* instance;
};

	}
}