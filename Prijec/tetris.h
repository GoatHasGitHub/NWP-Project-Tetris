#define TETRIS_H

#include <windows.h>

class Tetris {
public:
    void Initialize();
    void Update();
    void Draw(HDC hdc);
    void MoveLeft();
    void MoveRight();
    void MoveDown();
    void Rotate();

private:
    static const int BOARD_WIDTH = 10;
    static const int BOARD_HEIGHT = 20;
    int board[BOARD_WIDTH][BOARD_HEIGHT];
    int currentPiece[4][4];
    int pieceX, pieceY;

    void DrawBlock(HDC hdc, int x, int y, bool filled);
};
