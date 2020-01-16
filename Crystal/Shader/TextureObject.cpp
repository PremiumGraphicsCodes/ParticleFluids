#include "TextureObject.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

/*
TextureObject TextureObjectFactory::createTextureObject(const Image& image)
{
	TextureObject object;
	object.create(image, nextId++);
	return object;
}

TextureObject TextureObjectFactory::createTextureObject(const Imagef& image)
{
	TextureObject object;
	object.create(image, nextId++);
	return object;
}
*/

void TextureObject::create(const Image& image, const int id)
{
	this->id = id;
	this->width = image.getWidth();
	this->height = image.getHeight();

	glActiveTexture(GL_TEXTURE0 + id);
	glGenTextures(1, &texHandle);
	send(image);
}

void TextureObject::clear()
{
	glDeleteTextures(1, &texHandle);
}

void TextureObject::bind() const
{
	glActiveTexture(GL_TEXTURE0 + id);
	glBindTexture(GL_TEXTURE_2D, texHandle);
}

void TextureObject::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
}

void TextureObject::create(const Imagef& image, const int id)
{
	this->id = id;
	this->width = image.getWidth();
	this->height = image.getHeight();

	glActiveTexture(GL_TEXTURE0 + id);
	glGenTextures(1, &texHandle);
	send(image);
}

void TextureObject::send(const Image& image)
{
	glBindTexture(GL_TEXTURE_2D, texHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getValues().data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);


	glBindTexture(GL_TEXTURE_2D, 0);
	assert(GL_NO_ERROR == glGetError());

}


void TextureObject::send(const Imagef& image)
{
	glBindTexture(GL_TEXTURE_2D, texHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_FLOAT, image.getValues().data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glBindTexture(GL_TEXTURE_2D, 0);
	assert(GL_NO_ERROR == glGetError());
}