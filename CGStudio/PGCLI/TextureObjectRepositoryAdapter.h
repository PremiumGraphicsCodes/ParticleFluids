#pragma once

using namespace System;

namespace Crystal {
	namespace Model {
		class TextureObjectRepository;
	}
}

namespace PG {
	namespace CLI {

public ref class TextureObjectRepositoryAdapter
{
public:
	TextureObjectRepositoryAdapter();

	~TextureObjectRepositoryAdapter();

	int Add(PG::Core::Graphics::Texture^ texture);

internal:
	TextureObjectRepositoryAdapter(Crystal::Model::TextureObjectRepository* instance);

	Crystal::Model::TextureObjectRepository* instance;
};

	}
}