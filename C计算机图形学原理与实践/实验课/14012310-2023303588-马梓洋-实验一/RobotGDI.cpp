
#include <windows.h>
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

// 画机器人
void DrawRobot(HDC hdc)
{
    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    HBRUSH hBrush = CreateSolidBrush(RGB(240, 240, 240));
    HGDIOBJ oldPen = SelectObject(hdc, hPen);
    HGDIOBJ oldBrush = SelectObject(hdc, hBrush);

    // 头
    Ellipse(hdc, 160, 80, 320, 240);
    // 眼
    hBrush = CreateSolidBrush(RGB(0, 0, 255));
    SelectObject(hdc, hBrush);
    Ellipse(hdc, 190, 130, 220, 160);
    Ellipse(hdc, 260, 130, 290, 160);
    DeleteObject(hBrush);
    // 鼻
    hBrush = CreateSolidBrush(RGB(255, 192, 203));
    SelectObject(hdc, hBrush);
    Rectangle(hdc, 235, 175, 245, 195);
    DeleteObject(hBrush);
    // 嘴
    Arc(hdc, 210, 180, 270, 220, 210, 200, 270, 200);
    // 身体
    hBrush = CreateSolidBrush(RGB(160, 160, 160));
    SelectObject(hdc, hBrush);
    Rectangle(hdc, 180, 240, 300, 400);
    DeleteObject(hBrush);
    // 左臂
    MoveToEx(hdc, 180, 270, nullptr);
    LineTo(hdc, 120, 240); LineTo(hdc, 110, 280);
    // 右臂
    MoveToEx(hdc, 300, 270, nullptr);
    LineTo(hdc, 360, 240); LineTo(hdc, 370, 280);
    // 左腿
    MoveToEx(hdc, 200, 400, nullptr);
    LineTo(hdc, 190, 500); LineTo(hdc, 180, 510);
    // 右腿
    MoveToEx(hdc, 280, 400, nullptr);
    LineTo(hdc, 290, 500); LineTo(hdc, 300, 510);

    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(hPen);
}

// 窗口过程
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_PAINT)
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        DrawRobot(hdc);
        EndPaint(hwnd, &ps);
        return 0;
    }
    if (msg == WM_DESTROY) { PostQuitMessage(0); return 0; }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// 控制台项目入口：main
int main()
{
    // 1. 注册窗口类
    WNDCLASSEX wc = { sizeof(wc) };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = L"RobotGDI";
    RegisterClassEx(&wc);

    // 2. 创建窗口
    HWND hwnd = CreateWindowEx(
        0, L"RobotGDI", L"GDI 机器人 —— VS 控制台项目",
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 480, 640,
        nullptr, nullptr, wc.hInstance, nullptr);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    // 3. 消息循环
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}