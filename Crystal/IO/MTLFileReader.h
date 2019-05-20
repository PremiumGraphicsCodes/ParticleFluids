#ifndef __CRYSTAL_IO_MTL_FILE_READER_H__
#define __CRYSTAL_IO_MTL_FILE_READER_H__

#include <map>

#include "../Graphics/Material.h"
#include "../Graphics/ColorRGBA.h"

#include "../Math/Vector3d.h"


#include <cassert>

#include <fstream>
#include <string>

namespace Crystal {
	namespace IO {

struct MTL
{
	enum class Illumination
	{
		COLOR_ON_AND_AMBIENT_OFF = 0,
		COLOR_ON_AND_AMBIENT_ON = 1,
		HIGHLIGHT_ON = 2,
		REFRECTION_ON_AND_RAY_TRACE_ON = 3,

		REFLECTION_ON_AND_RAY_TRACE_OFF = 8,

		CAST_SHADOWS_ONTO_INVISIBLE_SURFACES = 10,
	};

	MTL();

	bool write(std::ostream& stream) const;

	/*
	void setOpticalDensity(const float d) {
		assert((0.001f <= d) && (d <= 10.0f));
		this->opticalDensity = d;
	}

	float getOpticalDensity() const { return opticalDensity; }
	*/

	//Graphics::Material toMaterial(const std::string& directory) const;

public:
	std::string name;
	Graphics::ColorRGBAf ambient;
	Graphics::ColorRGBAf diffuse;
	Graphics::ColorRGBAf specular;

	float specularExponent;
	float transparent;
	float opticalDensity;

	std::string ambientTexture;
	std::string diffuseTexture;
	std::string shininessTexture;
	std::string bumpTexture;

	Illumination illumination;
};

struct MTLFile
{
	std::vector<MTL> materials;
};

class MTLFileReader
{
public:

	bool read(const std::string& filename);

	bool read(std::istream& stream);

	MTLFile getMTL() const { return mtl; }

private:
	MTLFile mtl;
	//MTLTextureOption option;
};


	}
}

#endif