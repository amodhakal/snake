#include "game.h"

Game::Game() {
  for (int boardX = 0; boardX < BOARD_HEIGHT; boardX++) {
    for (int boardY = 0; boardY < BOARD_WIDTH; boardY++) {
      m_Board[boardX][boardY] = GamePiece::EMPTY;
    }
  }
}

void Game::Draw() {
  constexpr uint SPLIT = CELL_SIZE + CELL_DISTANCE;

  for (int boardX = 0; boardX < BOARD_HEIGHT; boardX++) {
    float posY = CELL_DISTANCE + boardX * SPLIT;

    for (int boardY = 0; boardY < BOARD_WIDTH; boardY++) {
      float posX = CELL_DISTANCE + boardY * SPLIT;
      float CELL_SIZE_F = static_cast<float>(CELL_SIZE);
      Rectangle rectangle = {posX, posY, CELL_SIZE_F, CELL_SIZE_F};

      GamePiece piece = m_Board[boardX][boardY];
      CLITERAL(Color) color = getPieceColor(piece);
      DrawRectangleRounded(rectangle, 0.8f, 4, BLACK);
    }
  }
}

CLITERAL(Color) Game::getPieceColor(const GamePiece &piece) {
  switch (piece) {
  case GamePiece::EMPTY:
    return BLACK;
  default:
    static_assert("[Game.getPieceColor] Received an invalid piece");
  }
}
