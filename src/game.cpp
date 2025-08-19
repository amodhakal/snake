#include "game.h"
#include <iostream>
#include <random>

Game::Game() {
  for (int boardX = 0; boardX < BOARD_HEIGHT; boardX++) {
    for (int boardY = 0; boardY < BOARD_WIDTH; boardY++) {
      m_Board[boardX][boardY] = GamePiece::EMPTY;
    }
  }

  int width = BOARD_WIDTH / 2;
  int height = BOARD_HEIGHT / 2;

  m_SnakePositions.insert(m_SnakePositions.begin(),
                          {(float)width, (float)height});
  m_Board[height][width] = GamePiece::SNAKE;

  m_SnakeDirection = MovementDirection::UP;
  Game::createApple();
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
  case GamePiece::APPLE:
    return RED;
  default:
    static_assert("[Game.getPieceColor] Received an invalid piece");
  }

  return BLACK;
}

void Game::UpdateSnake() {
  // Get values
  Vector2 movement = getMovementVector(m_SnakeDirection);
  Vector2 headPosition = m_SnakePositions.front();
  Vector2 tailPosition = m_SnakePositions.back();

  // Remove tail
  m_SnakePositions.pop_back();
  m_Board[(uint)tailPosition.y][(uint)tailPosition.x] = GamePiece::EMPTY;

  Vector2 newHead = {movement.x + headPosition.x, movement.y + headPosition.y};

  // Check for border touching
  if (newHead.x < 0 || newHead.x >= BOARD_WIDTH || newHead.y < 0 ||
      newHead.y >= BOARD_HEIGHT) {
    endGame();
  }

  // Check for eating itself
  for (const Vector2 &position : m_SnakePositions) {
    if (position.x == newHead.x && position.y == newHead.y) {
      endGame();
    }
  }

  // Check for apple
  if (newHead.x == m_ApplePosition.x && newHead.y == m_ApplePosition.y) {
    eatApple(tailPosition);
  }

  // Add head
  m_SnakePositions.insert(m_SnakePositions.begin(), newHead);
  m_Board[(uint)newHead.y][(uint)newHead.x] = GamePiece::SNAKE;
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

void Game::createApple() {
  uint chosenWidth = rand() % BOARD_WIDTH;
  uint chosenHeight = rand() % BOARD_HEIGHT;

  if (m_Board[chosenHeight][chosenWidth] != GamePiece::EMPTY) {
    return createApple();
  }

  m_Board[chosenHeight][chosenWidth] = GamePiece::APPLE;
  m_ApplePosition = {(float)chosenWidth, (float)chosenHeight};
}

void Game::eatApple(const Vector2 &tailPosition) {
  m_SnakePositions.push_back(tailPosition);
  m_Board[(uint)tailPosition.y][(uint)tailPosition.x] = GamePiece::SNAKE;

  createApple();
}
