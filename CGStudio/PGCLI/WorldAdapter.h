#pragma once

using namespace System;

namespace Crystal {
	namespace Scene {
		class World;
	}
}

namespace PG {
	namespace CLI {

public ref class WorldAdapter
{
public:
	WorldAdapter();

	~WorldAdapter(void);

	void Clear();

	void Init();

internal:
	Crystal::Scene::World* instance;
};

	}
}
