#include <windows.h>
#include "game.h"

#define TIMER_ID 1
#define TIMER_INTERVAL 500 //ms

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    WNDCLASSEX wcex = { 0 };
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = Game::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = sizeof(LONG_PTR);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "TetrisClass";

    if (!RegisterClassEx(&wcex)) {
        MessageBox(NULL, "Call to RegisterClassEx Failed", "Windows Destop Guided tour", NULL);
        return 1;
    }

    HWND hWnd = CreateWindow("TetrisClass", "Tetris", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        MessageBox(NULL, "Call to CreateWindow Failed", "Windows Destop Guided tour", NULL);
        return 1;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    Game game;
    SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)&game);

    SetTimer(hWnd, TIMER_ID, TIMER_INTERVAL, NULL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    KillTimer(hWnd, TIMER_ID);

    return (int)msg.wParam;
}
