#include "game.h"
#include <iostream>

Game::Game() {
    Initialize();
}

void Game::Initialize() {
    tetris.Initialize();
}

void Game::Update() {
    tetris.Update();
}

void Game::Draw(HWND hWnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    tetris.Draw(hdc);
    EndPaint(hWnd, &ps);
}

void Game::HandleInput(WPARAM wParam, HWND hWnd) {
    switch (wParam) {
    case VK_LEFT:
        tetris.MoveLeft();
        break;
    case VK_RIGHT:
        tetris.MoveRight();
        break;
    case VK_DOWN:
        tetris.MoveDown();
        break;
    case VK_UP:
        tetris.Rotate();
        break;
    }
    InvalidateRect(hWnd, NULL, TRUE);
}

LRESULT CALLBACK Game::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    Game* pGame = reinterpret_cast<Game*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    switch (message) {
    case WM_PAINT:
        if (pGame) {
            pGame->Draw(hWnd);
        }
        break;
    case WM_KEYDOWN:
        if (pGame) {
            pGame->HandleInput(wParam, hWnd);
        }
        break;
    case WM_TIMER:
        if (pGame) {
            if (wParam == TIMER_ID) {
                pGame->Update();
                InvalidateRect(hWnd, NULL, TRUE);
            }
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
