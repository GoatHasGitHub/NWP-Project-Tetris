#define GAME_H

#include <windows.h>
#include "tetris.h"

class Game {
public:
    Game();
    void Initialize();
    void Update();
    void Draw(HWND hWnd);
    void HandleInput(WPARAM wParam);

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
    Tetris tetris;
};


