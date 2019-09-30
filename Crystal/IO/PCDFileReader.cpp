#include "PCDFileReader.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>

using namespace Crystal::Math;
using namespace Crystal::IO;

namespace {
	std::vector<std::string> split(const std::string& input, char delimiter)
	{
		std::istringstream stream(input);

		std::string field;
		std::vector<std::string> result;
		while (std::getline(stream, field, delimiter)) {
			result.push_back(field);
		}
		return result;
	}
}

bool PCDFileReader::read(const std::filesystem::path& filename)
{
	std::ifstream stream(filename);
	if (!stream.is_open()) {
		return false;
	}
	return read(stream);
}

bool PCDFileReader::read(std::istream& stream)
{
	this->pcd.header = readHeader(stream);
	this->pcd.data = readData(stream);
	return true;
}

PCDFile::Header PCDFileReader::readHeader(std::istream& stream)
{
	PCDFile::Header header;
	std::string str;
	while (std::getline(stream, str)) {
		if (str.empty()) {
			continue;
		}
		if (str[0] == '#') {
			continue;
		}
		const auto& splitted = ::split(str, ' ');
		assert(splitted.size() >= 2);
		if (splitted[0] == "VERSION") {
			//this->version = splitted[1];
			continue;
		}
		else if (splitted[0] == "FIELDS") {
			continue;
		}
		else if (splitted[0] == "DATA") {
			return header;
		}
	}

	return header;
}

PCDFile::Data PCDFileReader::readData(std::istream& stream)
{
	PCDFile::Data data;

	std::string str;
	while (std::getline(stream, str)) {
		const auto& splitted = ::split(str, ' ');
		assert(splitted.size() >= 3);
		const auto x = std::stod(splitted[0]);
		const auto y = std::stod(splitted[1]);
		const auto z = std::stod(splitted[2]);
		data.positions.push_back(Vector3dd(x, y, z));
	}

	return data;
}

