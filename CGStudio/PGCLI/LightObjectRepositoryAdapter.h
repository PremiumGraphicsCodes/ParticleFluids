#pragma once

using namespace System;

namespace Crystal {
	namespace UI {
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
	LightObjectRepositoryAdapter(Crystal::UI::LightObjectRepository* instance);

	Crystal::UI::LightObjectRepository* instance;
};

	}
}