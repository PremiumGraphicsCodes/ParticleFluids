#include "IShaderScene.h"
#include "../Graphics/Material.h"

namespace Crystal {
	namespace Shader {
		class SmoothRenderer;
	}
	namespace Scene {

class MaterialBuffer
{
public:
	void add(const Graphics::Material& material) { this->materials.push_back(material); }

	std::vector<Graphics::Material> getMaterials() const { return materials; }

private:
	std::vector<Graphics::Material> materials;
};

	}
}