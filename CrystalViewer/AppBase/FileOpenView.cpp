#pragma once

#include "FileOpenView.h"

#include "tinyfiledialogs.h"

using namespace Crystal::UI;

FileOpenView::FileOpenView(const std::string& name) :
	IWindow(name),
	filename(nullptr)
{}

void FileOpenView::addFilter(char const* filter)
{
	filters.push_back(filter);
}

void FileOpenView::onShow()
{
	//char const * lFilterPatterns[2] = { "*.stl", "*.obj" };
	const auto filerCount = static_cast<int>(filters.size());
	filename = tinyfd_openFileDialog("Open", "", filerCount, filters.data(), nullptr, 0);
}

std::string FileOpenView::getFileName() const
{
	if (filename == nullptr) {
		return "";
	}
	return filename;
}
