#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include "Customer.h"
#include "QueueList.h"
#include "Register.h"
#include "RegisterList.h"

using namespace std;

// Function Declarations:

// Set mode of the simulation
string getMode();

// Register
void parseRegisterAction(stringstream &lineStream, string mode);
void openRegister(
    stringstream &lineStream,
    string mode);  // register opens (it is upto customers to join)
void closeRegister(stringstream &lineStream,
                   string mode);  // register closes

// Customer
void addCustomer(stringstream &lineStream,
                 string mode);  // customer wants to join

// Helper functions
bool getInt(stringstream &lineStream, int &iValue);
bool getDouble(stringstream &lineStream, double &dValue);
bool foundMoreArgs(stringstream &lineStream);

// ADDED: MY OWN FUNCITON HEADERS
void printStatistics();
void doSystemUpdate(string mode);

// Global variables
RegisterList *registerList;  // holding the list of registers
QueueList *doneList;         // holding the list of customers served
QueueList *singleQueue;      // holding customers in a single virtual queue
double expTimeElapsed;  // time elapsed since the beginning of the simulation

// List of commands:
// To open a register
// register open <ID> <secPerItem> <setupTime> <timeElapsed>
// To close register
// register close <ID> <timeElapsed>
// To add a customer
// customer <items> <timeElapsed>

int main() {
  registerList = new RegisterList();
  doneList = new QueueList();
  singleQueue = new QueueList();
  expTimeElapsed = 0;

  // Set mode by the user
  string mode = getMode();

  string line;
  string command;

  cout << "> ";  // Prompt for input
  getline(cin, line);

  while (!cin.eof()) {
    stringstream lineStream(line);
    lineStream >> command;
    if (command == "register") {
      parseRegisterAction(lineStream, mode);
    } else if (command == "customer") {
      addCustomer(lineStream, mode);
    } else {
      cout << "Invalid operation" << endl;
    }
    cout << "> ";  // Prompt for input
    getline(cin, line);
  }

  // Print statistics
  printStatistics();

  // You have to make sure all dynamically allocated memory is freed
  // before return 0
  delete registerList;
  delete doneList;
  delete singleQueue;

  return 0;
}

void enqueueToRegister(Register *freeRegister) {
  Customer *nextCustomer = singleQueue->dequeue();
  if (nextCustomer != nullptr) {
    freeRegister->get_queue_list()->enqueue(nextCustomer);
    cout << "Queued a customer with free register " << freeRegister->get_ID()
         << endl;
  }
}

string getMode() {
  string mode;
  cout << "Welcome to ECE 244 Grocery Store Queue Simulation!" << endl;
  cout << "Enter \"single\" if you want to simulate a single queue or "
          "\"multiple\" to "
          "simulate multiple queues: \n> ";
  getline(cin, mode);

  if (mode == "single") {
    cout << "Simulating a single queue ..." << endl;
  } else if (mode == "multiple") {
    cout << "Simulating multiple queues ..." << endl;
  }
  return mode;
}

void addCustomer(stringstream &lineStream, string mode) {
  int items;
  double timeElapsed;
  if (!getInt(lineStream, items) || !getDouble(lineStream, timeElapsed)) {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments." << endl;
    return;
  }
  // Depending on the mode of the simulation (single or multiple),
  // add the customer to the single queue (single) or to the register with
  // fewest items (multiple)

  // Increment expTimeElapsed
  expTimeElapsed += timeElapsed;

  // Do System update
  doSystemUpdate(mode);

  // Add Customer
  Customer *newCustomer = new Customer(expTimeElapsed, items);
  cout << "A customer entered" << endl;
  if (mode == "single") {
    if (registerList->get_free_register() ==
        nullptr) {  // there are no free registers
      cout << "No free registers" << endl;
      singleQueue->enqueue(
          newCustomer);  // add that customer in the single queue
    } else {             // there is a free register
      registerList->get_free_register()->get_queue_list()->enqueue(newCustomer);
      cout << "Queued a customer with free register "
           << registerList->get_head()->get_ID() << endl;
    }
  } else if (mode == "multiple") {  // if mode == "multiple"
    cout << "Queued a customer with quickest register "
         << registerList->get_min_items_register()->get_ID() << endl;
    registerList->get_min_items_register()->get_queue_list()->enqueue(
        newCustomer);
  } else {
    delete newCustomer;
    cout << "No free registers" << endl;
  }
}

void parseRegisterAction(stringstream &lineStream, string mode) {
  string operation;
  lineStream >> operation;
  if (operation == "open") {
    openRegister(lineStream, mode);
  } else if (operation == "close") {
    closeRegister(lineStream, mode);
  } else {
    cout << "Invalid operation" << endl;
  }
}

