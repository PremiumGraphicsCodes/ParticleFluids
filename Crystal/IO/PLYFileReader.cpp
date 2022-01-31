#include "PLYFileReader.h"

//#include "PCDFileReader.h"
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

bool PLYFileReader::readASCII(const std::filesystem::path& filename)
{
	std::ifstream stream(filename); //, std::ios::in | std::ios::binary);
	if (!stream.is_open()) {
		return false;
	}
	return readASCII(stream);
}

bool PLYFileReader::readASCII(std::istream& stream)
{
	unsigned int count = 0;
	std::string str;
	while (std::getline(stream, str)) {
		if (str.empty()) {
			continue;
		}
		const auto& splitted = ::split(str, ' ');
		//assert(splitted.size() >= 2);
		if (splitted[0] == "comment") {
			continue;
		}
		else if (splitted[0] == "element") {
			if (splitted[1] == "vertex") {
				count = std::stoi(splitted[2]);
			}
		}
		else if (splitted[0] == "end_header") {
			break;
		}
	}

	for(unsigned int i = 0; i < count; ++i) {
		std::getline(stream, str);
		const auto& splitted = ::split(str, ' ');
		assert(splitted.size() >= 3);
		const auto x = std::stod(splitted[0]);
		const auto y = std::stod(splitted[1]);
		const auto z = std::stod(splitted[2]);
		this->positions.push_back(Vector3dd(x, y, z));
	}

	return true;
}

bool PLYFileReader::readBinary(const std::filesystem::path& filename)
{
	std::ifstream stream(filename, std::ios::in | std::ios::binary);
	if (!stream.is_open()) {
		return false;
	}
	return readBinary(stream);
}

namespace {
	template<typename T>
	T read_binary_as(std::istream& is)
	{
		T val;
		is.read(reinterpret_cast<char*>(std::addressof(val)), sizeof(T));
		return val;
	}
}


bool PLYFileReader::readBinary(std::istream& stream)
{
	unsigned int count = 0;
	std::string str;
	while (std::getline(stream, str)) {
		if (str.empty()) {
			continue;
		}
		const auto& splitted = ::split(str, ' ');
		//assert(splitted.size() >= 2);
		if (splitted[0] == "comment") {
			continue;
		}
		else if (splitted[0] == "element") {
			if (splitted[1] == "vertex") {
				count = std::stoi(splitted[2]);
			}
		}
		else if (splitted[0] == "end_header") {
			break;
		}
	}

	for (unsigned int i = 0; i < count; ++i) {
		const auto x = read_binary_as<float>(stream);
		const auto y = read_binary_as<float>(stream);
		const auto z = read_binary_as<float>(stream);
		this->positions.push_back(Vector3dd(x, y, z));
	}
	return true;
}