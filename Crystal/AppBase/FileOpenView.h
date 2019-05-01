#pragma once

#include "IWindow.h"
#include <string>
#include <vector>

#include "tinyfiledialogs.h"

namespace Crystal {
	namespace UI {

class FileOpenView : public IWindow
{
public:
	explicit FileOpenView(const std::string& name) :
		IWindow(name)
	{}

	void addFilter(char const* filter) { filters.push_back(filter); }

	void show() override
	{
		//char const * lFilterPatterns[2] = { "*.stl", "*.obj" };
		filename = tinyfd_openFileDialog("Open", "", filters.size(), filters.data(), nullptr, 0);
	}

	std::string getFileName() const {
		if (filename == nullptr) {
			return "";
		}
		return filename;
	}

private:
	std::vector< char const* > filters;
	char const* filename;
};

	}
}