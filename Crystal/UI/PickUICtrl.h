#include <memory>
#include "../Graphics/ICamera.h"
#include "IUICtrl.h"
#include "IMouseListener.h"

namespace Crystal {
	namespace UI {
		class Model;

class PickUICtrl : public IUICtrl
{
public:
	virtual ~PickUICtrl() {}

	PickUICtrl(Model* model, Graphics::ICamera* camera);

	virtual void onLeftButtonDown(const Math::Vector2df& position) override;

	virtual void onLeftButtonUp(const Math::Vector2df& position) override;

	virtual void onLeftDragging(const Math::Vector2df& position) override;

	virtual void onRightButtonDown(const Math::Vector2df& position) override;

	virtual void onRightButtonUp(const Math::Vector2df& position) override;

	virtual void onRightDragging(const Math::Vector2df& position) override;

	virtual void onWheel(const float dx) override;

private:
	Math::Vector2df prevPosition;
	Model* model;
	Graphics::ICamera* camera;
};
	}
}
