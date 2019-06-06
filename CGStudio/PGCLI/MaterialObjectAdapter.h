#pragma once

using namespace System;

namespace Crystal {
	namespace Model {
		class MaterialObject;
	}
}

namespace PG {
	namespace CLI {

public ref class MaterialObjectAdapter
{
public:
	~MaterialObjectAdapter(void);

	int GetId();

	System::String^ GetName();

	bool GetVisible();

	void SetVisible(bool visible);

internal:
	MaterialObjectAdapter(Crystal::Model::MaterialObject* instance);

	Crystal::Model::MaterialObject* instance;
};

	}
}