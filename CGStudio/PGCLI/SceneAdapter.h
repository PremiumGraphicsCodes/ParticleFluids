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

	int AddLightScene(PG::Core::Graphics::PointLight^ light, System::String^ name);

	int AddMaterialScene(PG::Core::Graphics::Material^ material, System::String^ name);

	void ChangeName(int id, System::String^ name);

	void UpdateLightScene(int id, PG::Core::Graphics::PointLight^ light);

	void UpdateMaterialScene(int id, PG::Core::Graphics::Material^ m);

	//System::String^ FindNameById(int id);

	PG::Core::Graphics::Material^ FindMaterialByid(int id);

	PG::Core::Graphics::PointLight^ FindLightById(int id);

	PG::Core::Math::Vector3d^ FindPositionById(int parentId, int childId);

	PG::Core::SceneType^ GetTypeById(int id);

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
