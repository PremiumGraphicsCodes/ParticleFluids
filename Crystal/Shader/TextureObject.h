#pragma once

#include "ITextureObject.h"

#include "../Graphics/Image.h"
#include "../Graphics/Imagef.h"
#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Shader {


class TextureObject : public ITextureObject
{
//private:
//	TextureObject() {};

public:
	/*
	TextureObject(const int id) :
		ITextureObject(id)
	{}
	*/

	void create(const Graphics::Image& image, const int id);

	void create(const Graphics::Imagef& image, const int id);

	void clear();

	void send(const Graphics::Image& image);

	void send(const Graphics::Imagef& image);

	void bind() const override;

	void unbind() const override;

	void setName(const std::string& name) { this->name = name; }

	std::string getName() const { return name; }

//	friend class TextureObjectFactory;

private:
	std::string name;
};

	}
}
