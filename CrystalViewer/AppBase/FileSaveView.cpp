#include "FileSaveView.h"

#include "tinyfiledialogs.h"

using namespace Crystal::UI;

FileSaveView::FileSaveView(const std::string& name) :
	IWindow(name),
	filename(nullptr)
{}

void FileSaveView::addFilter(char const* filter)
{
	filters.push_back(filter);
}

void FileSaveView::onShow()
{
	filename = tinyfd_saveFileDialog("Save", "", filters.size(), filters.data(), nullptr);
}

std::string FileSaveView::getFileName() const
{
	if (filename == nullptr) {
		return "";
	}
	return filename;
}
