#ifndef __CRYSTAL_UI_I_CANVAS_H__
#define __CRYSTAL_UI_I_CANVAS_H__

#include "../Math/Vector2d.h"
#include "../Math/Box3d.h"
#include "../Graphics/ICamera.h"
#include <memory>
#include <list>

#include "IUICtrl.h"
#include "../Scene/Renderer.h"

namespace Crystal {
	namespace Scene {
		class ViewModel;
		class World;
	}
	namespace UI {
		class IUICtrl;
		class SceneRenderer;

class Canvas : public IMouseListener
{
public:
	Canvas();

	//explicit Canvas(Graphics::ICamera* camera);

	virtual ~Canvas() {}

	void build();

	void setUICtrl(IUICtrl* ctrl) { this->ctrl.reset(ctrl); }

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

	Graphics::Image getImage() const;

	int getWidth() const { return width; }

	int getHeight() const { return height; }

private:
	int width;
	int height;
	std::unique_ptr<IUICtrl> ctrl;
};
	}
}

#endif