#include "snake.h"

bool is_empty(void) { return front == -1; }

bool is_full(void) { return (rear + 1) % SNAKE_LENGTH == front; }

void insert_rear(coord_t pos) {
  if (is_full()) {
    printf("snake overflow\n");
    return;
  }

  if (is_empty()) {
    front = rear = 0;
  } else {
    rear = (rear + 1) % SNAKE_LENGTH;
  }

  snake[rear] = pos;
}

void delete_front(void) {
  if (is_empty()) {
    printf("Snake underflow!\n");
    return;
  }

  if (front == rear) {
    front = rear = -1;
  } else {
    front = (front + 1) % SNAKE_LENGTH;
  }
}

void display(void) {
  if (is_empty()) {
    printf("deque is empty\n");
  }

  int i = front;
  while (1) {
    printf("(x:%d,y:%d) ", snake[i].x, snake[i].y);
    if (i == rear)
      break;
    i = (i + 1) % SNAKE_LENGTH;
  }
  printf("\n");
}

bool check_collision(coord_t pos) {
  if (pos.x < 0 || pos.x >= GRID_COLS || pos.y < 0 || pos.y >= GRID_ROWS) {
    return true;
  }

  if (!is_empty()) {
    int i = front;
    while (1) {
      if (snake[i].x == pos.x && snake[i].y == pos.y) {
        return true;
      }
      if (i == rear)
        break;
      i = (i + 1) % SNAKE_LENGTH;
    }
  }

  return false;
}

