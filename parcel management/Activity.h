#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <string>
using namespace std;

class Activity {
private:
    int activityID;
    string parcelID;
    string description;
    string previousStatus;
    string newStatus;

public:
    Activity(int id, string pID, string desc,
             string oldStatus, string updatedStatus);

    int getActivityID() const;
    string getParcelID() const;
    string getDescription() const;
    string getPreviousStatus() const;
    string getNewStatus() const;

    void displayActivity() const;
};

#endif