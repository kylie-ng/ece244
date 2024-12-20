//
//  main.cpp
//  Lab 3 The Resistor Network Program
//
//  Created by Nathan Hung on 2024-09-11.
//  Modified by Salma Emara on 2024-09-30
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//
//  ECE244 Student: Complete the skeletal code of the main function in this file

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "Node.h"
#include "Resistor.h"

using namespace std;

Resistor** resistors =
    nullptr;  // Pointer that should point to an array of Resistor pointers
Node* nodes = nullptr;  // pointer that should hold address to an array of Nodes
int maxNodeNumber = 0;  // maximum number of nodes as set in the command line
int maxResistors = 0;  // maximum number of resistors as set in the command line
int resistorsCount = 0;  // count the number of resistors

string errorArray[10] = {
    "invalid command",                                  // 0
    "invalid argument",                                 // 1
    "negative resistance",                              // 2
    "node value is out of permitted range",             // 3
    "resistor name cannot be keyword \"all\"",          // 4
    "both terminals of resistor connect to same node",  // 5
    "too few arguments",                                // 6
};

// Function Prototypes
bool getInteger(stringstream& ss, int& x);
bool getString(stringstream& ss, string& s);
bool getDouble(stringstream& ss, double& s);

void handleMaxVal(stringstream& ss);
void handleInsertR(stringstream& ss);
void handleModifyR(stringstream& ss);
void handlePrintR(stringstream& ss);
void handleDeleteR(stringstream& ss);
void handleSetV(stringstream& ss);

int main() {
  string line;
  cout << ">>> ";
  cout.flush();
  getline(cin, line);   // read user input line
  while (!cin.eof()) {  // while not the end of the input line
    line.erase(line.find_last_not_of(" \t\n\r\f\v") +
               1);                      // citation: piazza post Question @569
    stringstream myStringStream(line);  // initialize stringstream w/ input line
    string command;
    if (getString(myStringStream, command)) {  // get command
      if (command == "maxVal") {
        handleMaxVal(myStringStream);
      } else if (command == "insertR") {
        handleInsertR(myStringStream);
      } else if (command == "modifyR") {
        handleModifyR(myStringStream);
      } else if (command == "printR") {
        handlePrintR(myStringStream);
      } else if (command == "deleteR") {
        handleDeleteR(myStringStream);
      } else if (command == "setV") {
        handleSetV(myStringStream);
      } else {
        cout << "Error: " << errorArray[0] << endl;
      }
    } else {
      cout << "Error: " << errorArray[0] << endl;
    }
    cout << ">>> ";
    getline(cin, line);
  }

  // Deallocate memory in case
  for (int i = 0; i < resistorsCount; i++) {
    delete resistors[i];
  }
  delete[] resistors;
  delete[] nodes;

  return 0;
}

// TODO: Implement functions here
bool getInteger(stringstream& ss, int& x) {
  if (!ss.eof()) {
    ss >> x;          // read it
    if (ss.fail()) {  // reading it will cause the flag if not an int
      cout << "Error: " << errorArray[1] << endl;
      ss.clear();
      ss.ignore(888, '\n');
      return false;
    } else {
      return true;
    }
  } else {
    cout << "Error: " << errorArray[6] << endl;
    return false;
  }
}

bool getString(stringstream& ss, string& s) {
  if (!ss.eof()) {
    ss >> s;
    if (ss.fail()) {
      cout << "Error: " << errorArray[1] << endl;
      ss.clear();
      ss.ignore(888, '\n');
      return false;
    } else {
      return true;
    }
  } else {
    cout << "Error: " << errorArray[6] << endl;
    return false;
  }
}

bool getDouble(stringstream& ss, double& s) {
  if (!ss.eof()) {
    ss >> s;
    if (ss.fail()) {
      cout << "Error: " << errorArray[1] << endl;
      ss.clear();
      ss.ignore(888, '\n');
      return false;
    } else {
      return true;
    }
  } else {
    cout << "Error: " << errorArray[6] << endl;
    return false;
  }
}

void handleMaxVal(stringstream& ss) {
  if (getInteger(ss, maxNodeNumber) && getInteger(ss, maxResistors)) {
    cout << "New network: max node number is " << maxNodeNumber
         << "; max resistors is " << maxResistors << endl;
    if (resistors != nullptr /*|| nodes != nullptr*/) {
      for (int i = 0; i < resistorsCount; i++) {
        delete resistors[i];
        resistors[i] = nullptr;
      }
      delete[] resistors;
      resistors = nullptr;
      delete[] nodes;
      nodes = nullptr;
    }
    nodes = new Node[maxNodeNumber + 1];
    resistors = new Resistor*[maxResistors];
    resistorsCount = 0;
  }
}

