#include <Gamebuino-Meta.h>

int ball_posX = 20;
int ball_posY = 20;
int ball_speedX = 1;
int ball_speedY = 1;
int ball_size = 4;

int racket1_posX = 10;
int racket1_posY = 30;

int racket2_posX = 65;
int racket2_posY = 30;

int racket_height = 12;
int racket_width = 3;

int score1 = 0;
int score2 = 0;

void setup() {
  gb.begin();
}

void loop() {
  while (!gb.update());
  gb.display.clear();

  ball_posX = ball_posX + ball_speedX;
  ball_posY = ball_posY + ball_speedY;

  if (gb.buttons.repeat(BUTTON_UP, 0)){
    racket1_posY = racket1_posY - 1;
  }
  if (gb.buttons.repeat(BUTTON_DOWN, 0)){
    racket1_posY = racket1_posY + 1;
  }

  if (gb.buttons.repeat(BUTTON_B, 0)){
    racket2_posY = racket2_posY - 1;
  }
  if (gb.buttons.repeat(BUTTON_A, 0)){
    racket2_posY = racket2_posY + 1;
  }

  if (ball_posY < 0){
    ball_speedY = 1;
  }

  if (ball_posY > gb.display.height() - ball_size){
    ball_speedY = -1;
  }

  if ((ball_posX < 0) || (ball_posX > gb.display.width())){
    if (ball_posX < 0){
        score2 = score2 + 1;
    }
    if (ball_posX + ball_size > gb.display.width()){
        score1 = score1 + 1;
    }
    ball_posX = 20;
    ball_posY = 20;
    ball_speedX = 1;
    ball_speedY = 1;
  }

  if(gb.collide.rectRect(racket1_posX, racket1_posY, racket_width, racket_height,
                            ball_posX, ball_posY, ball_size, ball_size)){
    ball_speedX = 1;
  }
  if(gb.collide.rectRect(racket2_posX, racket2_posY, racket_width, racket_height,
                            ball_posX, ball_posY, ball_size, ball_size)){
    ball_speedX = -1;
  }

  gb.display.setCursor(35, 5);
  gb.display.print(score1);
  gb.display.setCursor(42, 5);
  gb.display.print(score2);

  gb.display.fillRect(ball_posX, ball_posY, ball_size, ball_size);
  gb.display.fillRect(racket1_posX, racket1_posY, racket_width, racket_height);
  gb.display.fillRect(racket2_posX, racket2_posY, racket_width, racket_height);
}
