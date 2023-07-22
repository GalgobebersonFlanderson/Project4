#include "stdafx.h"

DirectXecution::DirectXecution()
{
}


DirectXecution::~DirectXecution()
{
}

void DirectXecution::DirectXInit(HWND _window)
{
	//Camera setup
	CameraSetup({ 0.0f, 0.0f, -4.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 0.0f });

	//Camera var setup
	angleY = 55.0f;
	nearP = 0.1f;
	farP = 100.0f;
	width = 1000.0f;
	height = 1000.0f;

	//Model load
	bool bResult;
	bResult = utility.LoadOBJFile("Krabby Patty/krabbypattie01.obj", pattyVerts, pattyInds);
	bResult = utility.LoadOBJFile("SpongeMan/spongebob.obj", spongeManVerts, spongeManInds);
	bResult = utility.LoadOBJFile("SpongeManHouse/building_pineapple01.obj", spongeManHouseVerts, spongeManHouseInds);
	bResult = utility.LoadOBJFile("StarMan/patrick.obj", starManVerts, starManInds);
	bResult = utility.LoadOBJFile("StarManHouse/patricksrock.obj", starManHouseVerts, starManHouseInds);
	bResult = utility.LoadOBJFile("Floor/floor.obj", floorVerts, floorInds);
	//bResult = utility.LoadOBJFile("Teapot/teapot.obj", teapotVerts, teapotInds);
	bResult = utility.LoadOBJFile("Skybox/skybox.obj", skyboxVerts, skyboxInds);

	//Cube setup
	cubeRect.left = -0.5f;
	cubeRect.right = 0.5f;
	cubeRect.top = 0.5f;
	cubeRect.bottom = -0.5f;
	utility.GenerateCubeVertsAndIndices(cubeVerts, 0.5f, cubeRect, cubeInd);

	//Adjusting matricies
		//Set
			for (unsigned int i = 0; i < ARRAYSIZE(cubeMats); ++i)
			{
				cubeMats[i] = XMMatrixIdentity();
			}
		//Translate
			cubeMats[0] = utility.Translate(XMFLOAT3(-13.0f, 0.73f, -5.0f), 0, cubeMats[0]);
			cubeMats[1] = utility.Translate(XMFLOAT3(-13.0f, 2.94f, -5.0f), 0, cubeMats[1]);
			cubeMats[2] = utility.Translate(XMFLOAT3(-13.0f, 4.67f, -5.0f), 0, cubeMats[2]);
			cubeMats[3] = utility.Translate(XMFLOAT3(-13.0f, 5.9f, -5.0f), 0, cubeMats[3]);
			cubeMat = utility.Translate(XMFLOAT3(0.0f, 0.5f, 3.0f), 0, cubeMat);
			pattyMat = utility.Translate(XMFLOAT3(-13.0f, 6.4f, -5.0f), 0, pattyMat);
			spongeManMat = utility.Translate(XMFLOAT3(-6.0f, -0.5f, 2.0f), 0, spongeManMat);
			spongeManHouseMat = utility.Translate(XMFLOAT3(-6.0f, -0.5f, -5.0f), 0, spongeManHouseMat);
			starManMat = utility.Translate(XMFLOAT3(8.0f, -0.5f, 2.0f), 0, starManMat);
			starManHouseMat = utility.Translate(XMFLOAT3(8.0f, -0.5f, -4.8f), 0, starManHouseMat);
			//teapotMat = utility.Translate(XMFLOAT3(0.0f, -0.5f, -3.0f), 0, teapotMat);
			floorMat = utility.Translate(XMFLOAT3(0.0f, -0.5f, 0.0f), 0, floorMat);
		//Scale
			cubeMats[0] = utility.Scale(XMFLOAT3(2.5f, 2.5f, 2.5f), 0, cubeMats[0]);
			cubeMats[1] = utility.Scale(XMFLOAT3(2.0f, 2.0f, 2.0f), 0, cubeMats[1]);
			cubeMats[2] = utility.Scale(XMFLOAT3(1.5f, 1.5f, 1.5f), 0, cubeMats[2]);
			pattyMat = utility.Scale(XMFLOAT3(0.1f, 0.1f, 0.1f), 0, pattyMat);
			floorMat = utility.Scale(XMFLOAT3(1.5f, 2.0f, 1.0f), 0, floorMat);
			//teapotMat = utility.Scale(XMFLOAT3(0.04f, 0.04f, 0.04f), 0, teapotMat);
			spongeManMat = utility.Scale(XMFLOAT3(0.1f, 0.1f, 0.1f), 0, spongeManMat);
			spongeManHouseMat = utility.Scale(XMFLOAT3(0.3f, 0.3f, 0.3f), 0, spongeManHouseMat);
			starManMat = utility.Scale(XMFLOAT3(4.0f, 4.0f, 4.0f), 0, starManMat);
			starManHouseMat = utility.Scale(XMFLOAT3(7.5f, 7.5f, 7.5f), 0, starManHouseMat);

	//Initialize directX11
	DX11Setup(_window);

	//Create texture
	result = CreateDDSTextureFromFile(m_pDevice.Get(), L"cubemat.dds", (ID3D11Resource**)m_pBrickTexture.GetAddressOf(), m_pCubeSrv.GetAddressOf());

	result = CreateDDSTextureFromFile(m_pDevice.Get(), L"Krabby Patty/krabbypattie01.dds", (ID3D11Resource**)m_pPattyTexture.GetAddressOf(), m_pPattySrv.GetAddressOf());

	result = CreateDDSTextureFromFile(m_pDevice.Get(), L"SpongeMan/spongetux.dds", (ID3D11Resource**)m_pSpongeManTexture.GetAddressOf(), m_pSpongeManSrv.GetAddressOf());
	result = CreateDDSTextureFromFile(m_pDevice.Get(), L"SpongeManHouse/building_pineapple01.dds", (ID3D11Resource**)m_pSpongeManHouseTexture.GetAddressOf(), m_pSpongeManHouseSrv.GetAddressOf());

	result = CreateDDSTextureFromFile(m_pDevice.Get(), L"StarMan/Tex_0086_2.dds", (ID3D11Resource**)m_pStarManTexture.GetAddressOf(), m_pStarManSrv.GetAddressOf());
	result = CreateDDSTextureFromFile(m_pDevice.Get(), L"StarManHouse/patricksrock.dds", (ID3D11Resource**)m_pStarManHouseTexture.GetAddressOf(), m_pStarManHouseSrv.GetAddressOf());

	//result = CreateDDSTextureFromFile(m_pDevice.Get(), L"Teapot/teapotmat.dds", (ID3D11Resource**)m_pPattyTexture.GetAddressOf(), m_pTeapotSrv.GetAddressOf());
	result = CreateDDSTextureFromFile(m_pDevice.Get(), L"Floor/floormat.dds", (ID3D11Resource**)m_pFloorTexture.GetAddressOf(), m_pFloorSrv.GetAddressOf());

	result = CreateDDSTextureFromFile(m_pDevice.Get(), L"Skybox/SkyboxOcean.dds", (ID3D11Resource**)m_pSkyboxTexture.GetAddressOf(), m_pSkyboxSrv.GetAddressOf());

	//Create stencil
	result = CreateDepthStencil();

	//Create layouts
	result = CreateCubeLayout();
	result = CreateOBJLayout();

	//Create buffers
	result = CreateVertexBuffer();
	result = CreateIndexBuffer();
	result = CreateVertexBuffer(pattyVerts, m_pPattyVertexBuffer);
	result = CreateIndexBuffer(pattyInds, m_pPattyIndexBuffer);
	result = CreateVertexBuffer(floorVerts, m_pFloorVertexBuffer);
	result = CreateIndexBuffer(floorInds, m_pFloorIndexBuffer);
	//result = CreateVertexBuffer(teapotVerts, m_pTeapotVertexBuffer);
	//result = CreateIndexBuffer(teapotInds, m_pTeapotIndexBuffer);
	result = CreateVertexBuffer(skyboxVerts, m_pSkyboxVertexBuffer);
	result = CreateIndexBuffer(skyboxInds, m_pSkyboxIndexBuffer);
	result = CreateVertexBuffer(spongeManVerts, m_pSpongeManVertexBuffer);
	result = CreateIndexBuffer(spongeManInds, m_pSpongeManIndexBuffer);
	result = CreateVertexBuffer(spongeManHouseVerts, m_pSpongeManHouseVertexBuffer);
	result = CreateIndexBuffer(spongeManHouseInds, m_pSpongeManHouseIndexBuffer);
	result = CreateVertexBuffer(starManVerts, m_pStarManVertexBuffer);
	result = CreateIndexBuffer(starManInds, m_pStarManIndexBuffer);
	result = CreateVertexBuffer(starManHouseVerts, m_pStarManHouseVertexBuffer);
	result = CreateIndexBuffer(starManHouseInds, m_pStarManHouseIndexBuffer);
	result = CreateConstBuffer(MatrixBuffer, m_pConstMatrixBuffer);
	result = CreateConstBuffer(MaterialBuffer, m_pConstMaterialBuffer);
	result = CreateConstBuffer(LightBuffer, m_pConstLightBuffer);
	result = CreateConstBuffer(InstancedMatrixBuffer, m_pConstInstancedMatrixBuffer);

	//Create shaders
	result = m_pDevice->CreateVertexShader(VertexShader, sizeof(VertexShader), NULL, m_pCubeVertShader.GetAddressOf());
	result = m_pDevice->CreateVertexShader(objVertexShader, sizeof(objVertexShader), NULL, m_pObjVertShader.GetAddressOf());
	result = m_pDevice->CreateVertexShader(SkyboxVertexShader, sizeof(SkyboxVertexShader), NULL, m_pSkyboxVertShader.GetAddressOf());
	result = m_pDevice->CreateVertexShader(InstancedVertexShader, sizeof(InstancedVertexShader), NULL, m_pInstancedVertShader.GetAddressOf());
	result = m_pDevice->CreatePixelShader(PixelShader, sizeof(PixelShader), NULL, m_pPixelShader.GetAddressOf());
	result = m_pDevice->CreatePixelShader(SkyboxPixelShader, sizeof(SkyboxPixelShader), NULL, m_pSkyboxPixelShader.GetAddressOf());

	//Create RTV
	result = m_pSwapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(m_pBackBufferTexture.GetAddressOf()));
	CD3D11_RENDER_TARGET_VIEW_DESC RTVDesc(D3D11_RTV_DIMENSION_TEXTURE2DMS);
	result = m_pDevice->CreateRenderTargetView(m_pBackBufferTexture.Get(), &RTVDesc, m_pRtv.GetAddressOf());

	//Create viewport
	m_ViewPort.Width = static_cast<float>(BufferWidth);
	m_ViewPort.Height = static_cast<float>(BufferHeight);
	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;
	m_ViewPort.MinDepth = 0.0f;
	m_ViewPort.MaxDepth = 1.0f;

	//Set materials
		//Use texture?
			cubeMaterial.material.useTexture = true;
			floorMaterial.material.useTexture = true;
			pattyMaterial.material.useTexture = true;
			spongeManMaterial.material.useTexture = true;
			spongeManHouseMaterial.material.useTexture = true;
			starManMaterial.material.useTexture = true;
			starManHouseMaterial.material.useTexture = true;
			//teapotMaterial.material.useTexture = true;
			skyboxMaterial.material.useTexture = true;
		//Set specular
			cubeMaterial.material.specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
			floorMaterial.material.specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
			pattyMaterial.material.specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
			spongeManMaterial.material.specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
			starManMaterial.material.specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
			//teapotMaterial.material.specular = XMFLOAT4(2.0f, 2.0f, 2.0f, 1.0f);

	//Set light and button stuff
	pLight = XMFLOAT3(0.0f, 3.0f, 0.0f);
	sLightPos = XMFLOAT3(0.0f, 2.0f, 0.0f);
	sLightDir = XMFLOAT3(-sLightPos.x, -sLightPos.y, -sLightPos.z);
	dLight = XMFLOAT3(0.0f, -5.0f, 0.0f);

	buttonLength = 0.25f;
	lightProperties.globalAmbient = XMFLOAT4(5.0f, 5.0f, 5.0f, 1.0f);
	//lightProperties.globalAmbient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);

	buttonTimer += buttonLength;
}

