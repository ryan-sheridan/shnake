#ifndef SNAKE_H
#define SNAKE_H

#include "raylib.h"
#include <_stdio.h>
#include <stdlib.h>

#define SNAKE_LENGTH 100
#define GRID_SIZE 25
#define GRID_COLS 24
#define GRID_ROWS 24

typedef struct {
  int x, y;
} coord_t;

typedef enum {
  UP,
  DOWN,
  LEFT,
  RIGHT
} direction_t;

extern coord_t snake[SNAKE_LENGTH];
extern direction_t snake_direction;
extern int front, rear;
extern bool game_over;

bool is_empty(void);
bool is_full(void);
void insert_rear(coord_t pos);
void delete_front(void);
bool check_collision(coord_t pos);
bool move_snake(void);
void draw_snake(void);
void draw_grid(void);
void display(void);

#endif
