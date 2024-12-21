#include "RegisterList.h"

#include <iostream>

#include "Register.h"
using namespace std;

RegisterList::RegisterList() {
  head = nullptr;
  size = 0;
}

RegisterList::~RegisterList() { delete head; }

Register* RegisterList::get_head() { return head; }

int RegisterList::get_size() {
  // return number of registers
  return size;
}

Register* RegisterList::get_min_items_register() {
  // loop all registers to find the register with least number of items
  Register* temp = head;
  if (temp == nullptr) {
    return nullptr;
  }
  int leastNumOfItems = temp->get_queue_list()->get_items();
  Register* least = temp;
  while (temp != nullptr) {
    if (temp->get_queue_list()->get_items() < leastNumOfItems) {
      leastNumOfItems = temp->get_queue_list()->get_items();  // updating least
      least = temp;
    }
    temp = temp->get_next();
  }
  return least;
}

Register* RegisterList::get_free_register() {
  // return the register with no customers
  // if all registers are occupied, return nullptr
  Register* temp = head;
  while (temp != nullptr) {
    if (temp->get_queue_list()->get_head() ==
        nullptr) {  // indicates no customers, there is a free register
      return temp;
    }
    temp = temp->get_next();
  }
  return nullptr;
}

void RegisterList::enqueue(Register* newRegister) {
  // a register is placed at the end of the queue
  // if the registers list is empty, the register becomes the head
  // Assume the next of the newRegister is set to null
  // You will have to increment size
  size++;
  Register* temp = head;
  if (temp == nullptr) {
    head = newRegister;
    return;
  }
  while (temp->get_next() != nullptr) {
    temp = temp->get_next();
  }
  temp->set_next(newRegister);
}

bool RegisterList::foundRegister(int ID) {
  // look for a register with the given ID
  // return true if found, false otherwise
  Register* temp = head;
  if (temp == nullptr) {
    return false;
  }
  while (temp != nullptr) {
    if (ID == temp->get_ID()) {
      return true;
    }
    temp = temp->get_next();
  }
  return false;
}

Register* RegisterList::dequeue(int ID) {
  // dequeue the register with given ID
  // return the dequeued register
  // return nullptr if register was not found
  Register* current = head;
  Register* prev;

  // if register with the id is not found
  if (!foundRegister(ID)) {
    return nullptr;
  }

  // If linked list is empty
  if (current == nullptr) {
    return nullptr;
  }

  // If ID found at front of linked list
  if (current->get_ID() == ID) {
    head = current->get_next();
    current->set_next(NULL);
    return current;
  }

  // If ID found elsewhere
  while (current != nullptr) {
    if (current->get_ID() == ID) {
      // found the node to remove
      if (prev != nullptr) {
        prev->set_next(current->get_next());
      }
      current->set_next(nullptr);
      return current;
    }
    prev = current;
    current = current->get_next();
  }
  return nullptr;
}

// prof salma helped :)
Register* RegisterList::calculateMinDepartTimeRegister(double expTimeElapsed) {
  // return the register with minimum time of departure of its customer
  // if all registers are free, return nullptr
  /*Register* temp = head;
  Register* least = head;
  bool allFree = true;
  if (head == nullptr) {
    return nullptr;
  }
  while (temp != nullptr) {
    double departTimeDouble = temp->calculateDepartTime();
    if (departTimeDouble <= expTimeElapsed) {  // if it's supposed to depart
      if (departTimeDouble != -1) {            // not free
        allFree = false;
      }
      if ((departTimeDouble != -1) &&
          departTimeDouble < least->calculateDepartTime()) {
        least = temp;
      }
    }
    temp = temp->get_next();
  }
  if (allFree) {
    return nullptr;
  }
  return least;*/
  Register* temp = head;
  Register* least = head;
  double neverTime = 999999999999999.0; // max double is 15 digits
  if (head != NULL) {
    while (temp != NULL) {
      Customer* headCustomer = temp->get_queue_list()->get_head();
      if (headCustomer != NULL) {
        double departTime = temp->calculateDepartTime();
        if (departTime < neverTime) {
          neverTime = departTime;
          least = temp;
        }
      }
      temp = temp->get_next();
    }
    return least;
  }
  return least;
}

void RegisterList::print() {
  Register* temp = head;
  while (temp != nullptr) {
    temp->print();
    temp = temp->get_next();
  }
}
