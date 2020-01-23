#pragma once

#include "IView.h"
#include "StringView.h"
#include "FilePathView.h"
#include "../../Crystal/Shader/TextureObject.h"

namespace Crystal {
	namespace UI {

class TextureView : public IView
{
public:
	explicit TextureView(const std::string& name);

	TextureView(const std::string& name, const std::string& filePath);

	void setValue(const Shader::TextureObject& texture);

private:
	FilePathView filePathView;
	StringView nameView;
};

	}
}