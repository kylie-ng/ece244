//
//  Triangle.h
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

#include <cmath>
#ifndef Triangle_h
#define Triangle_h

#include <iostream>
#include <string>
using namespace std;

// This class implements the triangle Shape objects.
// ECE244 Student: Write the definition of the class here.
#include "Shape.h"

class Triangle : public Shape {
 private:
  float x_centre;
  float y_centre;
  float x1;
  float y1;
  float x2;
  float y2;
  float x3;
  float y3;

 public:
  // Constructor
  Triangle(string n, float xcent, float ycent, float xOne, float yOne,
           float xTwo, float yTwo, float xThree, float yThree);

  // Destructor
  virtual ~Triangle();

  // Accessor
  float getX1() const;
  float getY1() const;
  float getX2() const;
  float getY2() const;
  float getX3() const;
  float getY3() const;

  // Mutator
  void setX1(float xOne);
  void setY1(float yOne);
  void setX2(float xTwo);
  void setY2(float yTwo);
  void setX3(float xThree);
  void setY3(float yThree);

  // Utility methods
  virtual void draw() const;

  virtual float computeArea() const;

  virtual Shape* clone() const;
};

#endif /* Triangle_h */