void DirectXecution::DirectXRun()
{
	timer.Signal();

	//Light toggle stuff
	buttonTimer += (float)timer.Delta();
	LightToggleStuff();

	//Camera update and setting skybox to camera
	utility.UpdateCamera(camera, (float)timer.Delta(), 5.0f, 1.0f);
	skyboxMat = utility.Translate(XMFLOAT3(camera._41, camera._42, camera._43), 0, skyboxMat, false);
	
	//Rotating stuff
	pattyMat = utility.Rotate(XMFLOAT3(0.0f, 1.0f, 0.0f), (float)timer.Delta(), pattyMat);

	//Changing angleY and Near and Far
	AdjZoomAndNearFarCheck(1.0f, 1.0f);

	//Setting const buffer view and proj matrix
	DirectX::XMStoreFloat4x4(&vramData.viewMat, DirectX::XMMatrixTranspose(XMMatrixInverse(nullptr, DirectX::XMLoadFloat4x4(&camera))));
	DirectX::XMStoreFloat4x4(&vramData.projMat, DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(angleY), width / height, nearP, farP)));
	DirectX::XMStoreFloat4x4(&vramDataInstanced.viewMat, DirectX::XMMatrixTranspose(XMMatrixInverse(nullptr, DirectX::XMLoadFloat4x4(&camera))));
	DirectX::XMStoreFloat4x4(&vramDataInstanced.projMat, DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(angleY), width / height, nearP, farP)));

	//Binding depth stencil
	m_pContext->OMSetDepthStencilState(m_pDepthStencilState.Get(), 1);

	//Clearing stencil
	m_pContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

	//Binding RTV
	m_pContext->OMSetRenderTargets(1, m_pRtv.GetAddressOf(), m_pDepthStencilView.Get());

	//Clearing RTV
	m_pContext->ClearRenderTargetView(m_pRtv.Get(), DirectX::Colors::WhiteSmoke);

	//Binding viewport
	m_pContext->RSSetViewports(1, &m_ViewPort);

	//Binding buffers
	ID3D11Buffer* buffers[] = { m_pConstMaterialBuffer.Get(), m_pConstLightBuffer.Get() };
	m_pContext->PSSetConstantBuffers(0, ARRAYSIZE(buffers), buffers);

	//Sending light info
	XMVECTOR cameraPos = { camera._41, camera._42, camera._43, camera._44 };
	XMStoreFloat4(&lightProperties.eyePos, cameraPos);
	m_pContext->UpdateSubresource(m_pConstLightBuffer.Get(), 0, nullptr, &lightProperties, 0, 0);

	//Draw calls
	DrawOBJ(m_pSkyboxVertexBuffer, m_pSkyboxIndexBuffer, m_pSkyboxVertShader, m_pSkyboxPixelShader, m_pSkyboxSrv, skyboxMat, skyboxVerts, skyboxInds, skyboxMaterial);
	m_pContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	DrawOBJ(m_pPattyVertexBuffer, m_pPattyIndexBuffer, m_pObjVertShader, m_pPixelShader, m_pPattySrv, pattyMat, pattyVerts, pattyInds, pattyMaterial);
	DrawOBJ(m_pSpongeManVertexBuffer, m_pSpongeManIndexBuffer, m_pObjVertShader, m_pPixelShader, m_pSpongeManSrv, spongeManMat, spongeManVerts, spongeManInds, spongeManMaterial);
	DrawOBJ(m_pSpongeManHouseVertexBuffer, m_pSpongeManHouseIndexBuffer, m_pObjVertShader, m_pPixelShader, m_pSpongeManHouseSrv, spongeManHouseMat, spongeManHouseVerts, spongeManHouseInds, spongeManHouseMaterial);
	DrawOBJ(m_pStarManVertexBuffer, m_pStarManIndexBuffer, m_pObjVertShader, m_pPixelShader, m_pStarManSrv, starManMat, starManVerts, starManInds, starManMaterial);
	DrawOBJ(m_pStarManHouseVertexBuffer, m_pStarManHouseIndexBuffer, m_pObjVertShader, m_pPixelShader, m_pStarManHouseSrv, starManHouseMat, starManHouseVerts, starManHouseInds, starManHouseMaterial);
	DrawOBJ(m_pFloorVertexBuffer, m_pFloorIndexBuffer, m_pObjVertShader, m_pPixelShader, m_pFloorSrv, floorMat, floorVerts, floorInds, floorMaterial);
	//DrawOBJ(m_pTeapotVertexBuffer, m_pTeapotIndexBuffer, m_pObjVertShader, m_pPixelShader, m_pTeapotSrv, teapotMat, teapotVerts, teapotInds, teapotMaterial);
	DrawCubeInstanced(cubeMats, ARRAYSIZE(cubeMats), cubeMaterial);

	//Display stuff on screen
	m_pSwapChain->Present(1, 0);
}

