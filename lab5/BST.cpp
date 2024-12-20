//
//  BST.cpp
//  Lab 5 Search Through A Database
//
//  Created by Kylie Ng, November 2024
#include "BST.h"

#include "Employee.h"

BST::BST(string order_) {
  root = NULL;
  order = order_;
}

BST::~BST() { delete root; }

// ADDED: Function headers for my helper functions that are not a member of the
// BST class (wouldn't mofify BST.h, and helper functions would not have BST::
// in front of it)
void insertH_name(Employee*, Employee*);
void insertH_ID(Employee*, Employee*);
void insertH_age(Employee*, Employee*);
void printInOrderH(Employee*);
Employee* searchID_H(int, Employee*);
void searchAgeRangeH(double, double, Employee*);
void autoCompleteH(string, Employee*);

// newEmployee is a pointer to a dynamically allocated Employee. Insert it
// ACCORDING to the value of "order" of the binary search tree.
void BST::insert(Employee* newEmployee_) {
  if (root == nullptr) {
    root = newEmployee_;
  } else {
    if (order == "name") {
      insertH_name(newEmployee_, root);
    } else if (order == "ID") {
      insertH_ID(newEmployee_, root);
    } else {  // if (order == "age")
      insertH_age(newEmployee_, root);
    }
  }
}
// all three have the exact same logic
void insertH_name(Employee* e, Employee* temp) {
  // "You can safely assume no two employees will have the same name"
  if (e->getName() < temp->getName()) {
    if (temp->getLeft() == NULL) {
      temp->setLeft(e);
    } else {
      insertH_name(e, temp->getLeft());
    }
  } else {  // (e->getName() > temp->getName())
    if (temp->getRight() == NULL) {
      temp->setRight(e);
    } else {
      insertH_name(e, temp->getRight());
    }
  }
}
// no two employees will have the same ID obviously
void insertH_ID(Employee* e, Employee* temp) {
  if (e->getID() < temp->getID()) {
    if (temp->getLeft() == NULL) {
      temp->setLeft(e);
    } else {
      insertH_ID(e, temp->getLeft());
    }
  } else {  // if (e->getID() > temp->getID())
    if (temp->getRight() == NULL) {
      temp->setRight(e);
    } else {
      insertH_ID(e, temp->getRight());
    }
  }
}
void insertH_age(Employee* e, Employee* temp) {
  // "if two employees have the same age, the new employee’s age should be
  // considered lower than the existing employee in the database"
  /*if (e->getAge() > temp->getAge()) { // changed to greater than
    if (temp->getLeft() == NULL) {
      temp->setLeft(e);
    } else {
      insertH_age(e, temp->getLeft());
    }
  } else {
    if (e->getAge() == temp->getAge()) {
      if (temp->getLeft() == NULL) {
        temp->setLeft(e);
      } else {
        insertH_age(e, temp->getLeft());
      }
    } else {
      if (temp->getRight() == NULL) {
        temp->setRight(e);
      } else {
        insertH_age(e, temp->getRight());
      }
    }
  }*/
  if (e->getAge() <= temp->getAge()) {  // changed to greater than
    if (temp->getLeft() == NULL) {
      temp->setLeft(e);
    } else {
      insertH_age(e, temp->getLeft());
    }
  } else {
    if (temp->getRight() == NULL) {
      temp->setRight(e);
    } else {
      insertH_age(e, temp->getRight());
    }
  }
}
// print the Employees in the tree according its order
// Doesn't print anything if nothing is found
void BST::printInOrder() { printInOrderH(root); }

void printInOrderH(Employee* e) {
  if (e != nullptr) {
    printInOrderH(e->getLeft());
    e->print();
    printInOrderH(e->getRight());
  }
}

// search for an employee with a particular ID
// Prints "<ID> ID does not exist" if ID doesn't exist
Employee* BST::searchID(int ID) {
  Employee* temp =
      searchID_H(ID, root);  // pass in the root and let recusion do its magic
  if (temp != nullptr) {
    return temp;
  } else {
    return nullptr;
  }
}
Employee* searchID_H(int ID, Employee* e) {
  if (e == nullptr) {
    return nullptr;  // means either list empty aka dne, or traversed the
                     // entire BST and dne
  }
  if (e->getID() == ID) {
    return e;  // found
  } else if (e->getID() > ID) {
    return searchID_H(ID, e->getLeft());
  } else {
    return searchID_H(ID, e->getRight());
  }
}

// search for employees within the age range
// Doesn't print anything if nothing is found
void BST::searchAgeRange(double lowAge, double highAge) {
  searchAgeRangeH(lowAge, highAge,
                  root);  // pass in the root and let recusion do its magic
  return;                 // doesn't print anything if nothing is found
}
void searchAgeRangeH(double lowAge, double highAge, Employee* e) {
  if (e == nullptr) {
    return;  // means either list empty aka dne, or traversed the entire BST
             // and not found
  }
  if (e->getAge() >= lowAge &&
      e->getAge() <= highAge) {  // within the age range and print
    searchAgeRangeH(lowAge, highAge,
                    e->getLeft());  // prints youngest age first
    e->print();                     // prints middle age in between
    searchAgeRangeH(lowAge, highAge,
                    e->getRight());  // prints oldest age last
  } else if (e->getAge() > highAge) {
    searchAgeRangeH(lowAge, highAge, e->getLeft());
  } else {  // if (e->getAge() < lowAge)
    searchAgeRangeH(lowAge, highAge, e->getRight());
  }
}

// Search for employees with names having the same prefix in the firstName +
// secondName If available, it prints them in order of their names in
// alphabetical order
// Doesn't print anything if nothing is found
void BST::autocomplete(string prefix) {
  autoCompleteH(prefix, root);
  return;  // doesn't print anything if nothing is found
}
void autoCompleteH(string prefix, Employee* e) {
  if (e == nullptr) {
    return;  // means either list empty aka dne, or traversed the entire BST
             // and not found
  }
  autoCompleteH(prefix, e->getLeft());
  // split full name into first name and last name
  int splitByCapital = e->getName().find_first_of(
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
      1);  // searches for capital letters, by skipping the first capital
           // character in firstname
  if (splitByCapital != std::string::npos) {
    string firstName = e->getName().substr(0, splitByCapital);
    string lastName = e->getName().substr(splitByCapital);

    if (firstName.find(prefix) !=
        std::string::npos) {  // if the prefix matches "any part of the first
                              // name without the last name"
      e->print();
    } else if ((firstName + " " + lastName).find(prefix) ==
               0) {  // if the prefix matches "the first name followed by a
                     // space and part of
                     // the last name of an employee"
      e->print();
    }
  }
  autoCompleteH(prefix, e->getRight());
}
