#include "GraphicObject_Texture.h"
#include "Model.h"
#include "ShaderTexture.h"
#include <assert.h>

GraphicObject_Texture::GraphicObject_Texture(ShaderTexture* texture, Model* mod)
{
	SetModel(mod);
	pShaderTexture = texture;
	pTexture = nullptr;
	World = Matrix(IDENTITY);
}

GraphicObject_Texture::~GraphicObject_Texture()
{

}

void GraphicObject_Texture::SetTexture(Texture* tex)
{
	pTexture = tex;
}

void GraphicObject_Texture::SetWorld(const Matrix& world)
{
	World = world;
}

void GraphicObject_Texture::Render()
{
	pShaderTexture->SetTextureResourceAndSampler(pTexture);
	pShaderTexture->SendWorld(World);
	pModel->Render(pShaderTexture->GetContext());
}