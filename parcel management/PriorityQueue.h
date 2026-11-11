#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "ServiceRequest.h"

class PriorityQueue {
private:
    struct Node {
        ServiceRequest data;
        Node* next;

        Node(ServiceRequest request)
            : data(request), next(nullptr) {}
    };

    Node* front;
    int count;

public:
    PriorityQueue();
    ~PriorityQueue();

    bool isEmpty() const;
    int getCount() const;

    bool containsParcel(string parcelID) const;
    bool containsRequest(string requestID) const;
    string getParcelIDByRequest(string requestID) const;

    void enqueue(ServiceRequest request);
    ServiceRequest* peek();
    ServiceRequest dequeue();

    bool cancelRequest(string requestID);
    void displayQueue() const;
};

#endif