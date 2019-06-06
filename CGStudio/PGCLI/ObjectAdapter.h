#pragma once

using namespace System;

namespace Crystal {
	namespace Model {
		class IObject;
	}
}

namespace PG {
	namespace CLI {

public ref class ObjectAdapter
{
public:
	~ObjectAdapter(void);

	int GetId();

	System::String^ GetName();

	bool GetVisible();

	void SetVisible(bool visible);

internal:
	ObjectAdapter(Crystal::Model::IObject* instance);

	Crystal::Model::IObject* instance;
};

	}
}