void DirectXecution::ResizeUpdate(HWND _window)
{
	RECT windowRect;

	GetClientRect(_window, &windowRect);
	width = (float)(windowRect.right - windowRect.left);
	height = (float)(windowRect.bottom - windowRect.top);

	m_pContext->OMSetRenderTargets(0, nullptr, nullptr);
	m_pRtv.Reset();
	m_pDepthStencil.Reset();
	m_pBackBufferTexture.Reset();
	result = m_pSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);

	//Create viewport
	m_ViewPort.Width = static_cast<float>(width);
	m_ViewPort.Height = static_cast<float>(height);
	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;
	m_ViewPort.MinDepth = 0.0f;
	m_ViewPort.MaxDepth = 1.0f;

	//Depth stencil description
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc;
	ZeroMemory(&depthStencilStateDesc, sizeof(depthStencilStateDesc));
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	//Resource
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = NULL;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.Height = (UINT)height;
	depthStencilDesc.Width = (UINT)width;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.MiscFlags = NULL;
	depthStencilDesc.SampleDesc.Count = 4;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;

	//State
	depthStencilStateDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilStateDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilStateDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStencilStateDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilStateDesc.DepthEnable = true;
	depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilStateDesc.StencilEnable = true;
	depthStencilStateDesc.StencilReadMask = 0xFF;
	depthStencilStateDesc.StencilWriteMask = 0xFF;
	depthStencilStateDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilStateDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilStateDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilStateDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//View
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	//Create RTV
	result = m_pSwapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(m_pBackBufferTexture.GetAddressOf()));
	CD3D11_RENDER_TARGET_VIEW_DESC RTVDesc(D3D11_RTV_DIMENSION_TEXTURE2DMS);
	result = m_pDevice->CreateRenderTargetView(m_pBackBufferTexture.Get(), &RTVDesc, m_pRtv.GetAddressOf());

	//Create stencil
	result = m_pDevice->CreateTexture2D(&depthStencilDesc, NULL, m_pDepthStencil.GetAddressOf());
	result = m_pDevice->CreateDepthStencilState(&depthStencilStateDesc, m_pDepthStencilState.GetAddressOf());
	result = m_pDevice->CreateDepthStencilView(m_pDepthStencil.Get(), &depthStencilViewDesc, m_pDepthStencilView.GetAddressOf());
}

