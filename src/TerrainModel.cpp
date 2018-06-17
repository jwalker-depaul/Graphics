#include "TerrainModel.h"
#include "Model.h"
#include "d3dUtil.h"
#include "DirectXTex.h"
#include <assert.h>


TerrainModel::TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV)
{
	// Height map
	DirectX::ScratchImage scrtTex;
	HRESULT hr = LoadFromTGAFile(heightmapFile, nullptr, scrtTex);
	assert(SUCCEEDED(hr));

	const DirectX::Image* hgtmap = scrtTex.GetImage(0, 0, 0);
	assert(hgtmap->height == hgtmap->width ); // Check that it's evenenly spread

	size_t side = hgtmap->height;	// the image should be square
	//size_t pixel_width = 4;			// 4 bytes RGBA per pixel
	//uint8_t h_val = hgtmap->pixels[ pixel_width * (5 * side + 3) ]; // the 'R' byte of the pixel at (3,5)
	uint8_t h_val = 0;
	// ** much work to add below **

	int ntri = ((side - 1)*(side - 1)) * 2;
	TriangleByIndex* pTriList = new TriangleByIndex[ntri];

	int nverts = ntri * 3;
	StandardVertex* pVerts = new StandardVertex[nverts];

	int inc = 0;
	for (int j = 0; j < (int)side; j++)
	{
		for (int i = 0; i < (int)side; i++)
		{
			h_val = hgtmap->pixels[TexelIndex(side, i, j)];
			h_val = uint8_t(((float)h_val / 255) * maxheight);
			pVerts[inc].set((float)i * len, ytrans + (float)h_val, (float)j * len, RepeatU * ((float)i / side), RepeatV * ((float)j / side), Colors::Black);
			pVerts[inc].normal = pVerts[inc++].Pos.getNorm();
		}
	}
	inc = 0;
	int x = 0;
	int y = 0;
	int z = 0;
	for (int j = 0; j < (int)side - 1; j++)
	{
		for (int i = 0; i < (int)side - 1; i++)
		{
			x = j * side + i;
			y = (j+1) * side + i;
			z = j *side + i + 1;
			pTriList[inc++].set(x, y, z);

			x = (j + 1)*side + i;
			y = (j+1) * side + i + 1;
			z = j *side + i + 1;
			pTriList[inc++].set(x, y, z);
		}
	}

	pModTerrain = new Model(dev, pVerts, nverts, pTriList, ntri);
}

int TerrainModel::TexelIndex(int side, int i, int j) const
{
	return  4 * (j*side + i);
}

TerrainModel::~TerrainModel()
{
	delete pModTerrain;
}

void TerrainModel::Render(ID3D11DeviceContext* context)
{
	pModTerrain->Render(context);
}