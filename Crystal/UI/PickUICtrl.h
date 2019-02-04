#include <memory>
#include "../Graphics/ICamera.h"
#include "Canvas.h"
#include "IUICtrl.h"
#include "IMouseListener.h"

namespace Crystal {
	namespace UI {
		class Repository;

class PickUICtrl : public IUICtrl
{
public:
	virtual ~PickUICtrl() {}

	PickUICtrl(Repository* model, Canvas* canvas);

	virtual void onLeftButtonDown(const Math::Vector2df& position) override;

	virtual void onLeftButtonUp(const Math::Vector2df& position) override;

	virtual void onLeftDragging(const Math::Vector2df& position) override;

	virtual void onRightButtonDown(const Math::Vector2df& position) override;

	virtual void onRightButtonUp(const Math::Vector2df& position) override;

	virtual void onRightDragging(const Math::Vector2df& position) override;

	virtual void onWheel(const float dx) override;

private:
	Repository* model;
	Canvas* canvas;
};
	}
}
