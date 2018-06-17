#ifndef _ShaderTexture
#define _ShaderTexture

#include "ShaderBase.h"
#include "Texture.h"

struct ID3D11Buffer;
struct ID3D11Device;

class ShaderTexture : public ShaderBase
{
public:
	ShaderTexture(ID3D11Device* device);

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	void SetTextureResourceAndSampler(Texture* tex);
	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void ShaderTexture::SendWorld(const Matrix& world);

	~ShaderTexture();

private:
	struct CamMatrices
	{
		Matrix View;
		Matrix Projection;
	};

	ID3D11Buffer*           mpBufferCamMatrices;

	struct Data_World
	{
		Matrix World;
	};

	ID3D11Buffer*           mpBuffWorld;
};

#endif _ShaderTexture