#pragma once
#include <raylib.h>
#include <sys/types.h>

enum class GamePiece { EMPTY, SNAKE, APPLE };

enum class MovementDirection { UP, DOWN, LEFT, RIGHT };

class Game {
public:
  Game();
  void Draw();
  void UpdateSnake();
  void HandleKeyPress();

  constexpr static uint FPS = 10;
  constexpr static uint CELL_SIZE = 30;
  constexpr static uint CELL_DISTANCE = 2;
  constexpr static uint BOARD_WIDTH = 25;
  constexpr static uint BOARD_HEIGHT = 20;
  constexpr static uint SCR_WIDTH =
      (CELL_SIZE * BOARD_WIDTH) + (CELL_DISTANCE * (BOARD_WIDTH + 1));
  constexpr static uint SCR_HEIGHT =
      (CELL_SIZE * BOARD_HEIGHT) + (CELL_DISTANCE * (BOARD_HEIGHT + 1));

private:
  MovementDirection m_SnakeDirection;
  GamePiece m_Board[BOARD_HEIGHT][BOARD_WIDTH];
  Vector2 m_SnakeHeadPosition;
  Vector2 m_SnakeTailPosition;

  CLITERAL(Color) getPieceColor(const GamePiece &piece);
  Vector2 getMovementVector(const MovementDirection &direction);
  void endGame();
};
