#include "Task4.h"
#include <iostream>
#include <limits>
using namespace std;

Task4::Task4(Task1& system)
    : parcelSystem(system) {
    nextActivityID = 1;
}

bool Task4::isValidStatus(string status) {
    return status == "Received" ||
           status == "Request Pending" ||
           status == "Ready for Collection" ||
           status == "Ready for Delivery" ||
           status == "Special Handling" ||
           status == "Assigned to Counter" ||
           status == "Assigned for Delivery" ||
           status == "Assigned for Special Handling" ||
           status == "Collected" ||
           status == "Delivered" ||
           status == "Returned" ||
           status == "Cancelled" ||
           status == "Missing" ||
           status == "On Hold";
}

void Task4::recordActivity() {
    string parcelID;
    cout << "\n========== RECORD PARCEL ACTIVITY ==========\n";
    cout << "Enter Parcel ID: ";
    getline(cin, parcelID);

    if (parcelID.empty()) {
        cout << "Parcel ID cannot be empty.\n";
        return;
    }

    Parcel* parcel = parcelSystem.findParcelByID(parcelID);

    if (parcel == nullptr) {
        cout << "Parcel not found.\n";
        return;
    }

    string previousStatus = parcel->getStatus();

    cout << "\nCurrent Parcel Status: " << previousStatus << endl;

    cout << "\nSelect New Status:\n";
    cout << "1. Ready for Collection\n";
    cout << "2. Ready for Delivery\n";
    cout << "3. Collected\n";
    cout << "4. Delivered\n";
    cout << "5. Returned\n";
    cout << "6. Cancelled\n";
    cout << "7. Missing\n";
    cout << "8. On Hold\n";
    cout << "Choice: ";

    int choice;

    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string newStatus;

    switch (choice) {
        case 1: newStatus = "Ready for Collection"; break;
        case 2: newStatus = "Ready for Delivery"; break;
        case 3: newStatus = "Collected"; break;
        case 4: newStatus = "Delivered"; break;
        case 5: newStatus = "Returned"; break;
        case 6: newStatus = "Cancelled"; break;
        case 7: newStatus = "Missing"; break;
        case 8: newStatus = "On Hold"; break;
        default:
            cout << "Invalid status selection.\n";
            return;
    }

    if (previousStatus == newStatus) {
        cout << "Parcel already has this status.\n";
        return;
    }

    if (previousStatus == "Collected" ||
        previousStatus == "Delivered" ||
        previousStatus == "Returned" ||
        previousStatus == "Cancelled") {
        cout << "Completed parcels cannot have their status changed here.\n";
        return;
    }

    string description = "Parcel status changed from " +
                         previousStatus + " to " + newStatus;

    Activity activity(
        nextActivityID,
        parcelID,
        description,
        previousStatus,
        newStatus
    );

    // Record the activity before updating the parcel.
    activityStack.push(activity);

    parcel->setStatus(newStatus);

    cout << "\nActivity recorded successfully!\n";
    cout << "Activity ID: " << nextActivityID << endl;
    cout << "Previous Status: " << previousStatus << endl;
    cout << "New Status: " << newStatus << endl;

    nextActivityID++;
}

void Task4::displayRecentActivities() {
    activityStack.displayRecentActivities();
}

void Task4::displayParcelHistory() {
    string parcelID;

    cout << "\nEnter Parcel ID: ";
    getline(cin, parcelID);

    if (parcelID.empty()) {
        cout << "Parcel ID cannot be empty.\n";
        return;
    }

    if (parcelSystem.findParcelByID(parcelID) == nullptr) {
        cout << "Parcel not found.\n";
        return;
    }

    activityStack.displayParcelHistory(parcelID);
}

void Task4::undoLastActivity() {
    if (activityStack.isEmpty()) {
        cout << "\nThere are no activities to undo.\n";
        return;
    }

    Activity* latestActivity = activityStack.peek();

    if (latestActivity == nullptr)
        return;

    cout << "\n========== LATEST ACTIVITY ==========\n";
    latestActivity->displayActivity();

    cout << "\nUndo this activity? (1 = Yes, 0 = No): ";

    int choice;

    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice != 1) {
        cout << "Undo cancelled.\n";
        return;
    }

    string parcelID = latestActivity->getParcelID();

    Parcel* parcel = parcelSystem.findParcelByID(parcelID);

    if (parcel == nullptr) {
        cout << "Parcel no longer exists. Cannot undo activity.\n";
        return;
    }

    if (parcel->getStatus() != latestActivity->getNewStatus()) {
        cout << "Cannot undo: Parcel status has changed since this activity.\n";
        return;
    }

    if (parcel->getStatus() == "Collected" ||
        parcel->getStatus() == "Delivered" ||
        parcel->getStatus() == "Returned" ||
        parcel->getStatus() == "Cancelled") {
        cout << "Completed parcel activity cannot be undone here.\n";
        return;
    }

    Activity undoneActivity = activityStack.pop();

    parcel->setStatus(undoneActivity.getPreviousStatus());

    cout << "\nActivity successfully undone!\n";
    cout << "Parcel ID: " << parcelID << endl;
    cout << "Restored Status: " << parcel->getStatus() << endl;
}

void Task4::displayMenu() {
    int choice;

    do {
        cout << "\n====================================\n";
        cout << " TASK 4 - ACTIVITY MANAGEMENT\n";
        cout << "====================================\n";
        cout << "1. Record Parcel Activity\n";
        cout << "2. Display Recent Activities\n";
        cout << "3. View Parcel Activity History\n";
        cout << "4. Undo Latest Activity\n";
        cout << "0. Return to Main Menu\n";
        cout << "\nEnter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a number.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: recordActivity(); break;
            case 2: displayRecentActivities(); break;
            case 3: displayParcelHistory(); break;
            case 4: undoLastActivity(); break;
            case 0: cout << "Returning to main menu...\n"; break;
            default: cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}
void Task4::logStatusChange(
    string parcelID,
    string description,
    string previousStatus,
    string newStatus
) {
    Activity newActivity(
        nextActivityID,
        parcelID,
        description,
        previousStatus,
        newStatus
    );

    activityStack.push(newActivity);
    nextActivityID++;

    cout << "Activity automatically recorded.\n";
}