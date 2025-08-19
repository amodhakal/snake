#include "game.h"
#include <iostream>
#include <random>

Game::Game() {
  for (int boardX = 0; boardX < BOARD_HEIGHT; boardX++) {
    for (int boardY = 0; boardY < BOARD_WIDTH; boardY++) {
      m_Board[boardX][boardY] = GamePiece::EMPTY;
    }
  }

  int Width = BOARD_WIDTH / 2;
  int Height = BOARD_HEIGHT / 2;

  m_SnakeHeadPosition = {(float)Width, (float)Height};
  m_SnakeTailPosition = {(float)Width, (float)Height};
  m_Board[Height][Width] = GamePiece::SNAKE;

  m_SnakeDirection = MovementDirection::UP;
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
      DrawRectangleRounded(rectangle, 0.8f, 4, color);
    }
  }
}

CLITERAL(Color) Game::getPieceColor(const GamePiece &piece) {
  switch (piece) {
  case GamePiece::EMPTY:
    return BLACK;
  case GamePiece::SNAKE:
    return GREEN;
  default:
    static_assert("[Game.getPieceColor] Received an invalid piece");
  }

  return BLACK;
}

void Game::UpdateSnake() {
  Vector2 previousHead = m_SnakeHeadPosition;
  Vector2 previousTail = m_SnakeTailPosition;
  Vector2 movement = getMovementVector(m_SnakeDirection);

  m_SnakeHeadPosition = {previousHead.x + movement.x,
                         previousHead.y + movement.y};
  m_SnakeTailPosition = {previousTail.x + movement.x,
                         previousTail.y + movement.y};

  if (m_SnakeHeadPosition.x < 0 || m_SnakeHeadPosition.x >= BOARD_WIDTH ||
      m_SnakeHeadPosition.y < 0 || m_SnakeHeadPosition.y >= BOARD_HEIGHT) {
    endGame();
  }

  m_Board[(uint)m_SnakeHeadPosition.y][(uint)m_SnakeHeadPosition.x] =
      GamePiece::SNAKE;
  m_Board[(uint)previousTail.y][(uint)previousTail.x] =
      GamePiece::EMPTY; // FIXME: Use queues for multi length snake
}

Vector2 Game::getMovementVector(const MovementDirection &direction) {
  switch (direction) {
  case MovementDirection::UP:
    return {0, -1};
  case MovementDirection::DOWN:
    return {0, 1};
  case MovementDirection::LEFT:
    return {-1, 0};
  case MovementDirection::RIGHT:
    return {1, 0};
  default:
    static_assert("[Game.getMovementVector] Received an invalid movement");
  }
}

void Game::endGame() {
  // TODO: Handle ending
  std::cout << "You died" << std::endl;
  exit(-1);
}

void Game::HandleKeyPress() {
  int keyResult = GetKeyPressed();
  if (keyResult == 0) {
    return;
  }

  switch (keyResult) {
  case KEY_W:
    goto handleUp;
  case KEY_A:
    goto handleLeft;
  case KEY_S:
    goto handleDown;
  case KEY_D:
    goto handleRight;
  case KEY_UP:
    goto handleUp;
  case KEY_LEFT:
    goto handleLeft;
  case KEY_DOWN:
    goto handleDown;
  case KEY_RIGHT:
    goto handleRight;
  default:
    return;
  }

handleUp:
  m_SnakeDirection = m_SnakeDirection == MovementDirection::DOWN
                         ? m_SnakeDirection
                         : MovementDirection::UP;
  return;

handleLeft:
  m_SnakeDirection = m_SnakeDirection == MovementDirection::RIGHT
                         ? m_SnakeDirection
                         : MovementDirection::LEFT;
  return;

handleDown:
  m_SnakeDirection = m_SnakeDirection == MovementDirection::UP
                         ? m_SnakeDirection
                         : MovementDirection::DOWN;
  return;

handleRight:
  m_SnakeDirection = m_SnakeDirection == MovementDirection::LEFT
                         ? m_SnakeDirection
                         : MovementDirection::RIGHT;
  return;
}
