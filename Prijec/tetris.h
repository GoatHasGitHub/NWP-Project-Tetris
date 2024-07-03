#define TETRIS_H

#include <windows.h>
#include <vector>
#include <array>

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
    std::vector<std::vector<int>> board;
    std::array<std::array<int, 4>, 4> currentPiece;
    int pieceX, pieceY;

    void DrawBlock(HDC hdc, int x, int y, bool filled);
    bool IsPositionValid(int newX, int newY, const std::array<std::array<int, 4>, 4>& piece);
};
