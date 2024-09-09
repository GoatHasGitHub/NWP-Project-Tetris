#include <windows.h>
#include "tetris.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    Tetris* game = reinterpret_cast<Tetris*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    switch (msg) {
    case WM_CREATE:
    {
        CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
        game = reinterpret_cast<Tetris*>(cs->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(game));
    }
    break;
    case WM_KEYDOWN:
        if (game) {
            switch (wParam) {
            case VK_LEFT:
                game->MoveLeft();
                break;
            case VK_RIGHT:
                game->MoveRight();
                break;
            case VK_DOWN:
                game->MoveDown();
                break;
            case VK_UP:
                game->Rotate();
                break;
            }
            InvalidateRect(hwnd, nullptr, TRUE);
        }
        break;
    case WM_PAINT:
        if (game) {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            game->Draw(hdc);
            EndPaint(hwnd, &ps);
        }
        break;
    case WM_TIMER:
        if (game) {
            game->Update();
            InvalidateRect(hwnd, nullptr, TRUE);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t* className = L"TetrisWindowClass";
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, hInstance, LoadIcon(nullptr, IDI_APPLICATION), LoadCursor(nullptr, IDC_ARROW), (HBRUSH)(COLOR_WINDOW + 1), nullptr, className, LoadIcon(nullptr, IDI_APPLICATION) };

    RegisterClassEx(&wc);

    Tetris game;
    HWND hwnd = CreateWindowEx(0, className, L"Tetris", WS_BORDER | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 320, 640, nullptr, nullptr, hInstance, &game);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    SetTimer(hwnd, 1, 500, nullptr);

    MSG msg = { 0 };
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}
