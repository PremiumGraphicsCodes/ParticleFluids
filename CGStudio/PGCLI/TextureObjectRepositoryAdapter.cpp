#include "stdafx.h"
#include "TextureObjectRepositoryAdapter.h"
#include "../../Crystal/UI/TextureObjectRepository.h"
#include "Converter.h"

using namespace PG::CLI;

TextureObjectRepositoryAdapter::TextureObjectRepositoryAdapter()
{
	this->instance = new Crystal::UI::TextureObjectRepository();
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

TextureObjectRepositoryAdapter::TextureObjectRepositoryAdapter(Crystal::UI::TextureObjectRepository* instance)
{
	this->instance = instance;
}
