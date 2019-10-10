#pragma once

#include "IWindow.h"
#include <string>
#include <vector>

#include "tinyfiledialogs.h"

namespace Crystal {
	namespace UI {

class FileSaveView : public IWindow
{
public:
	explicit FileSaveView(const std::string& name) :
		IWindow(name)
	{}

	void addFilter(char const* filter) { filters.push_back(filter); }

	void onShow() override
	{
		filename = tinyfd_saveFileDialog("Save", "", filters.size(), filters.data(), nullptr);
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