//For self-made cube
HRESULT DirectXecution::CreateVertexBuffer()
{
	//Cube vertex buffer description
	D3D11_BUFFER_DESC cubeVertBufferDesc;
	ZeroMemory(&cubeVertBufferDesc, sizeof(cubeVertBufferDesc));
	cubeVertBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	cubeVertBufferDesc.ByteWidth = sizeof(Vertex) * 24;
	cubeVertBufferDesc.CPUAccessFlags = NULL;
	cubeVertBufferDesc.MiscFlags = NULL;
	cubeVertBufferDesc.StructureByteStride = sizeof(Vertex);
	cubeVertBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	//Cube vertex initial data
	D3D11_SUBRESOURCE_DATA cubeVertInitData;
	ZeroMemory(&cubeVertInitData, sizeof(cubeVertInitData));
	cubeVertInitData.pSysMem = cubeVerts;
	cubeVertInitData.SysMemPitch = NULL;
	cubeVertInitData.SysMemSlicePitch = NULL;

	//Create cube buffer
	result = m_pDevice->CreateBuffer(&cubeVertBufferDesc, &cubeVertInitData, m_pCubeVertexBuffer.GetAddressOf());

	return result;
}

//For OBJ files
HRESULT DirectXecution::CreateVertexBuffer(std::vector<VertexOBJ> &_vert, Microsoft::WRL::ComPtr<ID3D11Buffer> &_buffer)
{
	//OBJ vertex buffer description
	D3D11_BUFFER_DESC objVertBufferDesc;
	ZeroMemory(&objVertBufferDesc, sizeof(objVertBufferDesc));
	objVertBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	objVertBufferDesc.ByteWidth = sizeof(VertexOBJ) * (UINT)_vert.size();
	objVertBufferDesc.CPUAccessFlags = NULL;
	objVertBufferDesc.MiscFlags = NULL;
	objVertBufferDesc.StructureByteStride = sizeof(VertexOBJ);
	objVertBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	//OBJ vertex initial data
	D3D11_SUBRESOURCE_DATA objVertInitData;
	ZeroMemory(&objVertInitData, sizeof(objVertInitData));
	objVertInitData.pSysMem = &_vert[0];
	objVertInitData.SysMemPitch = NULL;
	objVertInitData.SysMemSlicePitch = NULL;

	//Create OBJ buffer
	result = m_pDevice->CreateBuffer(&objVertBufferDesc, &objVertInitData, _buffer.GetAddressOf());

	return result;
}

