#include "AppearancePanel.h"
#include "imgui.h"
#include "../UI/Repository.h"
#include "../UI/Canvas.h"
#include "../Shape/WireFrameBuilder.h"
#include "IntView.h"
#include "FloatView.h"
#include "Float4View.h"
#include "StringView.h"
#include "Vector3dView.h"
#include "IPopupButton.h"

#include "MaterialAddButton.h"
#include "LightAddButton.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;


AppearancePanel::AppearancePanel(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas)
{
	add( new LightAddButton(model, canvas) );
	add( new MaterialAddButton(model, canvas) );
}
