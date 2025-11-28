// BubbleBlower.cpp : 控制台项目 | 吹泡泡小游戏 | 已修复 C2280
#include <windows.h>
#include <windowsx.h>   // GET_X_LPARAM
#include <gdiplus.h>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

using namespace Gdiplus;
using namespace std;

constexpr wchar_t CLASS_NAME[] = L"BubbleBlowerWnd";
constexpr int     WINDOW_W = 800;
constexpr int     WINDOW_H = 600;
constexpr int     TIMER_ID = 1;
constexpr int     TIMER_ELAPSE = 30;

/* ---------- 泡泡 ---------- */
struct Bubble
{
    int   x, y, r;
    float dx, dy;
    int   life, maxLife;
    BYTE  r8, g8, b8;               // ① 避免 Color 不可拷贝

    bool  dead() const { return life <= 0; }
    void  update(RECT rc);
    void  draw(Graphics& g) const;  // ② const 成员函数
};

void Bubble::update(RECT rc)
{
    x += (int)dx;
    y += (int)dy;
    dy += 0.15f; // 水阻力
    life--;

    if (x - r < 0 || x + r > rc.right)  dx = -dx;
    if (y - r < 0)                      dy = -dy;
}

void Bubble::draw(Graphics& g) const
{
    int alpha = (life * 255) / maxLife;
    // 渐变画刷
    GraphicsPath path;
    path.AddEllipse(x - r, y - r, 2 * r, 2 * r);
    PathGradientBrush brush(&path);
    brush.SetCenterColor(Color(alpha, 255, 255, 255));
    Color surround[] = { Color(alpha, r8, g8, b8) };
    INT count = 1;
    brush.SetSurroundColors(surround, &count);
    g.FillPath(&brush, &path);

    // 高光
    SolidBrush highlight(Color(alpha * 2 / 3, 255, 255, 255));
    g.FillEllipse(&highlight, x - r / 3, y - r / 3, r / 2, r / 2);
}

/* ---------- 全局 ---------- */
vector<Bubble> bubbles;
RECT           rcClient{ 0,0,WINDOW_W,WINDOW_H };

inline void SpawnBubble(int mx, int my)
{
    Bubble b;
    b.r = 20 + rand() % 21;
    b.x = mx;
    b.y = my;
    b.dx = float(rand() % 5 - 2);
    b.dy = float(-(rand() % 4 + 3));
    b.maxLife = 80 + rand() % 41;
    b.life = b.maxLife;
    b.r8 = rand() % 256;
    b.g8 = rand() % 256;
    b.b8 = rand() % 256;
    bubbles.push_back(b);
}

/* ---------- 窗口过程 ---------- */
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
        SetTimer(hwnd, TIMER_ID, TIMER_ELAPSE, nullptr);
        srand((unsigned)time(nullptr));
        return 0;

    case WM_TIMER:
        for (auto& b : bubbles) b.update(rcClient);
        bubbles.erase(remove_if(bubbles.begin(), bubbles.end(),
            [](const Bubble& b) { return b.dead(); }),
            bubbles.end());
        InvalidateRect(hwnd, nullptr, FALSE);
        return 0;

    case WM_LBUTTONDOWN:
        SpawnBubble(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        return 0;

    case WM_SIZE:
        GetClientRect(hwnd, &rcClient);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        Graphics g(hdc);
        g.Clear(Color(135, 206, 235)); // 天蓝背景
        for (const auto& b : bubbles) b.draw(g);
        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_ERASEBKGND:
        return 1; // 防闪烁

    case WM_DESTROY:
        KillTimer(hwnd, TIMER_ID);
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

/* ---------- main ---------- */
int main()
{
    ULONG_PTR gdiToken;
    GdiplusStartupInput gdiSI;
    GdiplusStartup(&gdiToken, &gdiSI, nullptr);

    WNDCLASSEX wc = { sizeof(wc) };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.lpszClassName = CLASS_NAME;
    RegisterClassEx(&wc);

    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, L"实验三：BubbleBlower 吹泡泡（C2280 已修复）",
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_W, WINDOW_H,
        nullptr, nullptr, wc.hInstance, nullptr);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    GdiplusShutdown(gdiToken);
    return (int)msg.wParam;
}