#pragma once
#include <raylib.h>
#include <sys/types.h>
#include <vector>

enum class GamePiece { EMPTY, SNAKE, APPLE };

enum class GameStatus { RUNNING, DEFEAT, DEFEAT_DISPLAYED };

enum class MovementDirection { UP, DOWN, LEFT, RIGHT };

class Game {
public:
  Game();
  void Run();
  float GetFps();

  constexpr static float INITIAL_FPS = 10;
  constexpr static uint INITIAL_SCORE = 100;
  constexpr static uint CELL_SIZE = 30;
  constexpr static uint CELL_DISTANCE = 2;
  constexpr static uint BOARD_WIDTH = 25;
  constexpr static uint BOARD_HEIGHT = 20;
  constexpr static uint TEXT_SPACE = CELL_DISTANCE * 16 + 28;
  constexpr static uint SCR_WIDTH =
      (CELL_SIZE * BOARD_WIDTH) + (CELL_DISTANCE * (BOARD_WIDTH + 1));
  constexpr static uint SCR_HEIGHT = (CELL_SIZE * BOARD_HEIGHT) +
                                     (CELL_DISTANCE * (BOARD_HEIGHT + 1)) +
                                     TEXT_SPACE;

private:
  MovementDirection m_SnakeDirection;
  GamePiece m_Board[BOARD_HEIGHT][BOARD_WIDTH];
  std::vector<Vector2> m_SnakePositions;
  Vector2 m_ApplePosition;
  float m_Fps;
  float m_Score;
  float m_DefeatDisplayedTime;
  GameStatus m_Status;

  CLITERAL(Color) getPieceColor(const GamePiece &piece);
  Vector2 getMovementVector(const MovementDirection &direction);
  void eatApple(const Vector2 &tailPosition);
  void createApple();
  void updateGame();
  void handleRunning();
  void handleDefeat();
  void handleDefeatDisplayed();
  void handleKeyPress();
  void endGame();
};
