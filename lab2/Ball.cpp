//
//  Ball.cpp
//  Lab 2 Pong Game
//
//  Created by Kylie Ng on 2024-10-05

#include "Ball.h"

#include "Globals.h"

// Default Constructor
Ball::Ball() {
  x = 0.0;
  y = 0.0;
  velocity_x = 0.0;
  velocity_y = 0.0;
  id = 0;
  width = 1;
  height = 1;
};

// Constructor
Ball::Ball(double X, double Y, double velocity_X, double velocity_Y, int ID) {
  x = X;
  y = Y;
  velocity_x = velocity_X;
  velocity_y = velocity_Y;
  id = ID;
  width = 1;
  height = 1;
};

double Ball::getX() { return x; };

int Ball::getID() { return id; };

void Ball::update() {
  velocity_y = velocity_y - 0.02 * timeStep;  // given
  x += velocity_x * timeStep;  // x coordinate plus the x displacement
  y += velocity_y * timeStep;  // y coordinate plus the y displacement
};

int Ball::overlap(Ball& b) {
  if (((x + width <= b.x) || (y + height <= b.y)) ||
      ((b.x + b.width <= x) || (b.y + b.height <= y))) {
    return NO_OVERLAP;
  } else if (abs((x + width) - (b.x + b.width)) <=
             abs((y + height) - (b.y + b.height))) {
    return HORIZONTAL_OVERLAP;
  } else /*if (abs((x + width) - (b.x + b.width)) <
             abs((y + height) - (b.y + b.height)))*/
  {
    return VERTICAL_OVERLAP;
  }
};

int Ball::overlap(Player& p) {
  if (((x + width <= p.getX()) || (y + height <= p.getY())) ||
      ((p.getX() + p.getWidth() <= x) || (p.getY() + p.getHeight() >= y))) {
    return NO_OVERLAP;
  } else if (abs((x + width) - (p.getX() + 1)) <=
             abs((y + height) - (p.getY() + p.getHeight()))) {
    return HORIZONTAL_OVERLAP;
  } else /*if (abs((x + width) - (p.getX() + 1)) <
             abs((y + height) - (p.getY() + p.getHeight())))*/
  {
    return VERTICAL_OVERLAP;
  }
};

void Ball::bounce(Ball arr[], int ballCount, Player player) {
  // Check if current ball bounces off the walls
  if ((x + width >= WIDTH - 1) ||
      (x <= 0)) {  // ball location is at or beyond vertical walls
    velocity_x *= -1;
  } else if ((y + height >= HEIGHT - 1) ||
             (y <=
              0)) {  // ball location is on ground or beyond horizontal walls
    velocity_y *= -1;
  }

  // Check if current ball bounces off any other ball
  for (int i = 0; i < ballCount; i++) {
    if (getID() != arr[i].getID()) {
      if (overlap(arr[i]) == HORIZONTAL_OVERLAP) {
        velocity_x *= -1;
      } else if (overlap(arr[i]) == VERTICAL_OVERLAP) {
        velocity_y *= -1;
      }
    }
  }

  // Check if current ball bounces of the paddle of the player
  if (overlap(player) == HORIZONTAL_OVERLAP) {
    velocity_x *= -1;
  } /*else if (overlap(player) == VERTICAL_OVERLAP) {
    velocity_y *= -1;
  }*/
  /*if ((x == player.getX() + 1) &&
      (y + height <= player.getY() + player.getHeight()) &&
      (y >= player.getY())) {
    velocity_x *= -1;
  }*/
};

void Ball::draw(Screen& screen_to_draw_to) {
  screen_to_draw_to.addPixel(x, y, 'o' /*+ id*/);
};
