#include <Gamebuino-Meta.h>

// Ball
const int ball_size = 4;
int ball_posX = gb.display.width() / 2;
int ball_posY = gb.display.height() - 20;
int ball_speedX = 1;
int ball_speedY = -1;

// Racket
const int racket_width = gb.display.width() / 6;
const int racket_height = 3;
const int racket_posY = gb.display.height() - racket_height;
int racket_posX = gb.display.width() / 3;

// Bricks
const int bricks_number = 8;
const int brick_width = (gb.display.width() / bricks_number) - 2;
const int brick_height = 3;
const int lines_number = 5;
int bricks_line[lines_number][bricks_number];

// Functions
void update_ball_position(){
  ball_posX = ball_posX + ball_speedX;
  ball_posY = ball_posY + ball_speedY;
}

void move_racket(){
  if (gb.buttons.repeat(BUTTON_LEFT, 0)){
    racket_posX = racket_posX - 2;
  }
  if (gb.buttons.repeat(BUTTON_RIGHT, 0)){
    racket_posX = racket_posX + 2;
  }
}

void bouncing_ball_walls(){
  if (ball_posY < 0){
    ball_speedY = 1;
  }
  if (ball_posX < 0){
    ball_speedX = 1;
  }
  if (ball_posX + ball_size > gb.display.width()){
    ball_speedX = -1;
  }
}

void bouncing_ball_racket(){
  if (gb.collide.rectRect(ball_posX, ball_posY, ball_size, ball_size,
      racket_posX, racket_posY, racket_width, racket_height)){
      ball_speedY = -1;
  }
}

void bouncing_ball_bricks(){
  for(int i = 0; i < lines_number; i++){
    for(int j = 0; j < bricks_number; j++){
      // Compute brick’s positionX
      int position_x_brick = j * (brick_width + 2);
      int position_y_brick = i * (brick_height + 2);
      if (bricks_line[i][j] == 1){
        if (gb.collide.rectRect(ball_posX, ball_posY, ball_size, ball_size,
            position_x_brick, position_y_brick, brick_width, brick_height)){
          bricks_line[i][j] = 0;
          ball_speedY = -ball_speedY;
        }
      }
    }
  }
}

void reinit_ball(){
  ball_posX = gb.display.width() / 2;
  ball_posY = gb.display.height() - 20;
  ball_speedX = 1;
  ball_speedY = -1;
}

void ball_exit(){
  if (ball_posY + ball_size > gb.display.height()){
    reinit_ball();
  }
}

void init_bricks(){
  for(int i = 0; i < lines_number; i++){
    for(int j = 0; j < bricks_number; j++){
      bricks_line[i][j] = 1;
    }
  }
}

void display(){
  int still_bricks = false;
  for(int i = 0; i < lines_number; i++){
    for(int j = 0; j < bricks_number; j++){
      int position_x_brick = j * (brick_width + 2);
      int position_y_brick = i * (brick_height + 2);
      // Display untouched bricks (1: brick untouched, 0: brick touched)
      if (bricks_line[i][j] == 1){
        still_bricks = true;
        gb.display.fillRect(position_x_brick, position_y_brick, brick_width, brick_height);
      }
    }
  }
  if(! still_bricks){
    gb.display.println("Bravo !");
    gb.display.println();
    gb.display.println("Appuyer sur A pour relancer");
  } else {
    gb.display.fillRect(ball_posX, ball_posY, ball_size, ball_size);
    gb.display.fillRect(racket_posX, racket_posY, racket_width, racket_height);
  }
}

void new_game(){
  if(gb.buttons.repeat(BUTTON_A, 0)){
    init_bricks();
    reinit_ball();
    racket_posX = gb.display.width() / 3;
  }
}

void setup() {
  gb.begin();
  init_bricks();
}

void loop() {
  while (!gb.update());
  gb.display.clear();

  update_ball_position();

  move_racket();

  bouncing_ball_walls();

  bouncing_ball_bricks();

  bouncing_ball_racket();

  ball_exit();

  new_game();

  display();
}
