#include "Register.h"

#include <iostream>

Register::Register(int id, double timePerItem, double overhead,
                   double entryTime) {
  ID = id;
  secPerItem = timePerItem;
  overheadPerCustomer = overhead;
  availableTime = entryTime;
  next = nullptr;           // no other registers yet
  queue = new QueueList();  // no customers in line yet, but has to initialize a
                            // queue
}

Register::~Register() {
  delete next;
  delete queue;
}

QueueList* Register::get_queue_list() { return queue; }

Register* Register::get_next() { return next; }

int Register::get_ID() { return ID; }

double Register::get_secPerItem() { return secPerItem; }

double Register::get_overheadPerCustomer() { return overheadPerCustomer; }

double Register::get_availableTime() { return availableTime; }

void Register::set_next(Register* nextRegister) { next = nextRegister; }

void Register::set_availableTime(double availableSince) {
  availableTime = availableSince;
}

double Register::calculateDepartTime() {
  // Get the departure time of the first customer in the queue
  // returns -1 if no customer is in the queue
  if (queue->get_head() == nullptr) {
    return -1;
  } else {
    double processingTime = 0.0;
    processingTime =
        queue->get_head()->get_numOfItems() * secPerItem + overheadPerCustomer;
    double departureTime = 0.0;
    if (queue->get_head()->get_arrivalTime() > availableTime) {
      departureTime = processingTime + queue->get_head()->get_arrivalTime();
    } else {
      departureTime = processingTime + availableTime;
    }
    return departureTime;
  }
}

void Register::departCustomer(QueueList* doneList) {
  // dequeue the head, set last dequeue time [departureTime, outtaHereCustomer
  // left at __ seconds], add to doneList, update availableTime of the register
  double departTime = calculateDepartTime();
  Customer* outtaHereCustomer = queue->dequeue();
  if (outtaHereCustomer == nullptr) {
    return;
  }
  outtaHereCustomer->set_departureTime(departTime);
  doneList->enqueue(outtaHereCustomer);
  availableTime = departTime;
  std::cout << "Departed a customer at register ID " << ID << " at "
            << departTime << std::endl;
}

void Register::print() {
  std::cout << "Register ID: " << ID << std::endl;
  std::cout << "Time per item: " << secPerItem << std::endl;
  std::cout << "Overhead per customer: " << overheadPerCustomer << std::endl;
  if (queue->get_head() != nullptr) {
    std::cout << "Queue has customers: \n";
    queue->print();
  }
}