#include "GraphicObject_Base.h"
#include "TerrainModel.h"
#include "ShaderTextureLight.h"

class GraphicObject_TerrainLight : public GraphicObject_Base
{
	friend class ShaderTextureLight;

public:
	GraphicObject_TerrainLight(const GraphicObject_TerrainLight&) = delete;				 // Copy constructor
	GraphicObject_TerrainLight(GraphicObject_TerrainLight&&) = default;                    // Move constructor
	GraphicObject_TerrainLight& operator=(const GraphicObject_TerrainLight&) & = default;  // Copy assignment operator
	GraphicObject_TerrainLight& operator=(GraphicObject_TerrainLight&&) & = default;       // Move assignment operator
	~GraphicObject_TerrainLight();		  											 // Destructor

	GraphicObject_TerrainLight() = delete;

	void SetMaterial(const Vect& a, const Vect& d, const Vect& s);
	void SetWorld(const Matrix& m);
	void SetTexture(Texture* tex);
	virtual void Render() override;

	GraphicObject_TerrainLight(ShaderTextureLight* texture, TerrainModel* terrainMod);

private:
	ShaderTextureLight * pShaderTextureLight;
	Texture * pTexture;
	Matrix World;
	TerrainModel* pTerrain;
	Vect ambient;
	Vect diffuse;
	Vect specular;
};