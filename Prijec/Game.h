#define GAME_H

#include <windows.h>
#include "tetris.h"
#include "timer.h"

class Game {
public:
    Game();
    void Initialize();
    void Update();
    void Draw(HWND hWnd);
    void HandleInput(WPARAM wParam, HWND hWnd);

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
    Tetris tetris;
    static constexpr UINT TIMER_INTERVAL = 500;
};


