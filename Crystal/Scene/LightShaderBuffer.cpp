#include "LightShaderBuffer.h"

//using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

bool LightShaderBuffer::build()
{
	return true;
}

void LightShaderBuffer::send()
{

}

void LightShaderBuffer::add(const PointLight& light)
{
	lights.push_back(light);
}
