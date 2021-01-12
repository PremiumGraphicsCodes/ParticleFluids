#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Util/UnCopyable.h"

#include "../../Crystal/Scene/IShapeScene.h"
#include "VDBParticleSystemPresenter.h"

#include <memory>

namespace Crystal {
    namespace VDB {
        class VDBParticleSystemImpl;

class VDBParticleSystemScene : public Scene::IShapeScene
{
public:
    VDBParticleSystemScene() :
        VDBParticleSystemScene(-1, "")
    {}

    VDBParticleSystemScene(const int id, const std::string name);

    ~VDBParticleSystemScene();

    void add(const Math::Vector3dd& position, const double radius);

    Math::Vector3dd getPosition(const int index) const;

    float getSize(const int index) const;

 //   Crystal::Scene::ParticleSystemScene* toCrystal() const;

    VDBParticleSystemImpl* getImpl() const { return impl.get(); }

    void fromCrystal(const std::vector<Math::Vector3dd>& positions, const float radius);

    void translate(const Math::Vector3dd& v) override {};

    void transform(const Math::Matrix3dd& m) override {};

    void transform(const Math::Matrix4dd& m) override {};

    Scene::IPresenter* getPresenter() { return presenter.get(); };

    Scene::SceneType getType() const { return Scene::SceneType::None; }

    Math::Box3d getBoundingBox() const override;

private:
    std::unique_ptr<VDBParticleSystemImpl> impl;
    std::unique_ptr<VDBParticleSystemPresenter> presenter;
};

    }
}