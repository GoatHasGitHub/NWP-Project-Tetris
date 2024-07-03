#include "tetris.h"

void Tetris::Initialize() {
    board.resize(BOARD_HEIGHT, std::vector<int>(BOARD_HEIGHT, 0));

    pieceX = BOARD_WIDTH / 2;
    pieceY = 0;

    std::array<std::array<int, 4>, 4> piece = { {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    } };
    currentPiece = piece;
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

bool Tetris::IsPositionValid(int newX, int newY, const std::array<std::array<int, 4>, 4>& piece) {
    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {
            if (piece[x][y]) {
                int boardX = newX + x;
                int boardY = newY + y;
                if (boardX < 0 || boardX >= BOARD_WIDTH || boardY < 0 || boardY >= BOARD_HEIGHT || board[boardX][boardY]) {
                    return false;
                }
            }
        }
    }
    return true;
}

void Tetris::MoveLeft() {
    if (IsPositionValid(pieceX - 1, pieceY, currentPiece)) {
        --pieceX;
    }
}

void Tetris::MoveRight() {
    if (IsPositionValid(pieceX + 1, pieceY, currentPiece)) {
        ++pieceX;
    }
}

void Tetris::MoveDown() {
    if (IsPositionValid(pieceX, pieceY + 1, currentPiece)) {
        ++pieceY;
    }
    else {
        // Lock piece in place and reset
        for (int x = 0; x < 4; ++x) {
            for (int y = 0; y < 4; ++y) {
                if (currentPiece[x][y]) {
                    board[pieceX + x][pieceY + y] = 1;
                }
            }
        }
        pieceX = BOARD_WIDTH / 2;
        pieceY = 0;

        std::array<std::array<int, 4>, 4> piece = { {
            {0,1,0,0},
            {0,1,0,0},
            {0,1,1,0},
            {0,0,0,0}
} };
    }
}

void Tetris::Rotate() {
    std::array<std::array<int,4>,4> rotatedPiece;
    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {
            rotatedPiece[y][3 - x] = currentPiece[x][y];
        }
    }
    currentPiece = rotatedPiece;
}
