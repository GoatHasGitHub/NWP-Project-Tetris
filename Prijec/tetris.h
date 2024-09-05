#define TETRIS_H

#include <windows.h>
#include <vector>
#include <array>

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
    std::array<std::array<int, BOARD_WIDTH>, BOARD_HEIGHT> board;
    std::array<std::array<int, 4>, 4> currentPiece;
    int currentPieceIndex;
    int currentX, currentY;
    bool gameOver;

    void ClearLines();
    void PlacePiece();
    bool CanMove(const std::array<std::array<int, 4>, 4>& piece, int x, int y) const;
};
