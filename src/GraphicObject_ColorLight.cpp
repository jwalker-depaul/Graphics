#include "GraphicObject_ColorLight.h"
#include "Model.h"
#include "ShaderColorLight.h"
#include <assert.h>

GraphicObject_ColorLight::GraphicObject_ColorLight(ShaderColorLight* shaderLight, Model* mod)
{
	SetModel(mod);
	pShaderLight = shaderLight;

	ambient = Vect(1, 1, 1);
	diffuse = Vect(1, 1, 1);
	specular = Vect(1, 1, 1);
	World = Matrix(IDENTITY);
}

GraphicObject_ColorLight::~GraphicObject_ColorLight()
{

}

void GraphicObject_ColorLight::SetMaterial(const Vect& a, const Vect& d, const Vect& s)
{
	ambient = a;
	diffuse = d;
	specular = s;
}

void GraphicObject_ColorLight::SetWorld(const Matrix& world)
{
	World = world;
}

void GraphicObject_ColorLight::Render()
{
	pShaderLight->SendWorldAndMaterial(World, ambient, diffuse, specular);
	pModel->Render(pShaderLight->GetContext());
}