#include "Activity.h"
#include <iostream>
using namespace std;

Activity::Activity(int id, string pID, string desc,
                   string oldStatus, string updatedStatus) {
    activityID = id;
    parcelID = pID;
    description = desc;
    previousStatus = oldStatus;
    newStatus = updatedStatus;
}

int Activity::getActivityID() const {
    return activityID;
}

string Activity::getParcelID() const {
    return parcelID;
}

string Activity::getDescription() const {
    return description;
}

string Activity::getPreviousStatus() const {
    return previousStatus;
}

string Activity::getNewStatus() const {
    return newStatus;
}

void Activity::displayActivity() const {
    cout << "\nActivity ID: " << activityID << endl;
    cout << "Parcel ID: " << parcelID << endl;
    cout << "Activity: " << description << endl;
    cout << "Previous Status: " << previousStatus << endl;
    cout << "New Status: " << newStatus << endl;
}