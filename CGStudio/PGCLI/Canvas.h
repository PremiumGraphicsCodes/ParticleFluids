namespace Crystal {
	namespace UI {
		class Canvas;
	}
}

namespace PG {
	namespace CLI {
		ref class RepositoryAdapter;

public ref class Canvas
{
public:
	void render(const int width, const int height);

	void onLeftButtonDown(double x, double y);

	void onLeftButtonUp(double x, double y);

	void onRightButtonDown(double x, double y);

	void onRightButtonUp(double x, double y);

	void onMiddleButtonDown(double x, double y);

	void onMiddleButtonUp(double x, double y);

	void onLeftDragging(double x, double y);

	void onRightDragging(double x, double y);

	void onMiddleDragging(double x, double y);

	void onWheel(const float scale);

internal:
	Crystal::UI::Canvas* instance;
};

	}
}