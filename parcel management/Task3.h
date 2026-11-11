#ifndef TASK3_H
#define TASK3_H

#include "Task1.h"
#include "Task4.h"
#include "CircularResourceList.h"

class Task3 {
private:
    Task1& parcelSystem;
    Task4& activitySystem;
    CircularResourceList resources;
    int nextResourceNumber;

    string generateResourceID();

public:
    Task3(Task1& system, Task4& activity);

    void registerResource();
    void displayResources();
    void assignResourceToParcel();
    void completeAssignment();
    void markResourceUnavailable();
    void markResourceAvailable();

    void displayMenu();
};

#endif