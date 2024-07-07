#define TETRIS_H

#include <windows.h>
#include <vector>
#include <array>
#include "timer.h"

class Tetris {
public:
    Tetris();
    void Initialize();
    void Update();
    void Draw(HDC hdc);
    void MoveLeft();
    void MoveRight();
    void MoveDown();
    void Rotate();
    void NewPiece();

private:
    static const int BOARD_WIDTH = 10;
    static const int BOARD_HEIGHT = 20;
    std::array<std::array<int, BOARD_HEIGHT>, BOARD_HEIGHT> board;
    std::array<std::array<int, 4>, 4> currentPiece;
    int currentPieceIndex;
    int currentX, currentY;
    bool gameOver;

    /*int score;
    int speedLevel;
    int LinesCleard;
    HWND hWnd;*/

    void ClearLines();
    void PlacePiece();
    void UpdateSpeed();
    bool CanMove(const std::array<std::array<int, 4>, 4>& piece, int x, int y)const;
};
