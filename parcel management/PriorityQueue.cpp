#include "PriorityQueue.h"
#include <iostream>
using namespace std;

PriorityQueue::PriorityQueue() {
    front = nullptr;
    count = 0;
}

PriorityQueue::~PriorityQueue() {
    while (front != nullptr) {
        Node* temp = front;
        front = front->next;
        delete temp;
    }
}

bool PriorityQueue::isEmpty() const {
    return front == nullptr;
}

int PriorityQueue::getCount() const {
    return count;
}

bool PriorityQueue::containsParcel(string parcelID) const {
    Node* current = front;

    while (current != nullptr) {
        if (current->data.getParcelID() == parcelID)
            return true;

        current = current->next;
    }

    return false;
}

bool PriorityQueue::containsRequest(string requestID) const {
    Node* current = front;

    while (current != nullptr) {
        if (current->data.getRequestID() == requestID)
            return true;

        current = current->next;
    }

    return false;
}

void PriorityQueue::enqueue(ServiceRequest request) {
    Node* newNode = new Node(request);

    // Insert at the front if it has higher priority.
    if (front == nullptr ||
        request.getPriority() > front->data.getPriority()) {

        newNode->next = front;
        front = newNode;
    }
    else {
        Node* current = front;

        // Keep earlier requests ahead when priorities are equal.
        while (current->next != nullptr &&
               current->next->data.getPriority() >= request.getPriority()) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    count++;
}

ServiceRequest* PriorityQueue::peek() {
    if (isEmpty())
        return nullptr;

    return &front->data;
}

ServiceRequest PriorityQueue::dequeue() {
    if (isEmpty()) {
        cout << "No pending requests available.\n";
        return ServiceRequest("", "", "", "", 0, 0);
    }

    Node* temp = front;
    ServiceRequest request = temp->data;

    front = front->next;

    delete temp;
    count--;

    return request;
}

bool PriorityQueue::cancelRequest(string requestID) {
    Node* current = front;
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->data.getRequestID() == requestID) {
            if (previous == nullptr)
                front = current->next;
            else
                previous->next = current->next;

            delete current;
            count--;

            return true;
        }

        previous = current;
        current = current->next;
    }

    return false;
}

void PriorityQueue::displayQueue() const {
    if (isEmpty()) {
        cout << "\nThere are no pending service requests.\n";
        return;
    }

    Node* current = front;

    cout << "\n========== PENDING SERVICE REQUESTS ==========\n";

    while (current != nullptr) {
        current->data.displayRequest();
        current = current->next;
    }

    cout << "\nTotal Pending Requests: " << count << endl;
}
string PriorityQueue::getParcelIDByRequest(string requestID) const {
    Node* current = front;

    while (current != nullptr) {
        if (current->data.getRequestID() == requestID)
            return current->data.getParcelID();

        current = current->next;
    }

    return "";
}