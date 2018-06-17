#include "GraphicObject_Terrain.h"
#include <assert.h>

GraphicObject_Terrain::GraphicObject_Terrain(ShaderTexture* texture, TerrainModel* mod)
{
	pTerrain = mod;
	pShaderTexture = texture;
	pTexture = nullptr;
	World = Matrix(IDENTITY);
}

GraphicObject_Terrain::~GraphicObject_Terrain()
{

}

void GraphicObject_Terrain::SetTexture(Texture* tex)
{
	pTexture = tex;
}

void GraphicObject_Terrain::SetWorld(const Matrix& world)
{
	World = world;
}

void GraphicObject_Terrain::Render()
{
	pShaderTexture->SetTextureResourceAndSampler(pTexture);
	pShaderTexture->SendWorld(World);
	pTerrain->Render(pShaderTexture->GetContext());
}