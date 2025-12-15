#include <raylib.h>
#include "assert.h"
#include "game.h"

int main() {
  Game game;

  InitWindow(game.SCR_WIDTH, game.SCR_HEIGHT, "Snake");
  SetTargetFPS(game.GetFps());

  while (!WindowShouldClose()) {
   game.Run();
  }

  return 0;
}
