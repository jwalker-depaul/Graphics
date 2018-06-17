#ifndef _SkyBox
#define _SkyBox

class Model;
struct ID3D11Device;
struct ID3D11DeviceContext;


class SkyBox
{
private:
	Model * pModel;

public:
	SkyBox(const SkyBox&) = delete;				// Copy constructor
	SkyBox(Model&&) = delete;                    // Move constructor
	SkyBox& operator=(const SkyBox&) & = delete;  // Copy assignment operator
	SkyBox& operator=(SkyBox&&) & = delete;       // Move assignment operator
	~SkyBox();

	SkyBox(ID3D11Device* dev, float scale = 1.0f);

	void Render(ID3D11DeviceContext* context);

};

#endif _SkyBox