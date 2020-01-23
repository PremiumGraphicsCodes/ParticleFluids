#pragma once

#include "IWindow.h"
#include <string>
#include <vector>

namespace Crystal {
	namespace UI {

class FileSaveView : public IWindow
{
public:
	explicit FileSaveView(const std::string& name);

	void addFilter(char const* filter);

	void onShow() override;

	std::string getFileName() const;

private:
	std::vector< char const* > filters;
	char const* filename;
};

	}
}