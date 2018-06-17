#ifndef _GraphicObject_SkyBox
#define _GraphicObject_SkyBox

#include "GraphicObject_Base.h"
#include "Texture.h"
#include "ShaderTexture.h"

class GraphicObject_SkyBox : public GraphicObject_Base
{
	friend class ShaderTexture;
public:
	GraphicObject_SkyBox(const GraphicObject_SkyBox&) = delete;				 // Copy constructor
	GraphicObject_SkyBox(GraphicObject_SkyBox&&) = default;                    // Move constructor
	GraphicObject_SkyBox& operator=(const GraphicObject_SkyBox&) & = default;  // Copy assignment operator
	GraphicObject_SkyBox& operator=(GraphicObject_SkyBox&&) & = default;       // Move assignment operator
	~GraphicObject_SkyBox();		  											 // Destructor

	GraphicObject_SkyBox() = delete;

	void SetWorld(const Matrix& m);
	virtual void Render() override;

	GraphicObject_SkyBox(ShaderTexture* shader, ID3D11Device* dev, float scale, Texture* tex);

private:
	Model * pSkyB;
	ShaderTexture * pShader;
	Texture   *                     pTexture;
	Matrix							World;
};

#endif // !_GraphicObject_SkyBox
