#pragma once

using namespace System;

namespace Crystal {
	namespace UI {
		class ObjectRepository;
	}
}

namespace PG {
	namespace CLI {

public ref class ObjectRepositoryAdapter
{
public:
	ObjectRepositoryAdapter();

	~ObjectRepositoryAdapter(void);

	int AddWireFrameObject();

internal:
	ObjectRepositoryAdapter(Crystal::UI::ObjectRepository* instance);

	Crystal::UI::ObjectRepository* instance;
};

	}
}