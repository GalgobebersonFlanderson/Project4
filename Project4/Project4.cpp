// Project4.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Project4.h"

#pragma comment(lib, "d3d11.lib")

#define MAX_LOADSTRING 100
#define BufferWidth 1000
#define BufferHeight 950

// Generic Variables
UsefulStuff											utility;
UINT												cubeInd[36];

// Struct defines
Vertex												platformVerts[6];
RectF												cubeRect;

// Struct defines
Vertex												cubeVerts[24];

// Global DirectX variables
Microsoft::WRL::ComPtr<ID3D11Device>				m_pDevice = nullptr;
Microsoft::WRL::ComPtr<ID3D11DeviceContext>			m_pContext = nullptr;
Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		m_pRtv = nullptr;
Microsoft::WRL::ComPtr<IDXGISwapChain>				m_pSwapChain = nullptr;
Microsoft::WRL::ComPtr<ID3D11InputLayout>			m_pInputLayout = nullptr;
D3D_DRIVER_TYPE										m_DriverType;
D3D_FEATURE_LEVEL									m_FeatureLevel;
D3D11_VIEWPORT										m_ViewPort;

//DirectX buffers
Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pCubeVertexBuffer = nullptr;
Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pCubeIndexBuffer = nullptr;
Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pConstBuffer = nullptr;

//DirectX shaders
Microsoft::WRL::ComPtr<ID3D11VertexShader>			m_pVertexShader = nullptr;
Microsoft::WRL::ComPtr<ID3D11PixelShader>			m_pPixelShader = nullptr;

//Resources
Microsoft::WRL::ComPtr<ID3D11Resource>				m_pResource = nullptr;
Microsoft::WRL::ComPtr<ID3D11Texture2D>				m_pBackBufferTexture = nullptr;


// Global variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int, HWND&);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROJECT4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
	HWND window;
    if (!InitInstance (hInstance, nCmdShow, window))
    {
        return FALSE;
    }

	//Cube Setup
	cubeRect.left = -0.5f;
	cubeRect.right = 0.5f;
	cubeRect.top = 0.5f;
	cubeRect.bottom = -0.5f;
	utility.GenerateCubeVertsAndIndices(cubeVerts, 0.5f, cubeRect, cubeInd);

	// Initialize DirectX11
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
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapDesc.Windowed = true;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.Flags = NULL;
	swapDesc.OutputWindow = window;

	HRESULT result;
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

	//Cube vertex buffer description
	D3D11_BUFFER_DESC cubeVertBufferDesc;
	cubeVertBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	cubeVertBufferDesc.ByteWidth = sizeof(Vertex) * 24;
	cubeVertBufferDesc.CPUAccessFlags = NULL;
	cubeVertBufferDesc.MiscFlags = NULL;
	cubeVertBufferDesc.StructureByteStride = sizeof(Vertex);
	cubeVertBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	//Cube vertex initial data
	D3D11_SUBRESOURCE_DATA cubeVertInitData;
	cubeVertInitData.pSysMem = cubeVerts;
	cubeVertInitData.SysMemPitch = NULL;
	cubeVertInitData.SysMemSlicePitch = NULL;

	//Cube index buffer description
	D3D11_BUFFER_DESC cubeIndBufferDesc;
	cubeIndBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	cubeIndBufferDesc.ByteWidth = sizeof(int) * 36;
	cubeIndBufferDesc.CPUAccessFlags = NULL;
	cubeIndBufferDesc.MiscFlags = NULL;
	cubeIndBufferDesc.StructureByteStride = sizeof(int);
	cubeIndBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	//Cube index initial data
	D3D11_SUBRESOURCE_DATA cubeIndInitData;
	cubeIndInitData.pSysMem = cubeInd;
	cubeIndInitData.SysMemPitch = NULL;
	cubeIndInitData.SysMemSlicePitch = NULL;

	//Create buffers
	result = m_pDevice->CreateBuffer(&cubeVertBufferDesc, &cubeVertInitData, m_pCubeVertexBuffer.GetAddressOf());
	result = m_pDevice->CreateBuffer(&cubeIndBufferDesc, &cubeIndInitData, m_pCubeIndexBuffer.GetAddressOf());

	// Create shaders
	result = m_pDevice->CreateVertexShader(VertexShader, sizeof(VertexShader), NULL, m_pVertexShader.GetAddressOf());
	result = m_pDevice->CreatePixelShader(PixelShader, sizeof(PixelShader), NULL, m_pPixelShader.GetAddressOf());
	
	// Setup layout
	D3D11_INPUT_ELEMENT_DESC vertexShaderLayout[] = 
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMALS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"UV", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	
	// Create input layout
	result = m_pDevice->CreateInputLayout(vertexShaderLayout, ARRAYSIZE(vertexShaderLayout), VertexShader, sizeof(VertexShader), m_pInputLayout.GetAddressOf());

	// Create RTV
	result = m_pSwapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(m_pBackBufferTexture.GetAddressOf()));
	CD3D11_RENDER_TARGET_VIEW_DESC RTVDesc(D3D11_RTV_DIMENSION_TEXTURE2D);
	result = m_pDevice->CreateRenderTargetView(m_pBackBufferTexture.Get(), &RTVDesc, m_pRtv.GetAddressOf());

	// Binding RTV
	m_pContext->OMSetRenderTargets(1, m_pRtv.GetAddressOf(), nullptr);

	// Create viewport
	m_ViewPort.Width = static_cast<float>(BufferWidth);
	m_ViewPort.Height = static_cast<float>(BufferHeight);
	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;
	m_ViewPort.MinDepth = 0.0f;
	m_ViewPort.MaxDepth = 1.0f;

	//Binding viewport
	m_pContext->RSSetViewports(1, &m_ViewPort);

	//Binding buffers
	UINT cubeVertStride = sizeof(Vertex);
	UINT cubeVertOffset = 0;
	UINT cubeIndOffset = 0;
	m_pContext->IASetVertexBuffers(0, 1, m_pCubeVertexBuffer.GetAddressOf(), &cubeVertStride, &cubeVertOffset);
	m_pContext->IASetIndexBuffer(m_pCubeIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, cubeIndOffset);

	//Binding shaders
	m_pContext->VSSetShader(m_pVertexShader.Get(), 0, 0);
	m_pContext->PSSetShader(m_pPixelShader.Get(), 0, 0);

	//Binding input layout
	m_pContext->IASetInputLayout(m_pInputLayout.Get());

	//Binding topology
	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT4));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
		// Window stuff
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

		// Clearing RTV
		m_pContext->ClearRenderTargetView(m_pRtv.Get(), DirectX::Colors::Blue);

		//Draw
		m_pContext->Draw(24, 0);

		// Display stuff on screen
		m_pSwapChain->Present(0, 0);
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT4));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROJECT4);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, HWND& h)
{
   hInst = hInstance; // Store instance handle in our global variable

   h = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, BufferWidth, BufferHeight, nullptr, nullptr, hInstance, nullptr);

   if (!h)
   {
      return FALSE;
   }

   ShowWindow(h, nCmdShow);
   UpdateWindow(h);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
