#include "game.h"
#include "assert.h"
#include <format>
#include <string>

Game::Game()
    : m_Fps(INITIAL_FPS), m_Score(INITIAL_SCORE),
      m_Status(GameStatus::RUNNING) {
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

void Game::Run() {
  switch (m_Status) {
  case GameStatus::RUNNING:
    return handleRunning();
  case GameStatus::DEFEAT:
    return handleDefeat();
  case GameStatus::DEFEAT_DISPLAYED:
    return handleDefeatDisplayed();
    break;
  default:
    assert("[Game.Run] Received an invalid game status");
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
    assert(false && "[Game.getPieceColor] Received an invalid piece");
  }

  return BLACK;
}

void Game::updateGame() {
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
    return endGame();
  }

  // Check for eating itself
  for (const Vector2 &position : m_SnakePositions) {
    if (position.x == newHead.x && position.y == newHead.y) {
      return endGame();
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
    assert("[Game.getMovementVector] Received an invalid movement");
  }
}

void Game::endGame() { m_Status = GameStatus::DEFEAT; }

void Game::handleKeyPress() {
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
  m_Fps += 1;
  SetTargetFPS(m_Fps);

  m_Score += INITIAL_SCORE;

  m_SnakePositions.push_back(tailPosition);
  m_Board[(uint)tailPosition.y][(uint)tailPosition.x] = GamePiece::SNAKE;

  createApple();
}

float Game::GetFps() { return m_Fps; }

void Game::handleRunning() {
  BeginDrawing();
  ClearBackground(DARKGRAY);

  constexpr uint SPLIT = CELL_SIZE + CELL_DISTANCE;

  std::string timeString = std::format("{:.2f}", GetTime());
  std::string timeText = "Time: ";
  timeText += timeString;

  std::string scoreString = std::format("{}", m_Score);
  std::string scoreText = "Score: ";
  scoreText += scoreString;

  DrawText(timeText.c_str(), CELL_DISTANCE * 4, CELL_DISTANCE * 4, 24, WHITE);
  DrawText(scoreText.c_str(), CELL_DISTANCE * 4, CELL_DISTANCE * 16, 24, WHITE);

  for (int boardX = 0; boardX < BOARD_HEIGHT; boardX++) {
    float posY = CELL_DISTANCE + TEXT_SPACE + boardX * SPLIT;

    for (int boardY = 0; boardY < BOARD_WIDTH; boardY++) {
      float posX = CELL_DISTANCE + boardY * SPLIT;
      float CELL_SIZE_F = static_cast<float>(CELL_SIZE);
      Rectangle rectangle = {posX, posY, CELL_SIZE_F, CELL_SIZE_F};

      GamePiece piece = m_Board[boardX][boardY];
      CLITERAL(Color) color = getPieceColor(piece);
      DrawRectangleRounded(rectangle, 0.8f, 4, color);
    }
  }

  EndDrawing();
  handleKeyPress();
  updateGame();
}

void Game::handleDefeat() {
  std::string timeString = std::format("{:.2f}", GetTime());
  std::string timeText = "Time: ";
  timeText += timeString;

  std::string scoreString = std::format("{}", m_Score);
  std::string scoreText = "Score: ";
  scoreText += scoreString;

  BeginDrawing();
  ClearBackground(BLACK);
  DrawText(timeText.c_str(), SCR_WIDTH / 4, SCR_HEIGHT / 3 - 24, 48, RED);
  DrawText(scoreText.c_str(), SCR_WIDTH / 4, SCR_HEIGHT / 3 + 24, 48, RED);

  EndDrawing();

  m_DefeatDisplayedTime = GetTime();
  m_Status = GameStatus::DEFEAT_DISPLAYED;
}

void Game::handleDefeatDisplayed() {
  if (m_DefeatDisplayedTime + 3 < GetTime()) {
    exit(0);
  }
}
