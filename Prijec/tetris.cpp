#include "tetris.h"
#include <array>
#include <vector>

// Tetriminoi
std::array<std::array<std::array<int, 4>, 4>, 7> shapes = { {
    {{ {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} }},  // I
    {{ {1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} }},  // J
    {{ {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} }},  // L
    {{ {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} }},  // O
    {{ {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} }},  // S
    {{ {1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} }},  // T
    {{ {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} }}   // Z
} };

Tetris::Tetris() {
    Initialize();
}

void Tetris::Initialize() {
    board.fill({ 0 });
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
    if (CanMove(currentPiece, currentX + 1, currentY)) {
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
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_HEIGHT; x++) {
            if (currentPiece[y][x]) {
                board[currentY + y][currentX + x] = currentPiece[y][x];
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
                FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
            }
            else {
                FrameRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
            }
        }
    }

    // Draw the current piece
    for (int py = 0; py < 4; py++) {
        for (int px = 0; px < 4; px++) {
            if (currentPiece[py][px]) {
                rect.left = (currentX + px) * 30;
                rect.top = (currentY + py) * 30;
                rect.right = rect.left + 30;
                rect.bottom = rect.top + 30;
                FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
            }
        }
    }
}