#include "GraphicObject_SkyBox.h"
#include "Model.h"
#include "ShaderTexture.h"
#include "Texture.h"

GraphicObject_SkyBox::GraphicObject_SkyBox(ShaderTexture* shader, ID3D11Device* dev, float scale, Texture* tex)
{
	pSkyB = new Model(dev, Model::PreMadedeModels::UnitSkyBox, scale);
	pShader = shader;
	pTexture = tex;
	World = Matrix(IDENTITY);
}

GraphicObject_SkyBox::~GraphicObject_SkyBox()
{
	delete pSkyB;
}

void GraphicObject_SkyBox::SetWorld(const Matrix& m)
{
	World = m;
}

void GraphicObject_SkyBox::Render()
{
	pShader->SetTextureResourceAndSampler(pTexture);
	pShader->SendWorld(World);
	pSkyB->Render(pShader->GetContext());

}