bool resistorExists(Resistor* resistors[], string name) {
  for (int i = 0; i < resistorsCount; i++) {
    if ((resistors[i] != nullptr) &&
        name ==
            resistors[i]->getName()) {  // equivalent to *(resistors[i]).getName
      return true;
    }
  }
  return false;
}

Resistor* findResistor(string name) {
  for (int i = 0; i < resistorsCount; i++) {
    if ((resistors[i] != nullptr) && name == resistors[i]->getName()) {
      return resistors[i];
    }
  }
  return nullptr;
}

void handleInsertR(stringstream& ss) {
  string name;
  double resistance = 0.0;
  int endpointNodeIDs[2] = {0};
  int nodeid0 = 0, nodeid1 = 0;

  if (getString(ss, name)) {
    if (name == "all") {
      cout << "Error: " << errorArray[4] << endl;
      return;
    } else if (resistorExists(resistors, name)) {
      cout << "Error: resistor " << name << " already exists" << endl;
      return;
    }
    if (getDouble(ss, resistance)) {
      if (resistance < 0.0) {
        cout << "Error: " << errorArray[2] << endl;
      } else if (getInteger(ss, nodeid0)) {
        endpointNodeIDs[0] = nodeid0;  // here
        if (getInteger(ss, nodeid1)) {
          if (nodeid0 != nodeid1) {
            if (nodes->canAddResistor()) {
              endpointNodeIDs[1] = nodeid1;
              resistors[resistorsCount] =
                  new Resistor(name, resistance, endpointNodeIDs);
              resistorsCount++;
              nodes->addResistor(resistorsCount);
              cout << "Inserted: resistor " << name << " " << std::fixed
                   << std::setprecision(2) << resistance << " Ohms "
                   << endpointNodeIDs[0] << " -> " << endpointNodeIDs[1]
                   << endl;
            } else {
              cout << "Error: " << errorArray[3] << endl;
            }
          } else {
            cout << "Error: " << errorArray[5] << endl;
          }
        }
      }
    }
  }
}

void handleModifyR(stringstream& ss) {
  string name;
  double resistance = 0.0;
  if (getString(ss, name)) {
    if (name == "all") {
      cout << "Error: " << errorArray[4] << endl;
      return;
    } else if (!resistorExists(
                   resistors,
                   name)) {  // reused function of "resistor exists" to be
                             // applied for "resistor not found"
      cout << "Error: resistor " << name << " not found" << endl;
      return;
    }
    if (getDouble(ss, resistance)) {
      cout << "Modified: resistor " << name << "from "
           << findResistor(name)->getResistance() << " Ohms to " << std::fixed
           << std::setprecision(2) << resistance << " Ohms" << endl;
      findResistor(name)->setResistance(resistance);
    }
  }
}

void handlePrintR(stringstream& ss) {
  string name;
  if (getString(ss, name)) {
    if (name == "all") {
      for (int i = 0; i < resistorsCount; i++) {
        if (resistors[i]) {
          resistors[i]->print();
        }
      }
    } else if (!resistorExists(
                   resistors,
                   name)) {  // reused function of "resistor exists" to be
                             // applied for "resistor not found"
      cout << "Error: resistor " << name << " not found" << endl;
      return;
    } else {
      cout << "Print:" << endl;
      findResistor(name)->print();  // the given code in Resistor.cpp function
                                    // takes care of that for me already
    }
  }
}

void handleDeleteR(stringstream& ss) {
  string name;
  if (getString(ss, name)) {
    if (name == "all") {
      for (int i = 0; i < resistorsCount; i++) {
        delete resistors[i];
        resistors[i] = nullptr;
      }
      delete[] resistors;
      resistors = nullptr;
      delete[] nodes;
      nodes = nullptr;
      resistorsCount = 0;
    }
  } else {
    cout << "Error: " << errorArray[6] << endl;
  }
  cout << "Deleted: all resistors" << endl;
}

void handleSetV(stringstream& ss) {
  int nodeid = 0;
  double voltage = 0.0;
  if (getInteger(ss, nodeid)) {
    if (getDouble(ss, voltage)) {
      if (nodeid >= 0 && nodeid <= maxNodeNumber) {
        nodes[nodeid].setVoltage(voltage);
        cout << "Set: node " << nodeid << " to " << voltage << " Volts" << endl;
        return;
      } else {
        cout << "Error: " << errorArray[3] << endl;
      }
    }
  }
}