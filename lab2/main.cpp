//
//  main.cpp
//  Lab 2 Pong Game
//
//  Created by Nathan Hung on 2024-09-11.
//  Modified by Salma Emara on 2024-09-11
//  Copyright © 2024 Nathan Hung. No rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//
//  ECE244 Student: Complete the skeletal code of the main function in this file

#include <string>

#include "Ball.h"
#include "Globals.h"
#include "Player.h"
#include "Screen.h"
#include "io.h"

int main() {
  int score = 0;
  bool gameEnded = false;
  std::string messageToPutOnScreen;

  std::chrono::steady_clock::time_point begin_time =
      std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point now_time;
  Screen screen = Screen();

  int ballCount = 0;
  const int max_ballCount = 5;

  Ball balls_array[max_ballCount];

  balls_array[0] = Ball(30.0, 30.0, 1.7, 0, ballCount);
  ballCount++;

  Player player = Player(0, 5, 10);

  while (!gameEnded) {
    // TODO: ECE 244 Student: Complete the game loop here only!
    // ECE 244 Student: DO NOT edit any other segments of this file!
    for (int j = 0; j < simulation_fps; j++) {
      char userInput = get_input();
      if (userInput != '\0') {
        if (userInput == 'q') {
          gameEnded = true;
        }
        player.update(userInput);
      }
      for (int i = 0; i < ballCount; i++) {
        balls_array[i].update();  // update the position of each ball
        balls_array[i].bounce(balls_array, ballCount,
                              player);  // check for collisions/overlaps

        if (balls_array[i].getX() <= 0) {
          gameEnded = true;
        }

        if (balls_array[i].overlap(player) ==
            HORIZONTAL_OVERLAP) {  // horizontal overlap means ball hits paddle
          score++;
          if (score % 2 == 0 && player.getHeight() > 3) {
            player.decreaseHeight(1);
          }
          if (score % 5 == 0 && ballCount < max_ballCount) {
            balls_array[ballCount] = Ball(30.0, 30.0, 0.9, 0.0, ballCount);
            ballCount++;
          }
        }
      }
    }

    for (int i = 0; i < ballCount; i++) {
      balls_array[i].draw(screen);  // draw the balls
    }

    player.draw(screen);  // and draw the player

    messageToPutOnScreen = "Your score is: " + std::to_string(score);
    screen.update(messageToPutOnScreen);

    // wait until 1/fps seconds
    while (std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::steady_clock::now() - begin_time)
               .count() < (long int)milliseconds_per_frame) {
    }
    begin_time = std::chrono::steady_clock::now();
  }
  messageToPutOnScreen = "Game over. Your score is: " + std::to_string(score);
  screen.update(messageToPutOnScreen);
  return 0;
}