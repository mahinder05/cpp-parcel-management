#ifndef TASK2_H
#define TASK2_H

#include "Task1.h"
#include "PriorityQueue.h"
#include "Task4.h"

class Task2 {
private:
    Task1& parcelSystem;
    PriorityQueue requestQueue;

    int nextRequestNumber;
    int nextSequenceNumber;

    string generateRequestID();
    Task4& activitySystem;

public:
    Task2(Task1& system, Task4& activity);

    void createRequest();
    void displayRequests();
    void processNextRequest();
    void cancelRequest();
    void displayMenu();
};

#endif