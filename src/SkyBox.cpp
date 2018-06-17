#include "SkyBox.h"
#include "Model.h"

SkyBox::SkyBox(ID3D11Device* dev, float scale)
{
	pModel = new Model(dev, Model::UnitSkyBox, scale);
}

SkyBox::~SkyBox()
{
	delete pModel;
}

void SkyBox::Render(ID3D11DeviceContext* context)
{
	pModel->Render(context);
}