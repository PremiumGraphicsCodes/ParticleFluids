#pragma once

using namespace System;

namespace Crystal {
	namespace UI {
		class Repository;
		class ViewModel3d;
	}
}

namespace PG {
	namespace CLI {
		ref class ObjectRepositoryAdapter;
		ref class AppearanceObjectRepositoryAdapter;

public ref class RepositoryAdapter
{
public:
	RepositoryAdapter();

	~RepositoryAdapter(void);

	void Clear();

	bool Import(System::String^ filename);

	bool Export(System::String^ filename);

	ObjectRepositoryAdapter^ Objects() { return objects; }

	AppearanceObjectRepositoryAdapter^ Appearance() { return appearance; }


private:
	ObjectRepositoryAdapter^ objects;

	AppearanceObjectRepositoryAdapter^ appearance;

internal:
	Crystal::UI::Repository* instance;
};

	}
}
