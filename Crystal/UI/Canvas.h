#ifndef __CRYSTAL_UI_I_CANVAS_H__
#define __CRYSTAL_UI_I_CANVAS_H__

#include "../Math/Vector2d.h"
#include "../Math/Box3d.h"
#include "../Graphics/ICamera.h"
#include <memory>
#include <list>

#include "IUICtrl.h"
#include "ObjectViewModel.h"
#include "AppearanceViewModel.h"
#include "ObjectRenderer.h"
#include "Renderer.h"

namespace Crystal {
	namespace UI {
		class IUICtrl;
		class Repository;
		class ObjectRenderer;

class Canvas : public IMouseListener
{
public:
	Canvas();

	explicit Canvas(Graphics::ICamera* camera);

	virtual ~Canvas() {}

	void build();

	void setUICtrl(IUICtrl* ctrl) { this->ctrl.reset(ctrl); }

	void setViewModel(ViewModel viewModel) {
		this->renderer->setViewModel(viewModel);
	}

	void render(const int width, const int height, const TextureObjectRepository& textures);

	virtual void onLeftButtonDown(const Math::Vector2df& position) override;

	virtual void onLeftButtonUp(const Math::Vector2df& position) override;

	virtual void onRightButtonDown(const Math::Vector2df& position) override;

	virtual void onRightButtonUp(const Math::Vector2df& position) override;

	virtual void onMiddleButtonDown(const Math::Vector2df& position) override;

	virtual void onMiddleButtonUp(const Math::Vector2df& position) override;

	virtual void onLeftDragging(const Math::Vector2df& position) override;

	virtual void onRightDragging(const Math::Vector2df& position) override;

	virtual void onMiddleDragging(const Math::Vector2df& position) override;

	virtual void onWheel(const float scale) override;

	Graphics::ICamera* getCamera() { return camera.get(); }

	void fitCamera(const Math::Box3d& boundingBox);

	void setCameraXY(const Math::Box3d& boundingBox);

	void setCameraYZ(const Math::Box3d& boundingBox);

	void setCameraZX(const Math::Box3d& boundingBox);

	Graphics::Image getImage() const;

	int getWidth() const { return width; }

	int getHeight() const { return height; }

	Renderer* getRenderer() { return renderer.get(); }

private:
	int width;
	int height;
	std::unique_ptr<Graphics::ICamera> camera;
	std::unique_ptr<IUICtrl> ctrl;
	std::unique_ptr<Renderer> renderer;
};
	}
}

#endif