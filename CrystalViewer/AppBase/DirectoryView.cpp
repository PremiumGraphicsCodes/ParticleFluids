#pragma once

#include "DirectoryView.h"

#include "tinyfiledialogs.h"

using namespace Crystal::UI;

DirectoryView::DirectoryView(const std::string& name) :
	IView(name),
	selectButton("Select"),
	pathView("Path")
{
	selectButton.setFunction([=]() { onSelect(); });
	add(&selectButton);
	add(&pathView);
}

void DirectoryView::onSelect()
{
	auto fileName = tinyfd_selectFolderDialog("Open", "");
	if (fileName == nullptr) {
		return;
	}
	pathView.setValue(fileName);
};
