//
//  Triangle.cpp
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Write the implementation of the class Triangle here

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#include "Shape.h"
#include "Triangle.h"

// Build a Triangle object
Triangle::Triangle(string n, float xcent, float ycent, float xOne, float yOne, float xTwo, float yTwo,
                   float xThree, float yThree)
    : Shape(n, xcent, ycent) {
  xcent = (xOne + xTwo + xThree) / 3.0f;
  ycent = (yOne + yTwo + yThree) / 3.0f;
  x_centre = xcent;
  y_centre = ycent;
  x1 = xOne;
  y1 = yOne;
  x2 = xTwo;
  y2 = yTwo;
  x3 = xThree;
  y3 = yThree;
}

Triangle::~Triangle() {
  // Nothing to do
}

// Accessor
float Triangle::getX1() const { return x1; }
float Triangle::getY1() const { return y1; }
float Triangle::getX2() const { return x2; }
float Triangle::getY2() const { return y2; }
float Triangle::getX3() const { return x3; }
float Triangle::getY3() const { return y3; }

// Mutator
void Triangle::setX1(float xOne) { x1 = xOne; }
void Triangle::setY1(float yOne) { y1 = yOne; }
void Triangle::setX2(float xTwo) { x2 = xTwo; }
void Triangle::setY2(float yTwo) { y2 = yTwo; }
void Triangle::setX3(float xThree) { x3 = xThree; }
void Triangle::setY3(float yThree) { y3 = yThree; }

void Triangle::draw() const {
  // Set floating point printing to fixed point with 2 decimals
  cout << std::fixed;
  cout << std::setprecision(2);

  // Print the information
  cout << "triangle: " << name << " " << x_centre << " " << y_centre << " "
       << x1 << " " << y1 << " " << x2 << " " << y2 << " " << x3 << " " << y3
       << " " << computeArea() << endl;
}

float Triangle::computeArea() const {
  return (0.5f * abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)));
}

Shape* Triangle::clone() const { return (new Triangle(*this)); }
