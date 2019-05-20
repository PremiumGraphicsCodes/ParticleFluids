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

MTLFile::MTLFile()
{
	ambient = Graphics::ColorRGBAf(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = Graphics::ColorRGBAf(0.0f, 0.0f, 0.0f, 0.0f);
	specular = Graphics::ColorRGBAf(0.0f, 0.0f, 0.0f, 0.0f);
	float specularExponent = 0.0f;
	float transparent = 0.0f;
	float opticalDensity = 0.0f;

	illumination = Illumination::COLOR_ON_AND_AMBIENT_OFF;
}

bool MTLFile::read(std::istream& stream)
{
	std::string header;
	this->name = Helper::read< std::string >(stream);
	stream >> header;

	while (!stream.eof()) {
		if (header.front() == '#') {
			std::getline(stream, header);
			//comment += header;
		}
		else if (header == "newmtl") {
			return true;
		}
		else if (header == "Ka") {
			this->ambient = Helper::readColorRGB(stream);
		}
		else if (header == "Kd") {
			this->diffuse = Helper::readColorRGB(stream);
		}
		else if (header == "Ks") {
			this->specular = Helper::readColorRGB(stream);
		}
		else if (header == "Ns") {
			this->specularExponent = Helper::read< float >(stream);
		}
		else if (header == "d" || header == "Tr") {
			this->transparent = Helper::read<float>(stream);
		}
		else if (header == "map_Ka") {
			this->ambientTexture = Helper::read< std::string >(stream);
		}
		else if (header == "map_Kd") {
			std::string str = Helper::read< std::string >(stream);
			/*
			if (str == "-o") {
				Helper::readVector(stream);
				str = Helper::read< std::string >(stream);
			}
			if (str == "-s") {
				Helper::readVector(stream);
				str = Helper::read< std::string >(stream);
			}
			*/
			this->diffuseTexture = str;
		}
		else if (header == "map_Ks") {
			this->shininessTexture = Helper::read< std::string >(stream);
		}
		else if (header == "map_Ns") {
			const std::string& filename = Helper::read< std::string >(stream);
		}
		else if (header == "map_d") {
			const std::string& filename = Helper::read< std::string >(stream);
		}
		else if (header == "map_bump" || header == "bump") {
			this->bumpTexture = Helper::read< std::string >(stream);
		}
		else if (header == "illum") {
			this->illumination = MTLFile::Illumination( Helper::read< int >(stream) );
		}
		else if (header == "Ni") {
			this->opticalDensity = Helper::read<float>(stream);
		}

		stream >> header;
	}
	return true;
}


bool MTLFile::write(std::ostream& stream) const
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
			std::getline( stream, header );
		}
		else if( header == "newmtl" ) {
			MTLFile mtl;
			mtl.read(stream);
			materials.push_back( mtl );
		}
		else {
			stream >> header;
		}
	}
	return true;
}
