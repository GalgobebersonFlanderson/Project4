#pragma once
class DirectXecution
{

private:
	//Generic Variables
	UsefulStuff											utility;
	XMFLOAT4X4											camera;
	XTime												timer;
	UINT												cubeInd[36];
	std::vector<VertexOBJ>								pattyVerts;
	std::vector<unsigned int>							pattyInds;
	std::vector<VertexOBJ>								spongeManVerts;
	std::vector<unsigned int>							spongeManInds;
	std::vector<VertexOBJ>								spongeManHouseVerts;
	std::vector<unsigned int>							spongeManHouseInds;
	std::vector<VertexOBJ>								starManVerts;
	std::vector<unsigned int>							starManInds;
	std::vector<VertexOBJ>								starManHouseVerts;
	std::vector<unsigned int>							starManHouseInds;
	std::vector<VertexOBJ>								floorVerts;
	std::vector<unsigned int>							floorInds;
	//std::vector<VertexOBJ>							teapotVerts;
	//std::vector<unsigned int>							teapotInds;
	std::vector<VertexOBJ>								skyboxVerts;
	std::vector<unsigned int>							skyboxInds;
	float												angleY, nearP, farP, width, height;
	float												buttonTimer, buttonLength;
	//float												emissiveVal;
	//bool												increaseEmissiveVal = true;
	XMFLOAT3											sLightPos, sLightDir, pLight, dLight;

	//Matricies
	XMMATRIX											cubeMat = XMMatrixIdentity();
	XMMATRIX											pattyMat = XMMatrixIdentity();
	XMMATRIX											spongeManMat = XMMatrixIdentity();
	XMMATRIX											spongeManHouseMat = XMMatrixIdentity();
	XMMATRIX											starManMat = XMMatrixIdentity();
	XMMATRIX											starManHouseMat = XMMatrixIdentity();
	XMMATRIX											floorMat = XMMatrixIdentity();
	//XMMATRIX											teapotMat = XMMatrixIdentity();
	XMMATRIX											skyboxMat = XMMatrixIdentity();
	XMMATRIX											cubeMats[4];

	//Materials
	MaterialProperties									cubeMaterial;
	MaterialProperties									pattyMaterial;
	MaterialProperties									spongeManMaterial;
	MaterialProperties									spongeManHouseMaterial;
	MaterialProperties									starManMaterial;
	MaterialProperties									starManHouseMaterial;
	//MaterialProperties								teapotMaterial;
	MaterialProperties									floorMaterial;
	MaterialProperties									skyboxMaterial;

	//Struct defines
	Vertex												platformVerts[6];
	Vertex												cubeVerts[24];
	LightProperties										lightProperties;
	MaterialProperties									materialProperties;
	RectF												cubeRect;
	Send_To_VRAM										vramData;
	Send_To_VRAM_Instanced								vramDataInstanced;

	//DirectX variables
	Microsoft::WRL::ComPtr<ID3D11Device>				m_pDevice = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			m_pContext = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain>				m_pSwapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			m_pCubeInputLayout = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			m_pObjInputLayout = nullptr;
	D3D_DRIVER_TYPE										m_DriverType;
	D3D_FEATURE_LEVEL									m_FeatureLevel;
	D3D11_VIEWPORT										m_ViewPort;
	HRESULT												result;

	//DirectX buffers
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pCubeVertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pPattyVertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pSpongeManVertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pSpongeManHouseVertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pStarManVertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pStarManHouseVertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pFloorVertexBuffer = nullptr;
	//Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pTeapotVertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pSkyboxVertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pCubeIndexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pPattyIndexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pSpongeManIndexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pSpongeManHouseIndexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pStarManIndexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pStarManHouseIndexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pFloorIndexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pSkyboxIndexBuffer = nullptr;
	//Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pTeapotIndexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pConstMatrixBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pConstInstancedMatrixBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pConstMaterialBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pConstLightBuffer = nullptr;

	//DirectX shaders
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			m_pCubeVertShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			m_pObjVertShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			m_pSkyboxVertShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			m_pInstancedVertShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			m_pPixelShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			m_pSkyboxPixelShader = nullptr;

	//Views
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		m_pRtv = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_pCubeSrv = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_pPattySrv = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_pSpongeManSrv = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_pSpongeManHouseSrv = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_pStarManSrv = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_pStarManHouseSrv = nullptr;
	//Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_pTeapotSrv = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_pFloorSrv = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_pSkyboxSrv = nullptr;

	//Resources
	Microsoft::WRL::ComPtr<ID3D11Resource>				m_pResource = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				m_pBackBufferTexture = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				m_pDepthStencil = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				m_pBrickTexture = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				m_pPattyTexture = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				m_pSpongeManTexture = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				m_pSpongeManHouseTexture = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				m_pStarManTexture = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				m_pStarManHouseTexture = nullptr;
	//Microsoft::WRL::ComPtr<ID3D11Texture2D>				m_pTeapotTexture = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				m_pFloorTexture = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				m_pSkyboxTexture = nullptr;

	//Depth stencil
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState>		m_pDepthStencilState = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>		m_pDepthStencilView = nullptr;

public:
	DirectXecution();
	~DirectXecution();
	void DirectXInit(HWND _window);
	void DirectXRun();
	void ResizeUpdate(HWND _window);
	void DX11Setup(HWND _window);
	void DrawCube(MaterialProperties _material);
	void DrawCubeInstanced(XMMATRIX _mats[], unsigned int _matSize, MaterialProperties _material);
	void DrawOBJ(Microsoft::WRL::ComPtr<ID3D11Buffer> &_vBuffer, Microsoft::WRL::ComPtr<ID3D11Buffer> &_iBuffer, Microsoft::WRL::ComPtr<ID3D11VertexShader> &_vertShader, Microsoft::WRL::ComPtr<ID3D11PixelShader> &_pixShader, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> &_srv, XMMATRIX &_mat, std::vector<VertexOBJ> _verts, std::vector<unsigned int> _inds, MaterialProperties _material);
	void AdjZoomAndNearFarCheck(float _angleVal, float _nearFarVal);
	void LightSetup(XMFLOAT3 _pos, XMFLOAT3 _dir, XMVECTORF32 _color, unsigned int _type, XMFLOAT3 _CLQAttenuation, float _spotAngle, unsigned int _slot);
	void CameraSetup(XMVECTOR _eyePos, XMVECTOR _focusPos, XMVECTOR _upDir);
	void LightToggleStuff();
	HRESULT CreateVertexBuffer();
	HRESULT CreateVertexBuffer(std::vector<VertexOBJ> &_vertVect, Microsoft::WRL::ComPtr<ID3D11Buffer> &_buffer);
	HRESULT CreateIndexBuffer(std::vector<unsigned int> _indVect, Microsoft::WRL::ComPtr<ID3D11Buffer> &_buffer);
	HRESULT CreateIndexBuffer();
	HRESULT CreateConstBuffer(unsigned int _constBufferNum, Microsoft::WRL::ComPtr<ID3D11Buffer> &_cBuffer);
	HRESULT CreateDepthStencil();
	HRESULT CreateCubeLayout();
	HRESULT CreateOBJLayout();
};

