//
//  Node.cpp
//  Lab 3 The Resistor Network Program
// Author: Kylie Ng
// Date: 10/12/2024

#include "Node.h"

Node::Node() {  // sets numRes to 0, voltage to 0 and voltageIsSet to false
  numRes = 0;
  voltage = 0;
  voltageIsSet = false;
}

bool Node::canAddResistor() {  // returns if the numRes < MAX_RESISTORS_PER_NODE
  if (numRes < MAX_RESISTORS_PER_NODE) {
    return true;
  } else {
    return false;
  }
}

void Node::addResistor(
    int rIndex) {  // adds a resistor to resIDArray array and increments numRes
  resIDArray[numRes] = rIndex; // rIndex is the index of the resistor
  numRes++;
}

double Node::getVoltage() {  // returns voltage
  return voltage;
}

void Node::setVoltage(
    double voltage_) {  // sets voltage and sets voltageIsSet to true
  voltage = voltage_;
  voltageIsSet = true;
}

void Node::setVoltageInternally(  // sets voltage temporarily during iterations
                                  // for solve command
    double voltage_) {
  voltage = voltage_;
}

bool Node::isVoltageSet() {  // returns voltageIsSet
  return voltageIsSet;
}

int Node::getNumRes() {  // returns numRes
  return numRes;
}

int* Node::getResIDArray() {  // returns resIDArray
  return resIDArray;
}
