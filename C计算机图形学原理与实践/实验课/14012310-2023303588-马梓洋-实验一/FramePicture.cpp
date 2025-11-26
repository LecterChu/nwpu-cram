// FramePicturePro.cpp  : 控制台模板 | 高级相框 | 已修复全部编译错误
#include <windows.h>
#include <gdiplus.h>
#include <cstdio>          // ① 修复 swprintf
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

using namespace Gdiplus;

constexpr wchar_t CLASS_NAME[] = L"FramePictureProWnd";

int g_winW = 0;
int g_winH = 0;

/* ----------------------------------------------------------
 * 高级绘图：外阴影 | 金边 | 内阴影 | 圆角裁剪
 * -------------------------------------------------------- */
void OnPaint(HDC hdc)
{
    Graphics g(hdc);
    g.SetSmoothingMode(SmoothingModeAntiAlias);

    // 1. 加载图片
    Image* img = Image::FromFile(L"oil.png");
    if (!img || img->GetLastStatus() != Ok)
    {
        wchar_t buf[128];
        swprintf(buf, _countof(buf),
            L"加载失败，GDI+ 状态码=%d\n请确认 oil.jpg 在同目录且为 RGB 格式",
            (int)img->GetLastStatus());
        MessageBox(nullptr, buf, L"诊断", MB_ICONERROR);
        return;
    }

    int imgW = img->GetWidth();
    int imgH = img->GetHeight();
    const int frame = 40;          // 外框宽度
    const int shadow = 15;         // 阴影宽度
    const int radius = 20;         // 圆角半径

    // 2. 外阴影（右下模糊）
    {
        GraphicsPath shadowPath;
        shadowPath.AddRectangle(Rect(shadow, shadow,
            imgW + 2 * frame + shadow,
            imgH + 2 * frame + shadow));
        PathGradientBrush shadowBrush(&shadowPath);
        shadowBrush.SetCenterColor(Color(80, 0, 0, 0));
        Color surround[] = { Color(0, 0, 0, 0) };
        INT   nSurround = 1;                              // ② 修复类型
        shadowBrush.SetSurroundColors(surround, &nSurround);
        g.FillPath(&shadowBrush, &shadowPath);
    }

    // 3. 金边外框
    Rect outRect(0, 0, imgW + 2 * frame, imgH + 2 * frame);
    LinearGradientBrush frameBrush(outRect,
        Color(255, 212, 175, 55),   // 金黄
        Color(255, 139, 69, 19),    // 棕
        LinearGradientModeVertical);
    Pen framePen(&frameBrush, frame);
    g.DrawRectangle(&framePen, outRect);

    // 4. 内阴影（凹陷）
    Rect inRect(frame - shadow, frame - shadow,
        imgW + 2 * shadow, imgH + 2 * shadow);
    GraphicsPath inPath;
    inPath.AddRectangle(inRect);
    PathGradientBrush inBrush(&inPath);
    inBrush.SetCenterColor(Color(0, 0, 0, 0));
    Color inSurround[] = { Color(120, 0, 0, 0) };
    INT   nIn = 1;                                        // ② 修复类型
    inBrush.SetSurroundColors(inSurround, &nIn);
    g.FillPath(&inBrush, &inPath);

    // 5. 圆角裁剪区
    GraphicsPath canvasPath;
    canvasPath.AddArc(frame, frame, radius, radius, 180, 90);
    canvasPath.AddArc(frame + imgW - radius, frame, radius, radius, 270, 90);
    canvasPath.AddArc(frame + imgW - radius, frame + imgH - radius, radius, radius, 0, 90);
    canvasPath.AddArc(frame, frame + imgH - radius, radius, radius, 90, 90);
    canvasPath.CloseFigure();

    // 6. 在裁剪区内画图
    Region oldReg;
    g.GetClip(&oldReg);
    g.SetClip(&canvasPath);
    g.DrawImage(img, frame, frame, imgW, imgH);
    g.SetClip(&oldReg);

    delete img;
}

/* ----------------------------------------------------------
 * 窗口过程
 * -------------------------------------------------------- */
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        OnPaint(hdc);
        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

/* ----------------------------------------------------------
 * main
 * -------------------------------------------------------- */
int main()
{
    // 1. GDI+ 初始化
    ULONG_PTR gdiToken = 0;
    GdiplusStartupInput gdiSI;
    GdiplusStartup(&gdiToken, &gdiSI, nullptr);

    // 2. 提前读尺寸
    {
        Image tmpImg(L"oil.png");
        if (tmpImg.GetLastStatus() != Ok)
        {
            MessageBox(nullptr, L"oil.png 加载失败，请确认文件存在且为 RGB 格式", L"错误", MB_ICONERROR);
            return 0;
        }
        const int frame = 40, shadow = 15;
        g_winW = tmpImg.GetWidth() + 2 * frame + shadow + 16;
        g_winH = tmpImg.GetHeight() + 2 * frame + shadow + 39;
    }

    // 3. 注册窗口类
    WNDCLASSEX wc = { sizeof(wc) };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = CLASS_NAME;
    RegisterClassEx(&wc);

    // 4. 创建窗口
    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, L"实验二·Pro：高级相框（已修复）",
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, g_winW, g_winH,
        nullptr, nullptr, wc.hInstance, nullptr);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    // 5. 消息循环
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // 6. 清理
    GdiplusShutdown(gdiToken);
    return (int)msg.wParam;
}