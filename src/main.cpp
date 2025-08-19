#include <raylib.h>

#include "game.h"

int main() {
  Game game;

  InitWindow(game.SCR_WIDTH, game.SCR_HEIGHT, "Snake");
  SetTargetFPS(game.FPS);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(DARKGRAY);
    game.Draw();
    EndDrawing();
    game.UpdateSnake();
    game.HandleKeyPress();
  }

  return 0;
}
