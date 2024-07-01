#include "tetris.h"

void Tetris::Initialize() {
    for (int x = 0; x < BOARD_WIDTH; ++x)
        for (int y = 0; y < BOARD_HEIGHT; ++y)
            board[x][y] = 0;

    pieceX = BOARD_WIDTH / 2;
    pieceY = 0;

    int piece[4][4] = {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    };
    memcpy(currentPiece, piece, sizeof(piece));
}

void Tetris::Update() {
    MoveDown();
}

void Tetris::Draw(HDC hdc) {
    for (int x = 0; x < BOARD_WIDTH; ++x) {
        for (int y = 0; y < BOARD_HEIGHT; ++y) {
            DrawBlock(hdc, x, y, board[x][y]);
        }
    }

    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {
            if (currentPiece[x][y]) {
                DrawBlock(hdc, pieceX + x, pieceY + y, true);
            }
        }
    }
}

void Tetris::DrawBlock(HDC hdc, int x, int y, bool filled) {
    
    RECT rect;
    rect.left = x * 20;
    rect.top = y * 20;
    rect.right = rect.left + 20;
    rect.bottom = rect.top + 20;
    FillRect(hdc, &rect, (HBRUSH)(filled ? GetStockObject(BLACK_BRUSH) : GetStockObject(WHITE_BRUSH)));
}

void Tetris::MoveLeft() {
    --pieceX;
}

void Tetris::MoveRight() {
    ++pieceX;
}

void Tetris::MoveDown() {
    ++pieceY;
}

void Tetris::Rotate() {
    int rotatedPiece[4][4];
    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {
            rotatedPiece[y][3 - x] = currentPiece[x][y];
        }
    }
    memcpy(currentPiece, rotatedPiece, sizeof(rotatedPiece));
}
