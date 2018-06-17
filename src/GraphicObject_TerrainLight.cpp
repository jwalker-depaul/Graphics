#include "GraphicObject_TerrainLight.h"
#include <assert.h>

GraphicObject_TerrainLight::GraphicObject_TerrainLight(ShaderTextureLight* texture, TerrainModel* terrainMod)
{
	pTerrain = terrainMod;
	pShaderTextureLight = texture;
	pTexture = nullptr;

	ambient = Vect(1, 1, 1);
	diffuse = Vect(1, 1, 1);
	specular = Vect(1, 1, 1);
	World = Matrix(IDENTITY);
}

GraphicObject_TerrainLight::~GraphicObject_TerrainLight()
{

}

void GraphicObject_TerrainLight::SetTexture(Texture* tex)
{
	pTexture = tex;
}

void GraphicObject_TerrainLight::SetWorld(const Matrix& world)
{
	World = world;
}

void GraphicObject_TerrainLight::SetMaterial(const Vect& a, const Vect& d, const Vect& s)
{
	ambient = a;
	diffuse = d;
	specular = s;
}

void GraphicObject_TerrainLight::Render()
{
	pShaderTextureLight->SetTextureResourceAndSampler(pTexture);
	pShaderTextureLight->SendWorldAndMaterial(World, ambient, diffuse, specular);
	pTerrain->Render(pShaderTextureLight->GetContext());
}