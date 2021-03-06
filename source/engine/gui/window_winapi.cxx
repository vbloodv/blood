#include "../../../include/blood/gui/window_winapi.hxx"

#ifdef WIN32

#include <exception>
#include <windows.h>
#include <winuser.h>

static const int ms_bits = 32;

LRESULT CALLBACK procedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

using namespace blood::gui;

WindowWinApi::WindowWinApi()
: m_hwnd(NULL)
, m_instance(NULL)
, m_fullscreen(false)
, m_w(0)
, m_h(0)
{}

WindowWinApi::~WindowWinApi()
{
    release();
}

void WindowWinApi::initialize(const char* title, int w, int h)
{
    WNDCLASS wc;
    DWORD dwExStyle;
    DWORD dwStyle;
    RECT WindowRect;
    WindowRect.top = (long)0;
    WindowRect.left = (long)0;
    WindowRect.right = (long)w;
    WindowRect.bottom = (long)h;
    m_instance = GetModuleHandle(NULL);
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = (WNDPROC)m_wnd_procedure;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = m_instance;
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = ms_class_name;

    if (!RegisterClass(&wc))
        throw std::exception("window class not registred");

    if (m_fullscreen)
    {
        DEVMODE dmScreenSettings;
        memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
        dmScreenSettings.dmSize = sizeof(dmScreenSettings);
        dmScreenSettings.dmPelsWidth = w;
        dmScreenSettings.dmPelsHeight = h;
        dmScreenSettings.dmBitsPerPel = ms_bits;
        dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

        if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
        {
            m_fullscreen = false;
        }
    }

    if (m_fullscreen)
    {
        dwExStyle = WS_EX_APPWINDOW;
        dwStyle = WS_POPUP;
        ShowCursor(false);
    }
    else
    {
        dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
        dwStyle = WS_OVERLAPPEDWINDOW;
    }

    AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle);
    const POINT display_center = get_display_center();                                                                                                                           
    const POINT window_size = { WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top };
    
    m_hwnd = CreateWindowEx
        (dwExStyle
        , ms_class_name
        , title
        , WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle
        , display_center.x - (window_size.x / 2.0f)
        , display_center.y - (window_size.y / 2.0f)
        , window_size.x
        , window_size.y
        , NULL
        , NULL
        , m_instance
        , NULL);

    if (m_hwnd)
    {
        //release();
        //KillGLWindow();
    }
}

void WindowWinApi::show()
{
    ShowWindow(m_hwnd, SW_SHOW);
    SetForegroundWindow(m_hwnd);
    SetFocus(m_hwnd);
}

void WindowWinApi::release()
{
    if (m_fullscreen)
    {
        ChangeDisplaySettings(NULL, 0);
        ShowCursor(true);
    }

    if (m_hwnd && !DestroyWindow(m_hwnd))
    {
        m_hwnd = NULL;
    }

    if (!UnregisterClass(ms_class_name, m_instance))
    {
        m_instance = NULL;
    }
    m_hwnd = NULL;
}

void WindowWinApi::set_fullscreen(bool fullscreen /*= true*/)
{
    m_fullscreen = fullscreen;
}

void WindowWinApi::set_procedure(callback_wnd_procedure* fn)
{
    m_wnd_procedure = fn;
}

bool blood::gui::WindowWinApi::is_created() const
{
    return m_hwnd;
}

POINT blood::gui::WindowWinApi::get_display_center()
{
    const int center_x = (int)GetSystemMetrics(SM_CXSCREEN)/2.0f;
    const int center_y = (int)GetSystemMetrics(SM_CYSCREEN)/2.0f;
    const POINT point = { center_x, center_y };
    return point;
}

#endif // WIN32