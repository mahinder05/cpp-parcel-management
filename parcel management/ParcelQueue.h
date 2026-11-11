
#ifndef PARCELQUEUE_H
#define PARCELQUEUE_H

#include <string>
using namespace std;

class ParcelQueue {

private:
    struct QueueNode {
        string parcelID;
        QueueNode* next;

        QueueNode(string id) {
            parcelID = id;
            next = nullptr;
        }
    };

    QueueNode* front;
    QueueNode* rear;
    int count;

public:
    ParcelQueue();
    ~ParcelQueue();

    bool isEmpty() const;
    int getCount() const;

    void enqueue(string parcelID);
    string dequeue();
    string peek() const;

    void displayQueue() const;
};

#endif
