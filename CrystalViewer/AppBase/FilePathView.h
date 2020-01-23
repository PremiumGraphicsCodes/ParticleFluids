#pragma once

#include "IView.h"
#include "Button.h"
#include "StringView.h"

namespace Crystal {
	namespace UI {

class FilePathView : public IView
{
public:
	explicit FilePathView(const std::string& name);

	void addFilter(const char* filter);

protected:
	void onSelect();

private:
	Button selectButton;
	StringView fileNameView;
	std::vector< char const* > filters;
};

	}
}