
#include "ParcelQueue.h"
#include <iostream>

using namespace std;

ParcelQueue::ParcelQueue() {
    front = nullptr;
    rear = nullptr;
    count = 0;
}

ParcelQueue::~ParcelQueue() {
    while (!isEmpty()) {
        dequeue();
    }
}

bool ParcelQueue::isEmpty() const {
    return front == nullptr;
}

int ParcelQueue::getCount() const {
    return count;
}

void ParcelQueue::enqueue(string parcelID) {

    QueueNode* newNode = new QueueNode(parcelID);

    if (isEmpty()) {
        front = rear = newNode;
    }
    else {
        rear->next = newNode;
        rear = newNode;
    }

    count++;

    cout << "Parcel " << parcelID
         << " added to processing queue.\n";
}

string ParcelQueue::dequeue() {

    if (isEmpty()) {
        cout << "Queue is empty.\n";
        return "";
    }

    QueueNode* temp = front;
    string removedID = temp->parcelID;

    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp;
    count--;

    return removedID;
}

string ParcelQueue::peek() const {

    if (isEmpty()) {
        return "";
    }

    return front->parcelID;
}

void ParcelQueue::displayQueue() const {

    if (isEmpty()) {
        cout << "Processing queue is empty.\n";
        return;
    }

    QueueNode* current = front;

    cout << "\n========== PROCESSING QUEUE ==========\n";

    while (current != nullptr) {
        cout << current->parcelID << endl;
        current = current->next;
    }

    cout << "Total waiting: " << count << endl;
}
