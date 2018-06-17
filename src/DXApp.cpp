#include "DXApp.h"
#include <windows.h>
#include <sstream>
#include <assert.h>
#include "d3dUtil.h"

// needed to load shaders from file
#include <d3dcompiler.h>

#include "Model.h"
#include "ShaderColor.h"
#include "DirectXTex.h"
#include "Texture.h"
#include "FlatPlane.h"
#include "TerrainModel.h"
#include "SkyBox.h"

void DXApp::InitDemo()
{
	/************************
	***   LOAD TEXTURES   ***
	************************/
	textureCube		= new Texture(md3dDevice, L"../Assets/Textures/Companion_Cube.tga");
	texSkyBox	= new Texture(md3dDevice, L"../Assets/Textures/cloud_skybox.tga");
	texTerrain	= new Texture(md3dDevice, L"../Assets/Textures/sandgrass.tga", D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	texturePyramid = new Texture(md3dDevice, L"../Assets/Textures/pyramid_texture.tga");
	textureTree = new Texture(md3dDevice, L"../Assets/Textures/tree_texture.tga");
	textureSixFace = new Texture(md3dDevice, L"../Assets/Textures/water_skybox.tga");
	

	/******************
	***   SHADERS   ***
	******************/
	pShaderTexture			= new ShaderTexture(md3dDevice);
	pShaderTextureLight		= new ShaderTextureLight(md3dDevice);
	pShaderColor			= new ShaderColor(md3dDevice);
	//pShaderColorLight		= new ShaderColorLight(md3dDevice);

	/*****************
	***   MODELS   ***
	*****************/
	modelCompanionCube	= new Model(md3dDevice, Model::PreMadedeModels::UnitBoxRepeatedTexture);
	modelSun			= new Model(md3dDevice, Model::PreMadedeModels::UnitSphere);
	modelPyramid		= new Model(md3dDevice, Model::PreMadedeModels::CreateUnitPyramidRepTexture);
	modelTree			= new Model(md3dDevice, "../Assets/Models/tree.azul");
	modelSixFaceBox		= new Model(md3dDevice, Model::PreMadedeModels::UnitBoxSixFaceTexture);

	/*************************
	***   WORLD MATRICES   ***
	*************************/
	mWorld1			= Matrix(SCALE, 1, 1, 1) * Matrix(TRANS, 0, 0, 0);
	pos2 = Vect(-100, 0, -4);
	worldSun		= Matrix(SCALE, 5, 5, 5) * Matrix(TRANS, pos2);
	worldSkyBox		=  Matrix(TRANS, 0, 0, 0);
	worldTerrain	= Matrix(TRANS, -350, 0, -400);
	pyramidWorld	= Matrix(SCALE, 5, 5, 5) * Matrix(TRANS, 0, -4, 0);

	/*****************
	***   SKYBOX   ***
	*****************/
	//pSkyBox = new SkyBox(md3dDevice, 200);
	GO_SkyBox = new GraphicObject_SkyBox(pShaderTexture, md3dDevice, 400, texSkyBox);

	/******************
	***   TERRAIN   ***
	******************/
	pShaderTextureLight->SetDirectionalLightParameters(Vect(-1, -1, 1).getNorm(), .9 * Vect(1, 1, 1), .5 * Vect(1, 1, 1), Vect(1, 1, 1));

	pTerrainModel = new TerrainModel(md3dDevice, L"../Assets/Textures/TerrainMap.tga", 2, 150, -49, 100, 100);
	GO_Terrain = new GraphicObject_TerrainLight(pShaderTextureLight, pTerrainModel);
	GO_Terrain->SetTexture(texTerrain);
	GO_Terrain->SetWorld(worldTerrain);

	/******************
	***   PYRAMID   ***
	******************/
	//  Setup light
	
	Vect position = Vect(0, 0, 0);
	float range = 5000;
	Vect attenuation = .5 * Vect(1, 0, 0);
	Vect direction = Vect(0, -200, 0);
	float spotExp = 50;
	Vect ambient = 5 * Colors::White;//.2 * Vect(1, 1, 1);
	Vect diffuse = 3 * Colors::Blue;//3 * Vect(1, 1, 1);
	Vect specular = 1 * Vect(1, 1, 1, 150);
	pShaderTextureLight->SetSpotLightParameters(position, range, attenuation, direction, spotExp, ambient, diffuse, specular);

	

	GO_Pyramid = new GraphicObject_TextureLight(pShaderTextureLight, modelPyramid);
	GO_Pyramid->SetTexture(texturePyramid);
	GO_Pyramid->SetMaterial(Colors::AliceBlue, Colors::AliceBlue, Vect(1, 1, 1, 100));
	GO_Pyramid->SetWorld(pyramidWorld);

	/****************
	***   TREES   ***
	****************/
	// Tree 1
	position = Vect(3, 0, 10);
	range = 50;
	direction = Vect(3, -20, 10);
	pShaderTextureLight->SetSpotLightParameters2(position, range, attenuation, direction, spotExp, ambient, diffuse, specular);

	worldTree = Matrix(SCALE, .3f, .3f, .3f) * Matrix(RotType::ROT_X, -.5 * 3.14) * Matrix(TRANS, 3, -4, 10);

	GO_ModelTree_1 = new GraphicObject_TextureLight(pShaderTextureLight, modelTree);
	GO_ModelTree_1->SetTexture(textureTree);
	GO_ModelTree_1->SetMaterial(Colors::AliceBlue, Colors::AliceBlue, Vect(1, 1, 1, 100));
	GO_ModelTree_1->SetWorld(worldTree);

	// Tree 2
	//position = Vect(-5, 0, 12);
	//range = 50;
	//direction = Vect(3, -20, 10);
	//pShaderTextureLight->SetSpotLightParameters3(position, range, attenuation, direction, spotExp, ambient, diffuse, specular);

	worldTree = Matrix(SCALE, .5f, .5f, .5f) * Matrix(RotType::ROT_X, -.5 * 3.14) * Matrix(TRANS, -5, -5, 12);

	GO_ModelTree_2 = new GraphicObject_TextureLight(pShaderTextureLight, modelTree);
	GO_ModelTree_2->SetTexture(textureTree);
	GO_ModelTree_2->SetMaterial(Colors::AliceBlue, Colors::AliceBlue, Vect(1, 1, 1, 100));
	GO_ModelTree_2->SetWorld(worldTree);

	// Tree 3
	worldTree = Matrix(SCALE, .3f, .3f, .3f) * Matrix(RotType::ROT_X, -.5 * 3.14) * Matrix(TRANS, -7, -4, 3);

	GO_ModelTree_3 = new GraphicObject_TextureLight(pShaderTextureLight, modelTree);
	GO_ModelTree_3->SetTexture(textureTree);
	GO_ModelTree_3->SetMaterial(Colors::AliceBlue, Colors::AliceBlue, Vect(1, 1, 1, 100));
	GO_ModelTree_3->SetWorld(worldTree);

	// Tree 4
	worldTree = Matrix(SCALE, .7f, .7f, .7f) * Matrix(RotType::ROT_X, -.5 * 3.14) * Matrix(TRANS, -3, 0, -4);

	GO_ModelTree_4 = new GraphicObject_TextureLight(pShaderTextureLight, modelTree);
	GO_ModelTree_4->SetTexture(textureTree);
	GO_ModelTree_4->SetMaterial(Colors::AliceBlue, Colors::AliceBlue, Vect(1, 1, 1, 100));
	GO_ModelTree_4->SetWorld(worldTree);

	// Tree 5
	worldTree = Matrix(SCALE, 5, 5, 5) * Matrix(RotType::ROT_X, -.5 * 3.14) * Matrix(TRANS, -30, 20, -80);

	GO_ModelTree_5 = new GraphicObject_TextureLight(pShaderTextureLight, modelTree);
	GO_ModelTree_5->SetTexture(textureTree);
	GO_ModelTree_5->SetMaterial(Colors::AliceBlue, Colors::AliceBlue, Vect(1, 1, 1, 100));
	GO_ModelTree_5->SetWorld(worldTree);

	/****************
	***   OTHER   ***
	****************/
	// Initialize the projection matrix
	mCam.setPerspective(3.14159 / 3, mClientWidth / (float)mClientHeight, 1.0f, 1000.0f);
	mCam.setOrientAndPosition(Vect(0, 1, 0), Vect(0, 0, 0), Vect(-5, 2, -8));

	// Initialize gimmicky mouse control values
	mTheta = .5;
	mPhi = 3.1415f / 8;
	mRadius = 6;

	mTimer.Reset();
}

void DXApp::UpdateScene()
{
	worldSun *= Matrix(ROT_Y, .003f);  // Simple slow rotation about y axis
	pos2 = worldSun.get(MatrixRowType::ROW_3);
	MoveLightPos = worldSun.get(MatrixRowType::ROW_3);
	mCam.getPos(tempCamPos);
	worldSkyBox = Matrix(TRANS, tempCamPos);

	
	if (GetKeyState('W') & 0x08000)
	{
		mCam.TranslateFwdBack(camSpeed);
	}
	else if (GetKeyState('S') & 0x08000)
	{
		mCam.TranslateFwdBack(-camSpeed);
	}

	if (GetKeyState('A') & 0x08000)
	{
		mCam.TranslateLeftRight(-camSpeed);
	}
	else if (GetKeyState('D') & 0x08000)
	{
		mCam.TranslateLeftRight(camSpeed);
	}

	if (GetKeyState(VK_LEFT) & 0x08000)
	{
		mCam.TurnLeftRight(rotSpeed);
	}
	else if (GetKeyState(VK_RIGHT) & 0x08000)
	{
		mCam.TurnLeftRight(-rotSpeed);
	}

	if (GetKeyState(VK_UP) & 0x08000)
	{
		mCam.TiltUpDown(rotSpeed);
	}
	else if (GetKeyState(VK_DOWN) & 0x08000)
	{
		mCam.TiltUpDown(-rotSpeed);
	}

	mCam.updateCamera();
}

void DXApp::DrawScene()
{
	// Clear the back buffer
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, VasA(BackgroundColor));
	// Clear the depth stencil;
	md3dImmediateContext->ClearDepthStencilView(mpDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	mCam.getPos(eyepos);

	/*************************
	***   COMPANION CUBE   ***
	*************************/
	
	worldHoverLight = mWorld1 * Matrix(TRANS, 0, 2 * cosf(mTimer.TotalTime()), 0);
	pShaderTexture->SetToContext(md3dImmediateContext);
	pShaderTexture->SetTextureResourceAndSampler(textureCube);
	pShaderTexture->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());
	pShaderTexture->SendWorld(worldHoverLight);
	
	modelCompanionCube->Render(md3dImmediateContext);

	/***********************
	***   SIX FACE BOX   ***
	***********************/
	worldSixFace = Matrix(TRANS, 0 , 3 , 0);
	worldSixFace = mWorld1 * Matrix(TRANS, 2 * cosf(mTimer.TotalTime()), 0, 0);
	pShaderTexture->SetTextureResourceAndSampler(textureSixFace);
	pShaderTexture->SendWorld(worldSixFace);
	modelSixFaceBox->Render(md3dImmediateContext);

	/**************
	***   SUN   ***
	**************/
	pShaderTextureLight->SetSpotLightParameters3(MoveLightPos, 50, .5 * Vect(1, 0, 0), Vect(0, -200, 0), 50, 5 * Colors::White, 3 * Colors::Blue, 1 * Vect(1, 1, 1, 150));

	pShaderColor->SetToContext(md3dImmediateContext);
	pShaderColor->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());
	
	pShaderColor->SendWorldColor(worldSun, Colors::Yellow);

	modelSun->Render(md3dImmediateContext);

	/*****************
	***   SKYBOX   ***
	*****************/
	pShaderTexture->SetToContext(md3dImmediateContext);
	pShaderTexture->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());
	pShaderTexture->SendWorld(worldSkyBox);
	GO_SkyBox->SetWorld(worldSkyBox);
	GO_SkyBox->Render();

	/******************
	***   TERRAIN   ***
	******************/
	pShaderTextureLight->SetToContext(md3dImmediateContext);
	pShaderTextureLight->SetTextureResourceAndSampler(texTerrain);
	pShaderTextureLight->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());
	pShaderTextureLight->SendFogDetails(5, 50); // 5, 50

	//texTerrain->SetToContext(md3dImmediateContext);
	//pTerrainModel->Render(md3dImmediateContext);
	GO_Terrain->SetMaterial(Colors::AntiqueWhite, Colors::Firebrick, Vect(1, 1, 1, 100));
	
	// Eye position
	pShaderTextureLight->SendLightParameters(eyepos);

	GO_Terrain->Render();

	/******************
	***   PYRAMID   ***
	******************/
	pShaderTextureLight->SetToContext(md3dImmediateContext);
	Matrix temp = mWorld1 * Matrix(TRANS, 0, 2 * cosf(mTimer.TotalTime()), 0);
	pShaderTextureLight->SendWorldAndMaterial(worldHoverLight, .2 * Colors::Blue, 3 * Colors::Blue, 1 * Vect(1, 1, 1, 150));
	pShaderTextureLight->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());

	// Eye position
	pShaderTextureLight->SendLightParameters(eyepos);

	// Render
	GO_Pyramid->Render();

	/****************
	***   TREES   ***
	****************/
	pShaderTextureLight->SetToContext(md3dImmediateContext);
	GO_ModelTree_1->Render();
	GO_ModelTree_2->Render();
	GO_ModelTree_3->Render();
	GO_ModelTree_4->Render();
	GO_ModelTree_5->Render();
	 
	// Switches the display to show the now-finished back-buffer
	mSwapChain->Present(0, 0);
}


