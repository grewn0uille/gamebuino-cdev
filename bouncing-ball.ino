#include <Gamebuino-Meta.h>

int positionX = 22;
int positionY = 32;
int speedX = 1;
int speedY = 1;
int ball_size = 4;

void setup() {
  gb.begin();
}

void loop() {
  while (!gb.update());
  gb.display.clear();

  positionX = positionX + speedX;
  positionY = positionY + speedY;

  if(positionX < 0){
    speedX = -speedX;
  }
  if(positionY < 0){
      speedY = -speedY;
  }

  if(positionX + ball_size > gb.display.width()){
    speedX = -speedX;
  }
  if(positionY + ball_size > gb.display.height()){
    speedY = -speedY;
  }

  gb.display.fillRect(positionX, positionY, ball_size, ball_size);
}
