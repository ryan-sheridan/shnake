#include "raylib.h"
#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

coord_t snake[SNAKE_LENGTH];
direction_t snake_direction;
int front = -1;
int rear = -1;
bool game_over = false;
int screenWidth = 600;
int screenHeight = 600;

int frame_counter = 0;
int move_interval = 10;

void draw_snake_node(int x, int y, Color color) {
  DrawRectangle(x * GRID_SIZE + 1, y * GRID_SIZE + 1, GRID_SIZE - 2,
                GRID_SIZE - 2, color);
}

void draw_grid(void) {
  for (int x = 0; x <= GRID_COLS; x++) {
    DrawLine(x * GRID_SIZE, 0, x * GRID_SIZE, GRID_ROWS * GRID_SIZE, DARKGRAY);
  }

  for (int y = 0; y <= GRID_ROWS; y++) {
    DrawLine(0, y * GRID_SIZE, GRID_COLS * GRID_SIZE, y * GRID_SIZE, DARKGRAY);
  }
}

bool move_snake(void) {
  if (is_empty())
    return false;

  coord_t new_head = snake[rear];

  switch (snake_direction) {
  case (UP):
    new_head.y--;
    break;
  case (DOWN):
    new_head.y++;
    break;
  case (LEFT):
    new_head.x--;
    break;
  case (RIGHT):
    new_head.x++;
    break;
  }

  if (check_collision(new_head)) {
    return false;
  }

  insert_rear(new_head);

  delete_front();

  return true;
}

void draw_snake(void) {
  if (is_empty()) {
    return;
  }

  int i = front;
  bool is_head = true;

  while (1) {
    Color color = is_head ? LIME : GREEN;
    draw_snake_node(snake[i].x, snake[i].y, color);
    if (i == rear)
      break;
    i = (i + 1) % SNAKE_LENGTH;
    is_head = false;
  }
}

void handle_input(void) {
  if (IsKeyPressed(KEY_UP) && snake_direction != DOWN) {
    snake_direction = UP;
  }
  if (IsKeyPressed(KEY_DOWN) && snake_direction != UP) {
    snake_direction = DOWN;
  }
  if (IsKeyPressed(KEY_LEFT) && snake_direction != RIGHT) {
    snake_direction = LEFT;
  }
  if (IsKeyPressed(KEY_RIGHT) && snake_direction != LEFT) {
    snake_direction = RIGHT;
  }
}

int main(void) {
  SetConfigFlags(FLAG_WINDOW_HIGHDPI);
  InitWindow(screenWidth, screenHeight, "shnake");
  SetTargetFPS(60);

  snake_direction = RIGHT;

  insert_rear((coord_t){5, 12});
  insert_rear((coord_t){6, 12});
  insert_rear((coord_t){7, 12});
  insert_rear((coord_t){8, 12});

  while (!WindowShouldClose()) {
    handle_input();

    if (!game_over) {
      frame_counter++;
      if (frame_counter >= move_interval) {
        frame_counter = 0;
        if (!move_snake()) {
          game_over = true;
        }
      }
    }

    if (game_over && (GetKeyPressed() != 0)) {
      game_over = false;
      front = rear = -1;
      snake_direction = RIGHT;
      frame_counter = 0;

      insert_rear((coord_t){5, 12});
      insert_rear((coord_t){6, 12});
      insert_rear((coord_t){7, 12});
      insert_rear((coord_t){8, 12});
    }

    BeginDrawing();
    ClearBackground(BLACK);

    if (!game_over) {
      draw_grid();
      draw_snake();
    } else {
      const char *game_over_text = "game over";
      const char *restart_text = "press any key to restart";

      int text_width = MeasureText(game_over_text, 40);
      int restart_width = MeasureText(restart_text, 20);

      DrawText(game_over_text, (screenWidth - text_width) / 2,
               screenHeight / 2 - 20, 40, RED);
      DrawText(restart_text, (screenWidth - restart_width) / 2,
               screenHeight / 2 + 30, 20, LIGHTGRAY);
    }

    EndDrawing();
  }
  CloseWindow();
  return 0;
}
