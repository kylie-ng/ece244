#include "QueueList.h"

#include "Customer.h"

QueueList::QueueList() { head = nullptr; }

QueueList::QueueList(Customer* customer) {
  head = customer;
  if (customer != nullptr) {
    customer->set_next(nullptr);
  }
}

QueueList::~QueueList() { delete head; }

Customer* QueueList::get_head() { return head; }

void QueueList::enqueue(Customer* customer) {
  // a customer is placed at the end of the queue
  // if the queue is empty, the customer becomes the head
  Customer* temp = head;
  if (temp == nullptr) {
    head = customer;
    return;
  }
  while (temp->get_next() != nullptr) {
    temp = temp->get_next();
  }
  temp->set_next(customer);
}

Customer* QueueList::dequeue() {
  // remove a customer from the head of the queue
  // and return a pointer to it
  if (head == nullptr) {
    return nullptr;
  }
  Customer* temp = head;
  head = head->get_next();
  temp->set_next(nullptr);
  return temp;
}

int QueueList::get_items() {
  // count total number of items each customer in the queue has
  int totalNumOfItems = 0;
  Customer* temp = head;
  while (temp != nullptr) {
    totalNumOfItems += temp->get_numOfItems();
    temp = temp->get_next();
  }
  return totalNumOfItems;
}

void QueueList::print() {
  // print customers in a queue
  Customer* temp = head;
  while (temp != nullptr) {
    temp->print();
    temp = temp->get_next();
  }
}