//For OBJ files
HRESULT DirectXecution::CreateIndexBuffer(std::vector<unsigned int> _indVect, Microsoft::WRL::ComPtr<ID3D11Buffer> &_buffer)
{
	//Cube index buffer description
	D3D11_BUFFER_DESC objIndBufferDesc;
	ZeroMemory(&objIndBufferDesc, sizeof(objIndBufferDesc));
	objIndBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	objIndBufferDesc.ByteWidth = sizeof(unsigned int) * (UINT)_indVect.size();
	objIndBufferDesc.CPUAccessFlags = NULL;
	objIndBufferDesc.MiscFlags = NULL;
	objIndBufferDesc.StructureByteStride = sizeof(unsigned int);
	objIndBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	//Cube index initial data
	D3D11_SUBRESOURCE_DATA objIndInitData;
	ZeroMemory(&objIndInitData, sizeof(objIndInitData));
	objIndInitData.pSysMem = &_indVect[0];
	objIndInitData.SysMemPitch = NULL;
	objIndInitData.SysMemSlicePitch = NULL;

	result = m_pDevice->CreateBuffer(&objIndBufferDesc, &objIndInitData, _buffer.GetAddressOf());

	return result;
}

//For self-made cube
HRESULT DirectXecution::CreateIndexBuffer()
{
	//Cube index buffer description
	D3D11_BUFFER_DESC cubeIndBufferDesc;
	ZeroMemory(&cubeIndBufferDesc, sizeof(cubeIndBufferDesc));
	cubeIndBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	cubeIndBufferDesc.ByteWidth = sizeof(int) * 36;
	cubeIndBufferDesc.CPUAccessFlags = NULL;
	cubeIndBufferDesc.MiscFlags = NULL;
	cubeIndBufferDesc.StructureByteStride = sizeof(int);
	cubeIndBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	//Cube index initial data
	D3D11_SUBRESOURCE_DATA cubeIndInitData;
	ZeroMemory(&cubeIndInitData, sizeof(cubeIndInitData));
	cubeIndInitData.pSysMem = cubeInd;
	cubeIndInitData.SysMemPitch = NULL;
	cubeIndInitData.SysMemSlicePitch = NULL;

	result = m_pDevice->CreateBuffer(&cubeIndBufferDesc, &cubeIndInitData, m_pCubeIndexBuffer.GetAddressOf());

	return result;
}

HRESULT DirectXecution::CreateConstBuffer(unsigned int _constBufferNum, Microsoft::WRL::ComPtr<ID3D11Buffer> &_cBuffer)
{
	//Const buffer description
	D3D11_BUFFER_DESC constBufferDesc;
	ZeroMemory(&constBufferDesc, sizeof(constBufferDesc));
	constBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constBufferDesc.CPUAccessFlags = NULL;
	constBufferDesc.MiscFlags = NULL;
	constBufferDesc.StructureByteStride = NULL;
	constBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	//Const buffer initial data
	D3D11_SUBRESOURCE_DATA constBufferInitData;
	ZeroMemory(&constBufferInitData, sizeof(constBufferInitData));
	constBufferInitData.SysMemPitch = NULL;
	constBufferInitData.SysMemSlicePitch = NULL;


	switch (_constBufferNum)
	{
		case MatrixBuffer:
		{
			constBufferDesc.ByteWidth = sizeof(Send_To_VRAM);
			constBufferInitData.pSysMem = &vramData;
		}
		break;

		case InstancedMatrixBuffer:
		{
			constBufferDesc.ByteWidth = sizeof(Send_To_VRAM_Instanced);
			constBufferInitData.pSysMem = &vramDataInstanced;
		}
		break;

		case MaterialBuffer:
		{
			constBufferDesc.ByteWidth = sizeof(MaterialProperties);
			constBufferInitData.pSysMem = &materialProperties;
		}
		break;

		case LightBuffer:
		{
			constBufferDesc.ByteWidth = sizeof(LightProperties);
			constBufferInitData.pSysMem = &lightProperties;
		}
	}

	result = m_pDevice->CreateBuffer(&constBufferDesc, &constBufferInitData, _cBuffer.GetAddressOf());
	return result;
}

