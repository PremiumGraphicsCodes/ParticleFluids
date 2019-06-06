#pragma once

using namespace System;

namespace Crystal {
	namespace Model {
		class MaterialObjectRepository;
	}
}

namespace PG {
	namespace CLI {
		ref class MaterialObjectAdapter;

public ref class MaterialObjectRepositoryAdapter
{
public:
	MaterialObjectRepositoryAdapter();

	~MaterialObjectRepositoryAdapter();

	int Add(PG::Core::Graphics::Material^ material, System::String^ name);

	System::Collections::Generic::List<MaterialObjectAdapter^>^ GetObjects();

internal:
	MaterialObjectRepositoryAdapter(Crystal::Model::MaterialObjectRepository* instance);

	Crystal::Model::MaterialObjectRepository* instance;
};

	}
}