//
//  Resistor.cpp
//  Lab 3 The Resistor Network Program
// Author: Kylie Ng
// Date: 10/12/2024

#include "Resistor.h"

#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

Resistor::Resistor(
    string name_, double resistance_,
    int endpoints_[2]) {  // sets name, resistance and endpoint node IDs
  name = name_;
  resistance = resistance_;
  endpointNodeIDs[0] = endpoints_[0];
  endpointNodeIDs[1] = endpoints_[1];
}

string Resistor::getName() {  // returns the name
  return name;
}

double Resistor::getResistance() {  // returns the resistance
  return resistance;
}

void Resistor::setResistance(double resistance_) {  // sets the resistance
  resistance = resistance_;
}

int Resistor::getOtherEndpoint(
    int nodeIndex) {  // returns the other node ID that the resistor is attached
                      // to (other than nodeIndex)
  if (endpointNodeIDs[0] == nodeIndex) {
    return endpointNodeIDs[1];
  } else if (endpointNodeIDs[1] == nodeIndex) {
    return endpointNodeIDs[0];
  } else {
    return -1;
  }
}

void Resistor::print() {  // prints resistor info
  cout << std::left << std::setw(20) << name << std::right << std::setw(8)
       << std::fixed << std::setprecision(2) << resistance << " Ohms "
       << endpointNodeIDs[0] << " -> " << endpointNodeIDs[1] << endl;
}