HRESULT DirectXecution::CreateDepthStencil()
{
	//Depth stencil description
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc;
	ZeroMemory(&depthStencilStateDesc, sizeof(depthStencilStateDesc));
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	//Resource
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = NULL;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.Height = BufferHeight;
	depthStencilDesc.Width = BufferWidth;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.MiscFlags = NULL;
	depthStencilDesc.SampleDesc.Count = 4;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;

	//State
	depthStencilStateDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilStateDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilStateDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStencilStateDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilStateDesc.DepthEnable = true;
	depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilStateDesc.StencilEnable = true;
	depthStencilStateDesc.StencilReadMask = 0xFF;
	depthStencilStateDesc.StencilWriteMask = 0xFF;
	depthStencilStateDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilStateDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilStateDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilStateDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//View
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	result = m_pDevice->CreateTexture2D(&depthStencilDesc, NULL, m_pDepthStencil.GetAddressOf());
	if (result != S_OK)
		return result;
	result = m_pDevice->CreateDepthStencilState(&depthStencilStateDesc, m_pDepthStencilState.GetAddressOf());
	if (result != S_OK)
		return result;
	result = m_pDevice->CreateDepthStencilView(m_pDepthStencil.Get(), &depthStencilViewDesc, m_pDepthStencilView.GetAddressOf());

	return result;
}

HRESULT DirectXecution::CreateCubeLayout()
{
	//Setup layout
	D3D11_INPUT_ELEMENT_DESC cubeVertShaderLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMALS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	//Create input layout
	result = m_pDevice->CreateInputLayout(cubeVertShaderLayout, ARRAYSIZE(cubeVertShaderLayout), VertexShader, sizeof(VertexShader), m_pCubeInputLayout.GetAddressOf());

	return result;
}

HRESULT DirectXecution::CreateOBJLayout()
{
	//Setup layout
	D3D11_INPUT_ELEMENT_DESC objVertShaderLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMALS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	//Create input layout
	result = m_pDevice->CreateInputLayout(objVertShaderLayout, ARRAYSIZE(objVertShaderLayout), objVertexShader, sizeof(objVertexShader), m_pObjInputLayout.GetAddressOf());

	return result;
}

void DirectXecution::DrawCube(MaterialProperties _material)
{
	UINT cubeVertStride = sizeof(Vertex);
	UINT cubeVertOffset = 0;
	UINT cubeIndOffset = 0;

	m_pContext->VSSetConstantBuffers(0, 1, m_pConstMatrixBuffer.GetAddressOf());

	//Send matrix
	DirectX::XMStoreFloat4x4(&vramData.worldMat, cubeMat);
	m_pContext->UpdateSubresource(m_pConstMatrixBuffer.Get(), 0, NULL, &vramData, 0, 0);

	//Send material
	m_pContext->UpdateSubresource(m_pConstMaterialBuffer.Get(), 0, nullptr, &_material, 0, 0);

	//Binding topology
	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Binding input layout
	m_pContext->IASetInputLayout(m_pCubeInputLayout.Get());

	//Binding shaders
	m_pContext->VSSetShader(m_pCubeVertShader.Get(), 0, 0);
	m_pContext->PSSetShader(m_pPixelShader.Get(), 0, 0);

	//Binding SRV
	m_pContext->PSSetShaderResources(0, 1, m_pCubeSrv.GetAddressOf());

	m_pContext->IASetVertexBuffers(0, 1, m_pCubeVertexBuffer.GetAddressOf(), &cubeVertStride, &cubeVertOffset);
	m_pContext->IASetIndexBuffer(m_pCubeIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, cubeIndOffset);
	m_pContext->DrawIndexed(ARRAYSIZE(cubeInd), 0, 0);
}

void DirectXecution::DrawOBJ(Microsoft::WRL::ComPtr<ID3D11Buffer> &_vBuffer, Microsoft::WRL::ComPtr<ID3D11Buffer> &_iBuffer, Microsoft::WRL::ComPtr<ID3D11VertexShader> &_vertShader, Microsoft::WRL::ComPtr<ID3D11PixelShader> &_pixShader, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> &_srv, XMMATRIX &_mat, std::vector<VertexOBJ> _verts, std::vector<unsigned int> _inds, MaterialProperties _material)
{
	UINT objVertStride = sizeof(VertexOBJ);
	UINT objVertOffset = 0;
	UINT objIndOffset = 0;

	m_pContext->VSSetConstantBuffers(0, 1, m_pConstMatrixBuffer.GetAddressOf());

	//Sending matrix
	DirectX::XMStoreFloat4x4(&vramData.worldMat, _mat);
	m_pContext->UpdateSubresource(m_pConstMatrixBuffer.Get(), 0, NULL, &vramData, 0, 0);

	//Send material
	m_pContext->UpdateSubresource(m_pConstMaterialBuffer.Get(), 0, nullptr, &_material, 0, 0);

	//Binding topology
	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Binding input layout
	m_pContext->IASetInputLayout(m_pObjInputLayout.Get());

	//Binding shaders
	m_pContext->VSSetShader(_vertShader.Get(), 0, 0);
	m_pContext->PSSetShader(_pixShader.Get(), 0, 0);

	//Binding SRV
	if (_srv != nullptr)
		m_pContext->PSSetShaderResources(0, 1, _srv.GetAddressOf());

	m_pContext->IASetVertexBuffers(0, 1, _vBuffer.GetAddressOf(), &objVertStride, &objVertOffset);
	m_pContext->IASetIndexBuffer(_iBuffer.Get(), DXGI_FORMAT_R32_UINT, objIndOffset);
	m_pContext->DrawIndexed((UINT)_inds.size(), 0, 0);
}

