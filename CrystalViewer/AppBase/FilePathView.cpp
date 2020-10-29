#include "FilePathView.h"

#include "tinyfiledialogs.h"

using namespace Crystal::UI;

FilePathView::FilePathView(const std::string& name) :
	IView(name),
	selectButton("Select"),
	fileNameView("FileName")
{
	selectButton.setFunction([=]() { onSelect(); });
	add(&selectButton);
	add(&fileNameView);
}

void FilePathView::addFilter(const char* filter)
{
	filters.push_back(filter);
}

void FilePathView::onSelect()
{
	const auto filterCount = static_cast<int>(filters.size());
	auto fileName = tinyfd_openFileDialog("Open", "", filterCount, filters.data(), nullptr, 0);
	if (fileName == nullptr) {
		return;
	}
	fileNameView.setValue( fileName );
};

