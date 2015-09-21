#pragma once
#include <memory>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx9math.h>
#include <directxmath.h>
#include <directxcolors.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11d.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "winmm.lib")

class DXDevice
{
public:
    DXDevice();
    ~DXDevice();

    void initialize(HWND, int w, int h, bool is_fullscreen);
    void release();

    void update();
    void render();

    void load_shader_content();

    void create_pixel_shader();
    void create_vertex_shader();

    void create_matrices();
    void create_constant_buffer();

    void create_vertex_buffer();
    void create_index_buffer();

    void create_input_layout();
    void create_depth_stencil_buffer();

public:
    DirectX::XMUINT2        m_display_size;
    HWND                    m_hwnd;
    HINSTANCE               m_hinstance;
    D3D_DRIVER_TYPE         m_driver_type;
    ID3D11Device*           m_device;
    ID3D11DeviceContext*    m_device_context;
    IDXGISwapChain*         m_swap_chain;
    ID3D11RenderTargetView* m_render_target_view;
private:
    ID3D11InputLayout*      m_input_layout;
    ID3D11VertexShader*     m_vertex_shader;
    ID3D11PixelShader*      m_pixel_shader;
private:
    DirectX::XMMATRIX       m_view;
    DirectX::XMMATRIX       m_world;
    DirectX::XMMATRIX       m_projection;
private:
    ID3D11Buffer*           m_vertex_buffer;
    ID3D11Buffer*           m_index_buffer;
    ID3D11Buffer*           m_constant_buffer;
private:
    ID3D11Texture2D*		 m_depth_stencil_buffer;
    ID3D11DepthStencilState* m_depth_stencil_state;
    ID3D11DepthStencilView*  m_depth_stencil_view;

private:
    char*                   m_vertex_shader_content;
    size_t                  m_vertex_shader_size;
    char*                   m_pixel_shader_content;
    size_t                  m_pixel_shader_size;
};