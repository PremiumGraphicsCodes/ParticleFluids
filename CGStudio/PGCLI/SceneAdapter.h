#pragma once

using namespace System;

namespace Crystal {
	namespace Scene {
		class IScene;
		class Scene;
		class SceneFactory;
	}
}

namespace PG {
	namespace CLI {

public ref class SceneAdapter
{
public:
	~SceneAdapter(void);

	void Clear();

	bool Import(System::String^ filename);

	bool Export(System::String^ filename);

	int AddParticleSystemScene(System::Collections::Generic::List<PG::Core::Math::Vector3d^>^ positions, System::String^ name);

	int AddWireFrameScene(System::Collections::Generic::List<PG::Core::Math::Line3d^>^ lines, System::String^ name);

	int AddPolygonMeshScene(System::Collections::Generic::List<PG::Core::Math::Line3d^>^ positions);

	PG::Core::Graphics::PointLight^ FindLightById(int id);

	PG::Core::Scene^ ToScene();

internal:
	PG::Core::Scene^ ToScene(Crystal::Scene::IScene* parent);

	SceneAdapter(Crystal::Scene::Scene* instance, Crystal::Scene::SceneFactory*factory);

internal:
	Crystal::Scene::Scene* instance;
	Crystal::Scene::SceneFactory* factory;
};

	}
}