void openRegister(stringstream &lineStream, string mode) {
  int ID;
  double secPerItem, setupTime, timeElapsed;
  // convert strings to int and double
  if (!getInt(lineStream, ID) || !getDouble(lineStream, secPerItem) ||
      !getDouble(lineStream, setupTime) ||
      !getDouble(lineStream, timeElapsed)) {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments" << endl;
    return;
  }
  // Check if the register is already open
  // If it's open, print an error message
  // Otherwise, open the register
  // If we were simulating a single queue,
  // and there were customers in line, then
  // assign a customer to the new register

  // TY JIA ON PIAZZA
  if (registerList->foundRegister(ID)) {  // if the register is open
    cout << "Error: register " << ID << " is already open"
         << endl;  // print an error message
    return;
  }

  // Increment expTimeElapsed
  expTimeElapsed += timeElapsed;

  // Do System Update
  doSystemUpdate(mode);

  // Open Register
  Register *newRegister =
      new Register(ID, secPerItem, setupTime, expTimeElapsed);
  registerList->enqueue(newRegister);  // open the register
  cout << "Opened register " << ID << endl;

  if (mode == "single" && (singleQueue->get_head() !=
                           nullptr)) {  // if we were simulating a single queue
                                        // and there were customers in line,
    newRegister->get_queue_list()->enqueue(
        singleQueue->dequeue());  // assign a customer to the new register
    cout << "Queued a customer with free register " << newRegister->get_ID()
         << endl;
  }
}

void closeRegister(stringstream &lineStream, string mode) {
  int ID;
  double timeElapsed;
  // convert string to int
  if (!getInt(lineStream, ID) || !getDouble(lineStream, timeElapsed)) {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments" << endl;
    return;
  }
  // Check if the register is open
  // If it is open dequeue it and free it's memory
  // Otherwise, print an error message
  if (registerList->foundRegister(ID) == false) {
    cout << "Error: register " << ID << " is not open" << endl;
    return;
  } else {
    // Increment expTimeElapsed
    expTimeElapsed += timeElapsed;

    // Do System Update
    doSystemUpdate(mode);

    // Close Register
    cout << "Closed register " << ID << endl;
    Register *closingRegister = registerList->dequeue(ID);  // dequeue it
    delete closingRegister;
    return;
  }
}

bool getInt(stringstream &lineStream, int &iValue) {
  // Reads an int from the command line
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  }
  iValue = stoi(command);
  return true;
}

bool getDouble(stringstream &lineStream, double &dvalue) {
  // Reads a double from the command line
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  }
  dvalue = stod(command);
  return true;
}

bool foundMoreArgs(stringstream &lineStream) {
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  } else {
    return true;
  }
}

// Process the customers at each register by checking if their checkout is
// complete. Move completed customers to doneList.
void doSystemUpdate(string mode) {
  Register *departingRegister =
      registerList->calculateMinDepartTimeRegister(expTimeElapsed);
  while (departingRegister != nullptr) {  // while there is a customer,
    // If the time taken to process the customer at the head of the queue of a
    // register has passed,
    if (departingRegister->calculateDepartTime() == -1) {
      return;
    }
    if (departingRegister->calculateDepartTime() > expTimeElapsed) {
      return;
    }
    if (departingRegister->calculateDepartTime() <= expTimeElapsed) {
      departingRegister->departCustomer(
          doneList);  // its departure time is updated, and the customer
                      // should leave the queue and get added to a linked list
                      // of customers that exited the system. this line does it
                      // all!
      if (mode == "single" && singleQueue->get_head() != nullptr) {
        enqueueToRegister(departingRegister);
      }
    }
    departingRegister =
        registerList->calculateMinDepartTimeRegister(expTimeElapsed);
  }
  return;
}

void printStatistics() {
  double totalWaitTime = 0.0;
  double maxWaitTime = 0.0;
  double waitTimeSumSq = 0.0;
  int numCustomers = 0;

  Customer *currentCustomer = doneList->get_head();

  while (currentCustomer != nullptr) {
    double waitTime = currentCustomer->get_departureTime() -
                      currentCustomer->get_arrivalTime();
    totalWaitTime += waitTime;

    if (waitTime > maxWaitTime) {
      maxWaitTime = waitTime;
    }

    waitTimeSumSq += (waitTime * waitTime);
    numCustomers++;

    currentCustomer =
        currentCustomer->get_next();  // Assuming you have a method to get the
                                      // next customer
  }

  double avgWaitTime = totalWaitTime / numCustomers;
  double stdDevWaitTime =
      sqrt((waitTimeSumSq / numCustomers) - (avgWaitTime * avgWaitTime));

  cout << "Finished at time " << expTimeElapsed << '\n'
       << "Statistics:" << endl;
  cout << "Maximum wait time: " << maxWaitTime << endl;
  cout << "Average wait time: " << avgWaitTime << endl;
  cout << "Standard Deviation of wait time: " << stdDevWaitTime << endl;
}