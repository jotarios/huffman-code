#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include <iostream>
#include "Node.cpp"

class PriorityQueue {
 private:
  Node *head;
  int size = 0;

 public:
  PriorityQueue() {
    this->head = nullptr;
  }

  void push(char character, int priority, Node *left, Node *right) {
    size++;

    if (!this->head) {
      this->head = new Node{character, priority, left, right, nullptr};
      return;
    }

    Node *newItem = new Node{character, priority, left, right, nullptr};

    if (this->head->priority >= priority) {
      newItem->next = head;
      head = newItem;
      return;
    }

    auto start = this->head;

    while (start->next != nullptr && start->next->priority < priority) {
      start = start->next;
    }

    newItem->next = start->next;
    start->next = newItem;
  }

  int getSize() {
    return this->size;
  }

  Node *pop() {
    Node *temp = this->head;
    this->head = this->head->next;

    size--;

    return temp;
  }

  bool isEmpty() {
    return head == nullptr;
  }

  void describe() {
    int total = 0;
    int totalChars = 0;
    while (!this->isEmpty()) {
      Node *item = this->pop();
      std::cout << item->item << " - " << item->priority << std::endl;
      total++;
      totalChars += item->priority;
    }

    std::cout << "Total: " << total << " - caracteres: " << totalChars << std::endl;
  }
};

#endif
