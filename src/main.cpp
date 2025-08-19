#include <raylib.h>
#include "assert.h"
#include "game.h"
#include <iostream>

int main() {
  Game game;

  InitWindow(game.SCR_WIDTH, game.SCR_HEIGHT, "Snake");
  SetTargetFPS(game.GetFps());

  while (!WindowShouldClose()) {
   game.Run();
  }

  return 0;
}