DXApp::DXApp(HWND hwnd)
{
	assert(hwnd);
	mhMainWnd = hwnd;

	BackgroundColor = Colors::MidnightBlue;

	md3dDevice = nullptr;
	md3dImmediateContext = nullptr;
	mSwapChain = nullptr;
	mRenderTargetView = nullptr;

	// Get window data through the window handle
	RECT rc;
	BOOL err = GetClientRect(mhMainWnd, &rc);  // Seriously MS: Redifining BOOL as int? Confusing much?
	assert(err);

	// get width/hight
	mClientWidth = rc.right - rc.left;
	mClientHeight = rc.bottom - rc.top;

	// Get window caption
	const int MAX_LABEL_LENGTH = 100; // probably overkill...
	WCHAR str[MAX_LABEL_LENGTH];
	GetWindowText(mhMainWnd, str, MAX_LABEL_LENGTH);
	mMainWndCaption = str;

	// Initialize DX11
	this->InitDirect3D();

	// Demo initialization
	this->InitDemo();
}

DXApp::~DXApp()
{
	// Textures
	delete textureCube;
	delete texSkyBox;
	delete texTerrain;
	delete texturePyramid;
	delete textureTree;
	delete textureSixFace;

	// Shaders
	delete pShaderTexture;
	delete pShaderTextureLight;
	delete pShaderColor;

	// Models
	delete modelCompanionCube;
	delete modelSun;
	delete modelPyramid;
	delete modelTree;
	delete modelSixFaceBox;

	// Skybox
	delete GO_SkyBox;

	// Terrain
	delete pTerrainModel;
	delete GO_Terrain;

	// Pyramid
	delete GO_Pyramid;
	
	// Trees
	delete GO_ModelTree_1;
	delete GO_ModelTree_2;
	delete GO_ModelTree_3;
	delete GO_ModelTree_4;
	delete GO_ModelTree_5;

	ReleaseAndDeleteCOMobject(FrontFaceAsCCWRS);

	ReleaseAndDeleteCOMobject(mRenderTargetView);
	ReleaseAndDeleteCOMobject(mpDepthStencilView);
	ReleaseAndDeleteCOMobject(mSwapChain);
	ReleaseAndDeleteCOMobject(md3dImmediateContext);

	// Must be done BEFORE the device is released
	ReportLiveDXObjects();		// See http://masterkenth.com/directx-leak-debugging/

	ReleaseAndDeleteCOMobject(md3dDevice);
}

