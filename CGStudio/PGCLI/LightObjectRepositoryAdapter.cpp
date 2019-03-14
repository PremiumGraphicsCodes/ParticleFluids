#include "stdafx.h"
#include "LightObjectRepositoryAdapter.h"
#include "../../Crystal/UI/LightObjectRepository.h"

using namespace PG::CLI;

LightObjectRepositoryAdapter::~LightObjectRepositoryAdapter()
{}

void LightObjectRepositoryAdapter::Add(PG::Core::Graphics::PointLight^ light)
{

}

LightObjectRepositoryAdapter::LightObjectRepositoryAdapter(Crystal::UI::LightObjectRepository* instance)
{
	this->instance = instance;
}