void DirectXecution::DrawCubeInstanced(XMMATRIX _mats[], unsigned int _matSize, MaterialProperties _material)
{
	UINT cubeVertStride = sizeof(Vertex);
	UINT cubeVertOffset = 0;
	UINT cubeIndOffset = 0;

	m_pContext->VSSetConstantBuffers(0, 1, m_pConstInstancedMatrixBuffer.GetAddressOf());

	//Set up world matricies
	for (unsigned int i = 0; i < _matSize; ++i)
	{
		DirectX::XMStoreFloat4x4(&vramDataInstanced.worldMat[i], _mats[i]);
	}

	//Send matricies
	m_pContext->UpdateSubresource(m_pConstInstancedMatrixBuffer.Get(), 0, NULL, &vramDataInstanced, 0, 0);

	//Send material
	m_pContext->UpdateSubresource(m_pConstMaterialBuffer.Get(), 0, nullptr, &_material, 0, 0);

	//Binding topology
	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Binding input layout
	m_pContext->IASetInputLayout(m_pCubeInputLayout.Get());

	//Binding shaders
	m_pContext->VSSetShader(m_pInstancedVertShader.Get(), 0, 0);
	m_pContext->PSSetShader(m_pPixelShader.Get(), 0, 0);

	//Binding SRV
	m_pContext->PSSetShaderResources(0, 1, m_pCubeSrv.GetAddressOf());

	m_pContext->IASetVertexBuffers(0, 1, m_pCubeVertexBuffer.GetAddressOf(), &cubeVertStride, &cubeVertOffset);
	m_pContext->IASetIndexBuffer(m_pCubeIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, cubeIndOffset);
	m_pContext->DrawIndexedInstanced(ARRAYSIZE(cubeInd), _matSize, 0, 0, 0);
}

void DirectXecution::AdjZoomAndNearFarCheck(float _angleVal, float _nearFarVal)
{
	if (GetAsyncKeyState('Z') & 0x1)
	{
		if (angleY > 10.0f)
			angleY -= _angleVal;
	}

	if (GetAsyncKeyState('X') & 0x1)
	{
		if (angleY < 120.0f)
			angleY += _angleVal;
	}

	if (GetAsyncKeyState('R') && GetAsyncKeyState(VK_LSHIFT))
	{
		angleY = 55.0f;
	}
}

void DirectXecution::LightSetup(XMFLOAT3 _pos, XMFLOAT3 _dir, XMVECTORF32 _color, unsigned int _type, XMFLOAT3 _CLQAttenuation, float _spotAngle, unsigned int _slot)
{
	Light light;
	light.enabled = true;
	light.lightType = _type;
	light.color = XMFLOAT4(_color);
	light.spotAngle = XMConvertToRadians(_spotAngle);
	light.attenuation = { _CLQAttenuation.x, _CLQAttenuation.y, _CLQAttenuation.z };
	XMFLOAT4 LightPos = XMFLOAT4(_pos.x, _pos.y, _pos.z, 1.0f);
	light.pos = LightPos;
	XMVECTOR LightDir = XMVectorSet(_dir.x, _dir.y, _dir.z, 0.0f);
	XMStoreFloat4(&light.dir, LightDir);

	lightProperties.lights[_slot] = light;
}

void DirectXecution::CameraSetup(XMVECTOR _eyePos, XMVECTOR _focusPos, XMVECTOR _upDir)
{
	XMStoreFloat4x4(&camera, XMMatrixInverse(nullptr, XMMatrixLookAtLH(_eyePos, _focusPos, _upDir)));
}

