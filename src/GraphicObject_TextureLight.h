#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderTextureLight.h"
#include "Texture.h"

class GraphicObject_TextureLight : public GraphicObject_Base
{
	friend class ShaderTextureLight;

public:
	GraphicObject_TextureLight(const GraphicObject_TextureLight&) = delete;				 // Copy constructor
	GraphicObject_TextureLight(GraphicObject_TextureLight&&) = default;                    // Move constructor
	GraphicObject_TextureLight& operator=(const GraphicObject_TextureLight&) & = default;  // Copy assignment operator
	GraphicObject_TextureLight& operator=(GraphicObject_TextureLight&&) & = default;       // Move assignment operator
	~GraphicObject_TextureLight();		  											 // Destructor

	GraphicObject_TextureLight() = delete;

	void SetMaterial(const Vect& a, const Vect& d, const Vect& s);
	void SetTexture(Texture* tex);
	void SetWorld(const Matrix& world);

	void SetTexture(Texture* tex, int meshnum);
	void SetMaterial(const Vect&am, const Vect&dif, const Vect& sp, int meshnum);

	virtual void Render() override;

	GraphicObject_TextureLight(ShaderTextureLight* shader, Model* mod);

private:
	ShaderTextureLight * pShaderLight;
	Vect*				meshAmbient;
	Vect*				meshDiffuse;
	Vect*				meshSpecular;
	Texture**			meshT;
	Matrix				World;
};