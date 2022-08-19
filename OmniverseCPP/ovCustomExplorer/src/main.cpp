
#if defined(__WIN32__) || defined(_WIN32)
# include <windows.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/imgui_impl_dx11.h>
#include <d3d11.h>
#endif

#include <string>

static ImVec4 base = ImVec4(0.502f, 0.075f, 0.256f, 1.0f);
static ImVec4 bg = ImVec4(0.200f, 0.220f, 0.270f, 1.0f);
static ImVec4 text = ImVec4(0.860f, 0.930f, 0.890f, 1.0f);
static float high_val = 0.8f;
static float mid_val = 0.5f;
static float low_val = 0.3f;
static float window_offset = -0.2f;

static ID3D11Device* g_pd3dDevice = NULL;
static ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
static IDXGISwapChain* g_pSwapChain = NULL;
static ID3D11RenderTargetView* g_mainRenderTargetView = NULL;

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
void sendReport(const std::string& path);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int
main(int argc, char* argv[]) {
  ImVec2 windowSize(1024, 620);
  ImVec2 windowPos(200, 100);
  ImVec2 buttonSize(450, 50);
  std::string windowTitle = "Cyllene Engine Crash Handler";
  WNDCLASSEXA wc = { sizeof(WNDCLASSEXA),
                     CS_CLASSDC,
                     WndProc,
                     0L,
                     0L,
                     GetModuleHandle(nullptr),
                     nullptr,
                     nullptr,
                     nullptr,
                     nullptr,
                     windowTitle.c_str(),
                     nullptr };
  ::RegisterClassExA(&wc);
  HWND hwnd = ::CreateWindowA(wc.lpszClassName,
                              windowTitle.c_str(),
                              WS_POPUP |
                                WS_SYSMENU |
                                WS_MAXIMIZEBOX |
                                WS_OVERLAPPED |
                                WS_MINIMIZEBOX,
                              windowPos.x,
                              windowPos.y,
                              windowSize.x,
                              windowSize.y,
                              nullptr,
                              nullptr,
                              wc.hInstance,
                              nullptr);

  // Initialize Direct3D
  if (!CreateDeviceD3D(hwnd)) {
    CleanupDeviceD3D();
    ::UnregisterClassA(wc.lpszClassName, wc.hInstance);
    return 1;
  }

  // Show the window
  ::ShowWindow(hwnd, SW_SHOWDEFAULT);
  ::UpdateWindow(hwnd);

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  ImGuiIO& io = ImGui::GetIO();
  (void)io;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  

  // Setup Platform/Renderer backends
  ImGui_ImplWin32_Init(hwnd);
  ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

  // Our state
  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 0.00f);
  
  // Main loop
  bool done = false;
  bool shouldDrag = false;
  bool alwaysOpen = true;

  while (!done)
  {
    MSG msg;
    while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
    {
      ::TranslateMessage(&msg);
      ::DispatchMessage(&msg);
      if (msg.message == WM_QUIT)
        done = true;
    }
    if (done) {
      break;
    }

    // Start the Dear ImGui frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    {

      ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y));
      ImGui::SetNextWindowPos(ImVec2(0, 0));
      if (ImGui::Begin("Omniverse Nucleus Custom Explorer",
          &alwaysOpen,
          ImGuiWindowFlags_NoResize |
          ImGuiWindowFlags_NoMove |
          ImGuiWindowFlags_NoCollapse)) {

        if (ImGui::IsMouseDown(0) && ImGui::GetMousePos().y < ImGui::GetFontSize()) {
          shouldDrag = true;
        }
        else if ((!ImGui::IsMouseDown(0))) {
          shouldDrag = false;
        }

        if (shouldDrag) {
          RECT rect;
          if (GetWindowRect(hwnd, &rect)) {
            MoveWindow(hwnd,
              rect.left + ImGui::GetMouseDragDelta().x,
              rect.top + ImGui::GetMouseDragDelta().y,
              windowSize.x,
              windowSize.y,
              true);

          }
        }
        ImGui::Text("This is a custom explorer for Nvidia Omniverse");
        ImGui::Text("\n");
        

        ImGui::End();
      }

    }
    // Rendering
    ImGui::Render();
    const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
    g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
    g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    g_pSwapChain->Present(1, 0); // Present with vsync
    if (alwaysOpen == false) { break; }
  }

  // Cleanup
  ImGui_ImplDX11_Shutdown();
  ImGui_ImplWin32_Shutdown();
  ImGui::DestroyContext();

  CleanupDeviceD3D();
  ::DestroyWindow(hwnd);
  ::UnregisterClassA(wc.lpszClassName, wc.hInstance);

  return 0;

}


void
sendReport(const std::string& fileName) {

}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
  // Setup swap chain
  DXGI_SWAP_CHAIN_DESC sd;
  ZeroMemory(&sd, sizeof(sd));
  sd.BufferCount = 2;
  sd.BufferDesc.Width = 0;
  sd.BufferDesc.Height = 0;
  sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  sd.BufferDesc.RefreshRate.Numerator = 60;
  sd.BufferDesc.RefreshRate.Denominator = 1;
  sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
  sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  sd.OutputWindow = hWnd;
  sd.SampleDesc.Count = 1;
  sd.SampleDesc.Quality = 0;
  sd.Windowed = TRUE;
  sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

  UINT createDeviceFlags = 0;
  //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
  D3D_FEATURE_LEVEL featureLevel;
  const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
  if (D3D11CreateDeviceAndSwapChain(NULL,
    D3D_DRIVER_TYPE_HARDWARE,
    NULL,
    createDeviceFlags,
    featureLevelArray,
    2,
    D3D11_SDK_VERSION,
    &sd,
    &g_pSwapChain,
    &g_pd3dDevice,
    &featureLevel,
    &g_pd3dDeviceContext) != S_OK)
    return false;

  CreateRenderTarget();
  return true;
}

void CleanupDeviceD3D()
{
  CleanupRenderTarget();
  if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
  if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
  if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}

void CreateRenderTarget()
{
  ID3D11Texture2D* pBackBuffer;
  g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
  g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
  pBackBuffer->Release();
}

void CleanupRenderTarget()
{
  if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
    return true;

  switch (msg)
  {
  case WM_SIZE:
    if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
    {
      CleanupRenderTarget();
      g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
      CreateRenderTarget();
    }
    return 0;
  case WM_SYSCOMMAND:
    if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
      return 0;
    break;
  case WM_DESTROY:
    ::PostQuitMessage(0);
    return 0;
  }
  return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

