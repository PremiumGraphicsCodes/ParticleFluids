#include "stdafx.h"
#include "TextureObjectRepositoryAdapter.h"
#include "../../Crystal/Model/TextureObjectRepository.h"
#include "Converter.h"

using namespace PG::CLI;

TextureObjectRepositoryAdapter::TextureObjectRepositoryAdapter()
{
	this->instance = new Crystal::Model::TextureObjectRepository();
}

TextureObjectRepositoryAdapter::~TextureObjectRepositoryAdapter()
{
	delete instance;
}

int TextureObjectRepositoryAdapter::Add(PG::Core::Graphics::Texture^ texture)
{
	return -1;
	//	instance->add( Converter::toCpp((light), "" );
}

TextureObjectRepositoryAdapter::TextureObjectRepositoryAdapter(Crystal::Model::TextureObjectRepository* instance)
{
	this->instance = instance;
}
