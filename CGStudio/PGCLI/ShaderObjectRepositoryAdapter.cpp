#include "stdafx.h"
#include "ShaderObjectRepositoryAdapter.h"
#include "../../Crystal/Shader/ShaderObjectRepository.h"
#include "ShaderObjectRepositoryAdapter.h"

using namespace PG::CLI;

ShaderObjectRepositoryAdapter::~ShaderObjectRepositoryAdapter()
{
	delete instance;
}

ShaderObjectRepositoryAdapter::ShaderObjectRepositoryAdapter(Crystal::Shader::ShaderObjectRepository* instance)
{
	this->instance = instance;
}

/*
MaterialObjectRepositoryAdapter^ AppearanceObjectRepositoryAdapter::Material()
{
	return gcnew MaterialObjectRepositoryAdapter(this->instance->getMaterials());
}
*/
