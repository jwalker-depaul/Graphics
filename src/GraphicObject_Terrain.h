#include "GraphicObject_Base.h"
#include "TerrainModel.h"
#include "ShaderTexture.h"

class GraphicObject_Terrain : public GraphicObject_Base
{
	friend class ShaderTexture;

public:
	GraphicObject_Terrain(const GraphicObject_Terrain&) = delete;				 // Copy constructor
	GraphicObject_Terrain(GraphicObject_Terrain&&) = default;                    // Move constructor
	GraphicObject_Terrain& operator=(const GraphicObject_Terrain&) & = default;  // Copy assignment operator
	GraphicObject_Terrain& operator=(GraphicObject_Terrain&&) & = default;       // Move assignment operator
	~GraphicObject_Terrain();		  											 // Destructor

	GraphicObject_Terrain() = delete;

	void SetTexture(Texture* tex);
	void SetWorld(const Matrix& m);
	virtual void Render() override;

	GraphicObject_Terrain(ShaderTexture* texture, TerrainModel* terrainMod);

private:
	ShaderTexture * pShaderTexture;
	Texture * pTexture;
	Matrix World;
	TerrainModel* pTerrain;
};