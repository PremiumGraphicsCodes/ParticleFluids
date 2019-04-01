#pragma once

using namespace System;

namespace Crystal {
	namespace UI {
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
	MaterialObjectRepositoryAdapter(Crystal::UI::MaterialObjectRepository* instance);

	Crystal::UI::MaterialObjectRepository* instance;
};

	}
}