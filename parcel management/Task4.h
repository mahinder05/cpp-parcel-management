#ifndef TASK4_H
#define TASK4_H

#include "Task1.h"
#include "ActivityStack.h"

class Task4 {
private:
    Task1& parcelSystem;
    ActivityStack activityStack;
    int nextActivityID;

    bool isValidStatus(string status);

public:
    Task4(Task1& system);

    void recordActivity();
    void displayRecentActivities();
    void displayParcelHistory();
    void undoLastActivity();
    void logStatusChange(string parcelID,
                     string description,
                     string previousStatus,
                     string newStatus);

    void displayMenu();
};

#endif