// See http://masterkenth.com/directx-leak-debugging/
void DXApp::ReportLiveDXObjects()
{
#ifdef _DEBUG
	HRESULT hr = S_OK;

	// Now we set up the Debug interface, to be queried on shutdown
	ID3D11Debug* debugDev;
	hr = md3dDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&debugDev));
	assert(SUCCEEDED(hr));

	debugDev->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	ReleaseAndDeleteCOMobject(debugDev);
#endif
}

void DXApp::InitDirect3D()
{
	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// This is a *greatly* simplified process to create a DX device and context:
	// We force the use of DX11 feature level since that's what CDM labs are limited to.
	// For real-life applications would need to test what's the best feature level and act accordingly
	hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, nullptr, 0, D3D11_SDK_VERSION, &md3dDevice, nullptr, &md3dImmediateContext);
	assert(SUCCEEDED(hr));

	// Now we obtain the associated DXGIfactory1 with our device 
	// Many steps...
	IDXGIDevice* dxgiDevice = nullptr;
	hr = md3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
	assert(SUCCEEDED(hr));

	IDXGIAdapter* adapter = nullptr;
	hr = dxgiDevice->GetAdapter(&adapter);
	assert(SUCCEEDED(hr));

	IDXGIFactory1* dxgiFactory1 = nullptr;
	hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory1));
	assert(SUCCEEDED(hr));
	// See also note on weird stuff with factories and swap chains (1s and 2s)
	// https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

	// We are done with these now...
	ReleaseAndDeleteCOMobject(adapter);
	ReleaseAndDeleteCOMobject(dxgiDevice);

	// Controls MSAA option:
	// - 4x count level garanteed for all DX11 
	// - MUST be the same for depth buffer!
	// - We _need_ to work with the depth buffer because reasons... (see below)
	DXGI_SAMPLE_DESC sampDesc;
	sampDesc.Count = 1;
	sampDesc.Quality = static_cast<UINT>(D3D11_CENTER_MULTISAMPLE_PATTERN);  // MS: what's with the type mismtach?

	DXGI_MODE_DESC buffdesc;				// https://msdn.microsoft.com/en-us/library/windows/desktop/bb173064(v=vs.85).aspx
	ZeroMemory(&buffdesc, sizeof(buffdesc));
	buffdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Next we create a swap chain. 
	// Useful thread: http://stackoverflow.com/questions/27270504/directx-creating-the-swapchain
	// Note that this is for a DirectX 11.0: in a real app, we should test the feature levels and act accordingly

	DXGI_SWAP_CHAIN_DESC sd;				// See MSDN: https://msdn.microsoft.com/en-us/library/windows/desktop/bb173075(v=vs.85).aspx
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;						// Much confusion about this number... see http://www.gamedev.net/topic/633807-swap-chain-buffer-count/
	sd.BufferDesc = buffdesc;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = mhMainWnd;
	sd.SampleDesc = sampDesc;
	sd.Windowed = TRUE;

	hr = dxgiFactory1->CreateSwapChain(md3dDevice, &sd, &mSwapChain);
	assert(SUCCEEDED(hr));
	ReleaseAndDeleteCOMobject(dxgiFactory1);

	// Create a render target view		https://msdn.microsoft.com/en-us/library/windows/desktop/ff476582(v=vs.85).aspx
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	assert(SUCCEEDED(hr));;

	hr = md3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &mRenderTargetView);
	ReleaseAndDeleteCOMobject(pBackBuffer);
	assert(SUCCEEDED(hr));

	/**********************************************************/

	// First we fix what it means for triangles to be front facing.
	// Requires setting a whole new rasterizer state
	//*
	D3D11_RASTERIZER_DESC rd;
	rd.FillMode = D3D11_FILL_SOLID;  // Also: D3D11_FILL_WIREFRAME
	rd.CullMode = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = true; // true for RH forward facing
	rd.DepthBias = 0;
	rd.SlopeScaledDepthBias = 0.0f;
	rd.DepthBiasClamp = 0.0f;
	rd.DepthClipEnable = true;
	rd.ScissorEnable = false;
	rd.MultisampleEnable = true;  // Does not in fact turn on/off multisample: https://msdn.microsoft.com/en-us/library/windows/desktop/ff476198(v=vs.85).aspx
	rd.AntialiasedLineEnable = false;

	//ID3D11RasterizerState* rs;
	md3dDevice->CreateRasterizerState(&rd, &FrontFaceAsCCWRS);

	md3dImmediateContext->RSSetState(FrontFaceAsCCWRS);
	//ReleaseAndDeleteCOMobject(rs); // we can release this resource since we won't be changing it any further
	//*/

	// We must turn on the abilty to process depth during rendering.
	// Done through depth stencils (see https://msdn.microsoft.com/en-us/library/windows/desktop/bb205074(v=vs.85).aspx)
	// Below is a simplified version
	//*
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = mClientWidth;
	descDepth.Height = mClientHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc = sampDesc;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	ID3D11Texture2D* pDepthStencil;
	hr = md3dDevice->CreateTexture2D(&descDepth, NULL, &pDepthStencil);
	assert(SUCCEEDED(hr));

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	descDSV.Texture2D.MipSlice = 0;;

	hr = md3dDevice->CreateDepthStencilView(pDepthStencil, &descDSV, &mpDepthStencilView);
	assert(SUCCEEDED(hr));
	ReleaseAndDeleteCOMobject(pDepthStencil);
	//*/

	/**********************************************************/

	//md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, nullptr);  // to use without depth stencil
	md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mpDepthStencilView);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)mClientWidth;
	vp.Height = (FLOAT)mClientHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	md3dImmediateContext->RSSetViewports(1, &vp);
}

