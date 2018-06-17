#include "GraphicObject_TextureLight.h"
#include "Model.h"
#include "ShaderTextureLight.h"
#include <assert.h>

GraphicObject_TextureLight::GraphicObject_TextureLight(ShaderTextureLight* shaderTextureLight, Model* mod)
{
	SetModel(mod);
	pShaderLight = shaderTextureLight;

	World = Matrix(IDENTITY);

	int n = mod->GetMeshCount();
	meshT = new Texture*[n];
	meshAmbient = new Vect[n];
	meshDiffuse = new Vect[n];
	meshSpecular = new Vect[n];
	for (int i = 0; i < n; i++)
	{
		meshT[i] = nullptr;
		meshAmbient[i] = Vect(1, 1, 1);
		meshDiffuse[i] = Vect(1, 1, 1);
		meshSpecular[i] = Vect(1, 1, 1);
	}
}

GraphicObject_TextureLight::~GraphicObject_TextureLight()
{
	delete[] meshT;
	delete[] meshAmbient;
	delete[] meshDiffuse;
	delete[] meshSpecular;
}

void GraphicObject_TextureLight::SetMaterial(const Vect& a, const Vect& d, const Vect& s)
{
	for (int i = 0; i <this->pModel->GetMeshCount(); i++)
	{
		meshAmbient[i] = a;
		meshDiffuse[i] = d;
		meshSpecular[i] = s;
	}
}

void GraphicObject_TextureLight::SetMaterial(const Vect& a, const Vect& d, const Vect& s, int meshnum)
{
	meshAmbient[meshnum] = a;
	meshDiffuse[meshnum] = d;
	meshSpecular[meshnum] = s;
}

void GraphicObject_TextureLight::SetTexture(Texture* tex)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
		meshT[i] = tex;
}

void GraphicObject_TextureLight::SetTexture(Texture* tex, int meshnum)
{
		meshT[meshnum] = tex;
}

void GraphicObject_TextureLight::SetWorld(const Matrix& world)
{
	World = world;
}

void GraphicObject_TextureLight::Render()
{
	pModel->BindVertexIndexBuffers(pShaderLight->GetContext());

	//pShaderTL->SendWorld(World);

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShaderLight->SetTextureResourceAndSampler(meshT[i]);
		pShaderLight->SendWorldAndMaterial(World, meshAmbient[i], meshDiffuse[i], meshSpecular[i]);
		pModel->RenderMesh(pShaderLight->GetContext(), i);
	}
}