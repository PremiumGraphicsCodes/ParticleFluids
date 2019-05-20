#define _CRT_SECURE_NO_DEPRECATE
#include "MTLFileReader.h"

#include "Helper.h"

#include <vector>

#include <cassert>

#include <string>

#include "../Graphics/ColorRGBA.h"
#include "../Graphics/Material.h"


using namespace Crystal::Graphics;
using namespace Crystal::IO;

MTL::MTL()
{
	ambient = Graphics::ColorRGBAf(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = Graphics::ColorRGBAf(0.0f, 0.0f, 0.0f, 0.0f);
	specular = Graphics::ColorRGBAf(0.0f, 0.0f, 0.0f, 0.0f);
	float specularExponent = 0.0f;
	float transparent = 0.0f;
	float opticalDensity = 0.0f;

	illumination = Illumination::COLOR_ON_AND_AMBIENT_OFF;
}

bool MTL::write(std::ostream& stream) const
{
	stream << "newmtl " << name << std::endl;

	const ColorRGBAf& ambient = this->ambient;
	char s[256];
	sprintf(s, "Ka %.4lf %.4lf %.4lf", ambient.r, ambient.g, ambient.b);
	stream << s << std::endl;

	sprintf(s, "Kd %.4lf %.4lf %.4lf", diffuse.r, diffuse.g, diffuse.b);
	stream << s << std::endl;

	sprintf(s, "Ks %.4lf %.4lf %.4lf", specular.r, specular.g, specular.b);
	stream << s << std::endl;

	sprintf(s, "Ns %.4lf", specularExponent);
	stream << s << std::endl;

	sprintf(s, "Tr %.4lf", transparent);
	stream << s << std::endl;

	return true;
}

bool MTLFileReader::read(const std::string& filename)
{
	std::ifstream stream;
	stream.open(filename.c_str());

	if (!stream.is_open()) {
		return false;
	}

	return read(stream);
}

bool MTLFileReader::read(std::istream& stream)
{
	std::string str;
	
	std::string comment;

	std::string header= Helper::read< std::string >(stream);

	while( !stream.eof() ) {
		if( header.front() == '#' ) {
			//std::getline( stream, header );
		}
		else if( header == "newmtl" ) {
			MTL mtl;
			mtl.name = Helper::read<std::string>(stream);
			this->mtl.materials.push_back( mtl );
			std::getline(stream, header);
		}
		else if (header == "Ka") {
			this->mtl.materials.back().ambient = Helper::readColorRGB(stream);
		}
		else if (header == "Kd") {
			this->mtl.materials.back().diffuse = Helper::readColorRGB(stream);
		}
		else if (header == "Ks") {
			this->mtl.materials.back().specular = Helper::readColorRGB(stream);
		}
		else if (header == "Ns") {
			this->mtl.materials.back().specularExponent = Helper::read< float >(stream);
		}
		else if (header == "d" || header == "Tr") {
			this->mtl.materials.back().transparent = Helper::read<float>(stream);
		}
		else if (header == "map_Ka") {
			this->mtl.materials.back().ambientTexture = Helper::read< std::string >(stream);
		}
		else if (header == "map_Kd") {
			std::string str = Helper::read< std::string >(stream);
			this->mtl.materials.back().diffuseTexture = str;
		}
		else if (header == "map_Ks") {
			this->mtl.materials.back().shininessTexture = Helper::read< std::string >(stream);
		}
		else if (header == "map_Ns") {
			const std::string& filename = Helper::read< std::string >(stream);
		}
		else if (header == "map_d") {
			const std::string& filename = Helper::read< std::string >(stream);
		}
		else if (header == "map_bump" || header == "bump") {
			this->mtl.materials.back().bumpTexture = Helper::read< std::string >(stream);
		}
		else if (header == "illum") {
			this->mtl.materials.back().illumination = MTL::Illumination(Helper::read< int >(stream));
		}
		else if (header == "Ni") {
			this->mtl.materials.back().opticalDensity = Helper::read<float>(stream);
		}
		stream >> header;
	}
	return true;
}
