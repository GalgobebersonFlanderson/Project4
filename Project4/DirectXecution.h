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
	std::vector<VertexOBJ>								floorVerts;
	std::vector<unsigned int>							floorInds;
	std::vector<VertexOBJ>								teapotVerts;
	std::vector<unsigned int>							teapotInds;
	std::vector<VertexOBJ>								skyboxVerts;
	std::vector<unsigned int>							skyboxInds;
	float												angleY, nearP, farP, width, height;
	float												buttonTimer, buttonLength;
	float												emissiveVal;
	bool												increaseEmissiveVal = true;
	XMFLOAT3											sLight, pLight, dLight;

	//Matricies
	XMMATRIX											cubeMat = XMMatrixIdentity();
	XMMATRIX											pattyMat = XMMatrixIdentity();
	XMMATRIX											floorMat = XMMatrixIdentity();
	XMMATRIX											teapotMat = XMMatrixIdentity();
	XMMATRIX											skyboxMat = XMMatrixIdentity();

	//Materials
	MaterialProperties									cubeMaterial;
	MaterialProperties									pattyMaterial;
	MaterialProperties									teapotMaterial;
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
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pFloorVertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pTeapotVertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pSkyboxVertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pCubeIndexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pPattyIndexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pFloorIndexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pSkyboxIndexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pTeapotIndexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pConstMatrixBuffer = nullptr;
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
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_pTeapotSrv = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_pFloorSrv = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_pSkyboxSrv = nullptr;

	//Resources
	Microsoft::WRL::ComPtr<ID3D11Resource>				m_pResource = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				m_pBackBufferTexture = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				m_pDepthStencil = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				m_pBrickTexture = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				m_pPattyTexture = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				m_pTeapotTexture = nullptr;
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
	void DrawOBJ(Microsoft::WRL::ComPtr<ID3D11Buffer> &_vBuffer, Microsoft::WRL::ComPtr<ID3D11Buffer> &_iBuffer, Microsoft::WRL::ComPtr<ID3D11VertexShader> &_vertShader, Microsoft::WRL::ComPtr<ID3D11PixelShader> &_pixShader, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> &_srv, XMMATRIX &_mat, std::vector<VertexOBJ> _verts, std::vector<unsigned int> _inds, MaterialProperties _material);
	void DrawOBJInstanced(Microsoft::WRL::ComPtr<ID3D11Buffer> &_vBuffer, Microsoft::WRL::ComPtr<ID3D11Buffer> &_iBuffer, Microsoft::WRL::ComPtr<ID3D11VertexShader> &_vertShader, Microsoft::WRL::ComPtr<ID3D11PixelShader> &_pixShader, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> &_srv, XMMATRIX _mat[], unsigned int _matSize, std::vector<VertexOBJ> _verts, std::vector<unsigned int> _inds, MaterialProperties _material);
	void AdjZoomAndNearFarCheck(float _angleVal, float _nearFarVal);
	void LightSetup(XMFLOAT3 _pos, XMFLOAT3 _dir, XMVECTORF32 _color, unsigned int _type, XMFLOAT3 _CLQAttenuation, float _spotAngle, unsigned int _slot);
	void CameraSetup(XMVECTOR _eyePos, XMVECTOR _focusPos, XMVECTOR _upDir);
	HRESULT CreateVertexBuffer();
	HRESULT CreateVertexBuffer(std::vector<VertexOBJ> &_vertVect, Microsoft::WRL::ComPtr<ID3D11Buffer> &_buffer);
	HRESULT CreateIndexBuffer(std::vector<unsigned int> _indVect, Microsoft::WRL::ComPtr<ID3D11Buffer> &_buffer);
	HRESULT CreateIndexBuffer();
	HRESULT CreateConstBuffer(unsigned int _constBufferNum, Microsoft::WRL::ComPtr<ID3D11Buffer> &_cBuffer);
	HRESULT CreateDepthStencil();
	HRESULT CreateCubeLayout();
	HRESULT CreateOBJLayout();
};