void DirectXecution::LightToggleStuff()
{
	//Turning lights on and off
	if (GetAsyncKeyState('1') && !lightProperties.lights[DirectionalLight].enabled && buttonTimer > buttonLength)
	{
		LightSetup(dLight, XMFLOAT3(0.0f, 0.0f, 0.0f), Colors::Cyan, DirectionalLight, XMFLOAT3(1.0f, 0.08f, 0.0f), 25.0f, 0);
		buttonTimer = 0.0f;
	}
	else if (GetAsyncKeyState('1') && lightProperties.lights[DirectionalLight].enabled && buttonTimer > buttonLength)
	{
		LightSetup(dLight, XMFLOAT3(0.0f, 0.0f, 0.0f), Colors::Transparent, DirectionalLight, XMFLOAT3(1.0f, 0.08f, 0.0f), 25.0f, 0);
		lightProperties.lights[DirectionalLight].enabled = false;
		buttonTimer = 0.0f;
	}
	if (GetAsyncKeyState('2') && !lightProperties.lights[PointLight].enabled && buttonTimer > buttonLength)
	{
		LightSetup(pLight, XMFLOAT3(0.0f, -1.0f, 0.0f), Colors::Green, PointLight, XMFLOAT3(1.0f, 0.08f, 0.0f), 25.0f, 1);
		buttonTimer = 0.0f;
	}
	else if (GetAsyncKeyState('2') && lightProperties.lights[PointLight].enabled && buttonTimer > buttonLength)
	{
		LightSetup(pLight, XMFLOAT3(0.0f, -1.0f, 0.0f), Colors::Transparent, PointLight, XMFLOAT3(1.0f, 0.08f, 0.0f), 25.0f, 1);
		lightProperties.lights[PointLight].enabled = false;
		buttonTimer = 0.0f;
	}
	if (GetAsyncKeyState('3') && !lightProperties.lights[SpotLight].enabled && buttonTimer > buttonLength)
	{
		LightSetup(sLightPos, sLightDir, Colors::Red, SpotLight, XMFLOAT3(1.0f, 0.08f, 0.0f), 45.0f, 2);
		buttonTimer = 0.0f;
	}
	else if (GetAsyncKeyState('3') && lightProperties.lights[SpotLight].enabled && buttonTimer > buttonLength)
	{
		LightSetup(sLightPos, sLightDir, Colors::Transparent, SpotLight, XMFLOAT3(1.0f, 0.08f, 0.0f), 45.0f, 2);
		lightProperties.lights[SpotLight].enabled = false;
		buttonTimer = 0.0f;
	}

	//Moving lights if they are turned on
	if (lightProperties.lights[PointLight].enabled)
	{	
		if (GetAsyncKeyState('T') & 0x1)
			--pLight.z;
		else if (GetAsyncKeyState('F') & 0x1)
			++pLight.x;
		else if (GetAsyncKeyState('G') & 0x1)
			++pLight.z;
		else if (GetAsyncKeyState('H') & 0x1)
			--pLight.x;
		else if (GetAsyncKeyState('J') & 0x1)
			--pLight.y;
		else if (GetAsyncKeyState('U') & 0x1)
			++pLight.y;
		else if (GetAsyncKeyState('R') & 0x1)
			pLight = XMFLOAT3(0.0f, 3.0f, 0.0f);

		LightSetup(pLight, XMFLOAT3(0.0, 0.0f, 0.0f), Colors::Green, PointLight, XMFLOAT3(1.0f, 0.08f, 0.0f), 25.0f, 1);
	}

	if (lightProperties.lights[DirectionalLight].enabled)
	{
		if (GetAsyncKeyState('T') & 0x1)
			--dLight.z;
		else if (GetAsyncKeyState('F') & 0x1)
			++dLight.x;
		else if (GetAsyncKeyState('G') & 0x1)
			++dLight.z;
		else if (GetAsyncKeyState('H') & 0x1)
			--dLight.x;
		else if (GetAsyncKeyState('J') & 0x1)
			--dLight.y;
		else if (GetAsyncKeyState('U') & 0x1)
			++dLight.y;
		else if (GetAsyncKeyState('R') & 0x1)
			dLight = XMFLOAT3(0.0f, -5.0f, 0.0f);

		LightSetup(XMFLOAT3(0.0, 0.0f, 0.0f), dLight, Colors::Cyan, DirectionalLight, XMFLOAT3(1.0f, 0.08f, 0.0f), 25.0f, 0);
	}

	if (lightProperties.lights[SpotLight].enabled)
	{
		if (GetAsyncKeyState('T') & 0x1)
			--sLightPos.z;
		else if (GetAsyncKeyState('F') & 0x1)
			++sLightPos.x;
		else if (GetAsyncKeyState('G') & 0x1)
			++sLightPos.z;
		else if (GetAsyncKeyState('H') & 0x1)
			--sLightPos.x;
		else if (GetAsyncKeyState('J') & 0x1)
			--sLightPos.y;
		else if (GetAsyncKeyState('U') & 0x1)
			++sLightPos.y;
		else if (GetAsyncKeyState('R') & 0x1)
		{
			sLightPos = XMFLOAT3(0.0f, 2.0f, 0.0f);
			sLightDir = XMFLOAT3(-sLightPos.x, -sLightPos.y, -sLightPos.z);
		}

		if (GetAsyncKeyState(VK_NUMPAD8) & 0x1)
			--sLightDir.z;
		else if (GetAsyncKeyState(VK_NUMPAD4) & 0x1)
			++sLightDir.x;
		else if (GetAsyncKeyState(VK_NUMPAD2) & 0x1)
			++sLightDir.z;
		else if (GetAsyncKeyState(VK_NUMPAD6) & 0x1)
			--sLightDir.x;
		else if (GetAsyncKeyState(VK_NUMPAD3) & 0x1)
			--sLightDir.y;
		else if (GetAsyncKeyState(VK_NUMPAD9) & 0x1)
			++sLightDir.y;

		LightSetup(sLightPos, sLightDir, Colors::Red, SpotLight, XMFLOAT3(1.0f, 0.08f, 0.0f), 25.0f, 2);
	}
}

void DirectXecution::DX11Setup(HWND _window)
{
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT driverCount = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};
	UINT featureCount = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC swapDesc;
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapDesc.BufferCount = 1;
	swapDesc.BufferDesc.Width = BufferWidth;
	swapDesc.BufferDesc.Height = BufferHeight;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.SampleDesc.Count = 4;
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapDesc.Windowed = true;
	swapDesc.Flags = NULL;
	swapDesc.OutputWindow = _window;

	for (unsigned int i = 0; i < driverCount; ++i)
	{
		result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL,
			featureLevels, featureCount, D3D11_SDK_VERSION, &swapDesc, m_pSwapChain.GetAddressOf(), m_pDevice.GetAddressOf(),
			&m_FeatureLevel, m_pContext.GetAddressOf());

		if (SUCCEEDED(result))
		{
			m_DriverType = driverTypes[i];
			break;
		}
	}
}
