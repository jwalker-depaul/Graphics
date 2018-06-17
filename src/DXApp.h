// DXApp
// Andre Berthiaume, June 2016
// Note: DX 11 SDK https://www.microsoft.com/en-us/download/details.aspx?id=6812
// Note on weird stuff with swap chain (1s and 2s) https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

#ifndef _DXApp
#define _DXApp

#include <d3d11.h>
#include "d3dUtil.h"
#include "Align16.h"
#include "GameTimer.h"
#include <string>

// New includes for demo
#include "Vect.h"
#include "Matrix.h"
#include "Camera.h"
#include "ShaderColor.h"
#include "ShaderColorLight.h"
#include "ShaderTexture.h"
#include "ShaderTextureLight.h"
#include "GraphicObject_Texture.h"
#include "GraphicObject_TextureLight.h"
#include "GraphicObject_ColorLight.h"
#include "GraphicObject_Terrain.h"
#include "GraphicObject_TerrainLight.h"
#include "GraphicObject_SkyBox.h"

class Model;
class Texture;
class FlatPlane;
class TerrainModel;
class SkyBox;

class DXApp : public Align16
{
private:
	// Main window handle
	HWND      mhMainWnd;

	Vect BackgroundColor;

	// DX application elements
	ID3D11Device* md3dDevice;					// Connects to the graphics card
	ID3D11DeviceContext* md3dImmediateContext;	// Settings for the GPU to use
	IDXGISwapChain* mSwapChain;					// image buffers used for rendering
	ID3D11RenderTargetView* mRenderTargetView;	// Where to send rendring operations (typically: points to one of the swap buffers)
	ID3D11DepthStencilView* mpDepthStencilView; // Needed to force depth-buffer operations

	GameTimer mTimer;
	std::wstring mMainWndCaption;
	int mClientWidth;
	int mClientHeight;

	void InitDirect3D();
	void InitDemo();
	void UpdateScene();
	void DrawScene();
	void CalculateFrameStats();

	// Shader loading utility. SHould be moved elsewhere later...
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	// Debug utility
	void ReportLiveDXObjects();

	// Demo specific additions
	Camera mCam;


	Matrix mWorld1;

	ShaderTexture* pShaderTexture;
	Texture* textureCube;
	
	Vect pos2;
	Vect MoveLightPos;
	Vect eyepos;

	// Camera vars
	Vect tempCamPos;
	float camSpeed = 0.04f;
	float rotSpeed = 0.01f;


	ShaderColor* pShaderColor;
	//ShaderColorLight* pShaderColorLight;

	// FINAL PROJECT
	// 6 face box
	Texture* textureSixFace;
	Model* modelSixFaceBox;
	Matrix worldSixFace;

	// Companion cube
	Matrix worldHoverLight;
	Model* modelCompanionCube;

	// Skybox
	GraphicObject_SkyBox* GO_SkyBox;
	Matrix worldSkyBox;
	Texture* texSkyBox;

	// Terrain
	TerrainModel* pTerrainModel;
	Texture* texTerrain;
	ShaderTextureLight* pShaderTextureLight;
	GraphicObject_TerrainLight* GO_Terrain;
	Matrix worldTerrain;
	

	// Pyramid
	Model* modelPyramid;
	GraphicObject_TextureLight* GO_Pyramid;
	Texture* texturePyramid;
	Matrix pyramidWorld;

	// Sun
	Model* modelSun;
	Matrix worldSun;

	// Frigate
	Model* modelTree;
	Texture* textureTree;
	GraphicObject_TextureLight* GO_ModelTree_1;
	GraphicObject_TextureLight* GO_ModelTree_2;
	GraphicObject_TextureLight* GO_ModelTree_3;
	GraphicObject_TextureLight* GO_ModelTree_4;
	GraphicObject_TextureLight* GO_ModelTree_5;
	Matrix worldTree;

	ID3D11RasterizerState* FrontFaceAsCCWRS;

	// gimmicky mouse control
	Vect MousePos;
	float mTheta;
	float mPhi;
	float mRadius;

public:
	DXApp(HWND hwnd);
	virtual ~DXApp();

	void FrameTick();

	// overrides for handling mouse input.
	void OnMouseDown(WPARAM btnState, int xval, int yval);
	void OnMouseUp(WPARAM btnState, int xval, int yval);
	void OnMouseMove(WPARAM btnState, int xval, int yval);
	void OnMouseWheel(short delta);


};

#endif _DXApp