void DXApp::CalculateFrameStats()
{
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	// Compute averages over one second period.
	if ((mTimer.TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		std::wostringstream outs;
		outs.precision(6);
		outs << mMainWndCaption << L"    "
			<< L"FPS: " << fps << L"    "
			<< L"Frame Time: " << mspf << L" (ms)";
		SetWindowText(mhMainWnd, outs.str().c_str());

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}

void DXApp::FrameTick()
{
	mTimer.Tick();
	CalculateFrameStats();

	this->UpdateScene();
	this->DrawScene();
}

void DXApp::OnMouseDown(WPARAM btnState, int xval, int yval)
{
	// Gimmicky mouse control
	if (btnState & MK_LBUTTON)
	{
		MousePos[x] = static_cast<float>(xval);
		MousePos[y] = static_cast<float>(yval);
	}
}

void DXApp::OnMouseUp(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);
}

void DXApp::OnMouseMove(WPARAM btnState, int xval, int yval)
{
	// Gimmicky mouse control
	if (btnState & MK_LBUTTON)
	{
		float dx = 0.01f*(MousePos[x] - xval);
		float dy = 0.01f*(MousePos[y] - yval);

		// Update angles based on input to orbit camera around box.
		mTheta += dx;
		mPhi -= dy;

		static float verticalMax = MATH_PI2 - 0.2f;

		if (mPhi > verticalMax)
			mPhi = verticalMax;
		else if (mPhi < -verticalMax)
			mPhi = -verticalMax;

		// Build the view matrix using gimmicky trick
		Vect target = Vect(0, 0, 0, 0);
		Vect up = Vect(0, 1, 0, 0);
		Vect pos = Vect(0, 0, -mRadius) * Matrix(ROT_Y, mTheta) * Matrix(ROT_X, mPhi);
		mCam.setOrientAndPosition(up, target, pos);
	}

	MousePos[x] = static_cast<float>(xval);
	MousePos[y] = static_cast<float>(yval);
}

void  DXApp::OnMouseWheel(short delta)
{
	if (delta > 0)
	{
		mRadius -= 1;
	}
	else
	{
		mRadius += 1;
	}
}


// Shader loading utility. Will be moved elsewhere later...
// Needs to be moved. Requires
HRESULT DXApp::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;

	// Disable optimizations to further improve shader debugging
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel, dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob)
		{
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}