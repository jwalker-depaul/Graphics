#ifndef _TerrainModel
#define _TerrainModel

#include "Matrix.h"
#include <tuple>
#include <d3d11.h>
#include "DirectXTex.h"

class Model;
struct ID3D11DeviceContext;
struct ID3D11Device;

class TerrainModel : public Align16
{

private:
	Model* pModTerrain;

public:
	TerrainModel(const TerrainModel&) = delete; // Copy constructor
	TerrainModel(Model&&) = delete; // Move constructor
	TerrainModel& operator= (const TerrainModel&) & = delete;
	TerrainModel& operator=(TerrainModel&&) & = delete;
	~TerrainModel();

	TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV);

	int TexelIndex(int side, int i, int j) const;

	void Render(ID3D11DeviceContext* context);

};



#endif _TerrainModel