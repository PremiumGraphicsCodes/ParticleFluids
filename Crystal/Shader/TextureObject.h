#ifndef __CRYSTAL_SHADER_TEXTURE_H__
#define __CRYSTAL_SHADER_TEXTURE_H__

#include "../Graphics/Image.h"
#include "../Graphics/Imagef.h"
#include "ITextureObject.h"
#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Shader {

		/*
class TextureObject;

class TextureObjectFactory : private UnCopyable
{
public:
	TextureObjectFactory() :
		nextId(0)
	{}

	TextureObject createTextureObject(const Graphics::Image& image);

	TextureObject createTextureObject(const Graphics::Imagef& image);

private:
	int nextId;
};
*/

class TextureObject : public ITextureObject
{
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

private:
	std::string name;
};


	}
}

#endif