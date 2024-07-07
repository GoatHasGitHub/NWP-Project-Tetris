#include "tetris.h"
#include <array>
#include <vector>
#include <ctime>
#include <cstdlib>

// Tetriminoi
std::array<std::array<std::array<int, 4>, 4>, 7> shapes = { {
    {{ {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0} }},  // I

    {{ {1, 1, 1, 0},
    {1, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0} }},  // J

    {{ {1, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0} }},  // L

    {{ {1, 1, 0, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0} }},  // O

    {{ {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}, 
    {0, 0, 0, 0} }},  // S

    {{ {1, 1, 1, 0},
    {0, 1, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0} }},  // T

    {{ {0, 1, 1, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0} }}   // Z
} };

std::array<COLORREF, 7> pieceColors = {
    RGB(0, 255, 255),  // I - Cyan
    RGB(0, 0, 255),    // J - Blue
    RGB(255, 165, 0),  // L - Orange
    RGB(255, 255, 0),  // O - Yellow
    RGB(0, 255, 0),    // S - Green
    RGB(128, 0, 128),  // T - Purple
    RGB(255, 0, 0)     // Z - Red
};

Tetris::Tetris() {
    Initialize();
}

void Tetris::Initialize() {
    for (auto& row : board){
        row.fill(0);
    }
    NewPiece();
    gameOver = false;
}

void Tetris::NewPiece() {
    currentPiece = shapes[rand() % shapes.size()];
    currentX = 3;
    currentY = 0;

    if (!CanMove(currentPiece, currentX, currentY)) {
        gameOver = true;
    }
}

void Tetris::MoveLeft() {
    if (CanMove(currentPiece, currentX - 1, currentY)) {
        currentX--;
    }
}

void Tetris::MoveRight() {
    if (CanMove(currentPiece, currentX, currentY+1)) {
        currentX++;
    }
}

void Tetris::MoveDown() {
    if (CanMove(currentPiece, currentX, currentY + 1)) {
        currentY++;
    }
    else {
        PlacePiece();
        ClearLines();
        NewPiece();
    }
}

void Tetris::Rotate() {
    std::array<std::array<int, 4>, 4> rotatedPiece;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            rotatedPiece[x][3 - y] = currentPiece[y][x];
        }
    }

    if (CanMove(rotatedPiece, currentX, currentY)) {
        currentPiece = rotatedPiece;
    }
}

void Tetris::PlacePiece() {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (currentPiece[y][x] && (currentY + y < BOARD_HEIGHT) && (currentX + x < BOARD_WIDTH)) {
                board[currentY + y][currentX + x] = currentPieceIndex + 1;
            }
        }
    }
}

void Tetris::ClearLines() {
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        bool fullLine = true;
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (!board[y][x]) {
                fullLine = false;
                break;
            }
        }
        if (fullLine) {
            for (int yy = y; yy > 0; yy--) {
                for (int xx = 0; xx < BOARD_WIDTH; xx++) {
                    board[yy][xx] = board[yy - 1][xx];
                }
            }
            for (int xx = 0; xx < BOARD_WIDTH; xx++) {
                board[0][xx] = 0;
            }
        }
    }
}

bool Tetris::CanMove(const std::array<std::array<int, 4>, 4>& piece, int x, int y) const {
    for (int py = 0; py < 4; py++) {
        for (int px = 0; px < 4; px++) {
            if (piece[py][px]) {
                int boardX = x + px;
                int boardY = y + py;
                if (boardX < 0 || boardX >= BOARD_WIDTH || boardY < 0 || boardY >= BOARD_HEIGHT) {
                    return false;
                }
                if (board[boardY][boardX]) {
                    return false;
                }
            }
        }
    }
    return true;
}

void Tetris::Update() {
    MoveDown();
}

void Tetris::Draw(HDC hdc) {
    RECT rect;
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            rect.left = x * 30;
            rect.top = y * 30;
            rect.right = rect.left + 30;
            rect.bottom = rect.top + 30;

            if (board[y][x]) {
                int colorIndex = board[y][x] - 1;
                if (colorIndex >= 0 && colorIndex < pieceColors.size()) {
                    HBRUSH pieceBrush = CreateSolidBrush(pieceColors[colorIndex]);
                    FillRect(hdc, &rect, pieceBrush);
                    DeleteObject(pieceBrush);
                }
            }
            else {
                FrameRect(hdc, &rect, (HBRUSH)GetSysColorBrush(BLACK_BRUSH));
            }
        }
    }


    for (int py = 0; py < 4; py++) {
        for (int px = 0; px < 4; px++) {
            if (currentPiece[py][px]) {
                int boardX = currentX + px;
                int boardY = currentY + py;
                rect.left = boardX * 30;
                rect.top = boardY * 30;
                rect.right = rect.left + 30;
                rect.bottom = rect.top + 30;
                HBRUSH pieceBrush = CreateSolidBrush(pieceColors[currentPieceIndex]);
                FillRect(hdc, &rect, pieceBrush);
                DeleteObject(pieceBrush);
            }
        }
    }
}