//
//  Player.cpp
//  Lab 2 Pong Game
//
//  Created by Kylie Ng on 2024-10-05

#include "Player.h"

#include "Globals.h"

// Default Constructor
Player::Player() {
  x = 0.0;
  y = 0.0;
  height = 0;
  width = 1;
};

// Constructor
Player::Player(double X, double Y, int Height) {
  x = X;
  y = Y;
  height = Height;
  width = 1;
};

// Functions using Player.h
double Player::getX() { return x; }

double Player::getY() { return y; }

int Player::getHeight() { return height; }

int Player::getWidth() { return width; }

void Player::decreaseHeight(int delta_to_decrease_by) {
  height -= delta_to_decrease_by;
}

void Player::update(char c) {
  if ((c == 'A') && (y + height < HEIGHT - 1)) {
    y += 2;
  } else if ((c == 'B') && (y > 0)) {
    y -= 2;
  }

  //  Ensure it doesn't exceed game boundaries
  if (y < 0) {
    y = 0;
  }
  if (y + height > HEIGHT - 1) {
    y = HEIGHT - 1 - height;
  }
}

void Player::draw(Screen &screen_to_draw_to) {
  for (int i = 0; i < height; i++) {
    screen_to_draw_to.addPixel(x, y + i, '#');
  }
}