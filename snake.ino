#include <GameBoy.h>

GameBoy gb;

const int SNAKE_MAX_LEN = 10;
int snake_len = 1;
int snake_x[SNAKE_MAX_LEN], snake_y[SNAKE_MAX_LEN];

const int SNAKE_MAX_SPEED = 1000;
const int snake_speed = 10;
unsigned long snake_last_move_time = 0;

int dir_x, dir_y;
int food_x, food_y;

void setup() {
	Serial.begin(9600);
  gb.begin(7);

  randomSeed(analogRead(A0));

  snake_x[0] = random(8);
  snake_y[0] = random(16);
  dir_x = 1;
  dir_y = 0;

  food_x = random(8);
  food_y = random(16);
}

void loop() {
  change_dir();
  move_snake();
	check_game_over();
  check_food();
  draw();
}

void change_dir() {
  if (gb.getKey() == 3 && dir_y != 1) {  //up
    dir_x = 0;
    dir_y = -1;
  }
  if (gb.getKey() == 6 && dir_y != -1) {  // down
    dir_x = 0;
    dir_y = 1;
  }
  if (gb.getKey() == 4 && dir_x != 1) {  // left
    dir_x = -1;
    dir_y = 0;
  }
  if (gb.getKey() == 5 && dir_x != -1) {  // right
    dir_x = 1;
    dir_y = 0;
  }
}

void move_snake() {
  if (millis() - snake_last_move_time < SNAKE_MAX_SPEED / snake_speed)
    return;

  for (int i = snake_len - 1; i > 0; --i) {
    snake_x[i] = snake_x[i - 1];
    snake_y[i] = snake_y[i - 1];
  }

  snake_x[0] += dir_x;
  snake_y[0] += dir_y;
  if (snake_x[0] > 7) snake_x[0] = 0;
  if (snake_x[0] < 0) snake_x[0] = 7;
  if (snake_y[0] > 15) snake_y[0] = 0;
  if (snake_y[0] < 0) snake_y[0] = 15;

  snake_last_move_time = millis();
}

void check_game_over() {
	for (int i = 1; i < snake_len; ++i) {
		if (snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i]) {
			gb.sound(COLLISION);
			gb.clearDisplay();

			for (int x = 0; x < 8; ++x) {
				for (int y = 0; y < 16; ++y) {
					gb.drawPoint(x, y);
					delay(50);
				}
			}

			snake_len = 1;
			snake_x[0] = random(8);
			snake_y[0] = random(16);
			dir_x = 0;
			dir_y = 0;
		}
	}
}

void check_food() {
  if (snake_x[0] == food_x && snake_y[0] == food_y) {
		gb.sound(SCORE);
    food_x = random(8);
    food_y = random(16);

    snake_x[snake_len] = snake_x[snake_len - 1] - dir_x;
    snake_y[snake_len] = snake_y[snake_len - 1] - dir_y;
    snake_len = snake_len + 1 >= SNAKE_MAX_LEN ? snake_len : snake_len + 1;
  }
}

void draw() {
  gb.clearDisplay();
  gb.drawPoint(food_x, food_y);

  for (int i = 0; i < snake_len; ++i) {
    gb.drawPoint(snake_x[i], snake_y[i]);
  }
}

