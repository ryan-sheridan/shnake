#include "raylib.h"

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  SetConfigFlags(FLAG_WINDOW_HIGHDPI);

  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(BLACK);

    DrawText("Congrats! You created your first window!", 10, 10, 20,
             WHITE);
    DrawCircle(screenWidth / 2, screenHeight / 2, screenWidth / 10, DARKBLUE);

    EndDrawing();
  }
  CloseWindow();
  return 0;
}
