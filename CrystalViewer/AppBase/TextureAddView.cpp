#include "TextureAddView.h"

#include "../Command/Command.h"
#include "../Command/Public/TextureCreateLabels.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

TextureAddView::TextureAddView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	filePathView("FilePath"),
	nameView("Name", std::string("TextureXXX"))
{
	add(&filePathView);
	add(&nameView);
}

void TextureAddView::onOk()
{
	Command::Command command(TextureCreateLabels::CommandNameLabel);
	command.setArg(TextureCreateLabels::FilePathLabel, filePathView.getFileName());
	command.setArg(TextureCreateLabels::NameLabel, nameView.getValue());
	command.execute(getWorld());
}
