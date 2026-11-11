
#include "Task3.h"
#include <iostream>
#include <limits>
using namespace std;

// Constructor
Task3::Task3(Task1& system, Task4& activity)
    : parcelSystem(system),
      activitySystem(activity) {
    nextResourceNumber = 1;
}

// Generate unique Resource ID
string Task3::generateResourceID() {
    string id = "RES";

    if (nextResourceNumber < 10)
        id += "00";
    else if (nextResourceNumber < 100)
        id += "0";

    id += to_string(nextResourceNumber);
    nextResourceNumber++;

    return id;
}

// Register a new resource
void Task3::registerResource() {
    int choice;
    string resourceType;

    cout << "\n========== REGISTER RESOURCE ==========\n";
    cout << "1. Collection Counter\n";
    cout << "2. Delivery Personnel\n";
    cout << "3. Special Handling Resource\n";
    cout << "Choose resource type: ";

    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (choice) {
        case 1:
            resourceType = "Counter";
            break;

        case 2:
            resourceType = "Delivery";
            break;

        case 3:
            resourceType = "Special Handling";
            break;

        default:
            cout << "Invalid resource type.\n";
            return;
    }

    string id = generateResourceID();

    Resource newResource(id, resourceType);

    if (resources.addResource(newResource)) {
        cout << "\nResource registered successfully!\n";
        cout << "Resource ID: " << id << endl;
        cout << "Resource Type: " << resourceType << endl;
    }
    else {
        cout << "Unable to register resource.\n";
    }
}

// Display all resources
void Task3::displayResources() {
    resources.displayResources();
}

// Assign an available resource to a parcel
void Task3::assignResourceToParcel() {
    string parcelID;

    cout << "\n========== ASSIGN RESOURCE ==========\n";
    cout << "Enter Parcel ID: ";
    getline(cin, parcelID);

    Parcel* parcel = parcelSystem.findParcelByID(parcelID);

    if (parcel == nullptr) {
        cout << "Parcel not found.\n";
        return;
    }

    string currentStatus = parcel->getStatus();
    string requiredType;

    // Determine the required resource type
    if (currentStatus == "Ready for Collection") {
        requiredType = "Counter";
    }
    else if (currentStatus == "Ready for Delivery") {
        requiredType = "Delivery";
    }
    else if (currentStatus == "Special Handling") {
        requiredType = "Special Handling";
    }
    else {
        cout << "This parcel is not ready for resource assignment.\n";
        cout << "Current Status: " << currentStatus << endl;
        return;
    }

    // Find a suitable available resource
    string resourceID = resources.assignResource(
        parcelID,
        requiredType
    );

    if (resourceID == "") {
        cout << "No suitable available resource found.\n";
        cout << "Required Resource Type: " << requiredType << endl;
        return;
    }

    // Update parcel status
    string oldStatus = parcel->getStatus();

    if (requiredType == "Counter") {
        parcel->setStatus("Assigned to Counter");
    }
    else if (requiredType == "Delivery") {
        parcel->setStatus("Assigned for Delivery");
    }
    else if (requiredType == "Special Handling") {
        parcel->setStatus("Assigned for Special Handling");
    }

    // Automatically record activity in Task 4
    activitySystem.logStatusChange(
        parcelID,
        "Resource assigned: " + resourceID,
        oldStatus,
        parcel->getStatus()
    );

    cout << "\nResource assigned successfully!\n";
    cout << "Resource ID: " << resourceID << endl;
    cout << "Parcel ID: " << parcelID << endl;
    cout << "New Parcel Status: " << parcel->getStatus() << endl;
}

// Complete an assignment and release the resource
void Task3::completeAssignment() {
    string resourceID;

    cout << "\n========== COMPLETE ASSIGNMENT ==========\n";
    cout << "Enter Resource ID: ";
    getline(cin, resourceID);

    string parcelID = resources.getAssignedParcel(resourceID);

    if (parcelID == "") {
        cout << "Resource not found or is not currently occupied.\n";
        return;
    }

    Parcel* parcel = parcelSystem.findParcelByID(parcelID);

    if (parcel == nullptr) {
        cout << "Assigned parcel does not exist.\n";
        return;
    }

    string resourceType = resources.getResourceType(resourceID);
    string oldStatus = parcel->getStatus();

    // Determine the parcel's new status
    if (resourceType == "Counter") {
        parcel->setStatus("Collected");
    }
    else if (resourceType == "Delivery") {
        parcel->setStatus("Delivered");
    }
    else if (resourceType == "Special Handling") {
        parcel->setStatus("Ready for Collection");
    }
    else {
        cout << "Invalid resource type.\n";
        return;
    }

    // Release resource after successful completion
    if (!resources.releaseResource(resourceID)) {
        cout << "Unable to release resource.\n";
        parcel->setStatus(oldStatus);
        return;
    }

    // Automatically record activity in Task 4
    activitySystem.logStatusChange(
        parcelID,
        "Resource assignment completed: " + resourceID,
        oldStatus,
        parcel->getStatus()
    );

    cout << "\nAssignment completed successfully!\n";
    cout << "Parcel ID: " << parcelID << endl;
    cout << "Resource ID: " << resourceID << endl;
    cout << "New Parcel Status: " << parcel->getStatus() << endl;
    cout << "Resource has been released.\n";
}

// Mark an available resource as unavailable
void Task3::markResourceUnavailable() {
    string resourceID;

    cout << "\nEnter Resource ID to mark unavailable: ";
    getline(cin, resourceID);

    if (resources.setUnavailable(resourceID)) {
        cout << "Resource marked as unavailable.\n";
    }
    else {
        cout << "Unable to update resource.\n";
        cout << "Check whether the ID exists and the resource is available.\n";
    }
}

// Make an unavailable resource available again
void Task3::markResourceAvailable() {
    string resourceID;

    cout << "\nEnter Resource ID to make available: ";
    getline(cin, resourceID);

    if (resources.setAvailable(resourceID)) {
        cout << "Resource is now available.\n";
    }
    else {
        cout << "Unable to update resource.\n";
        cout << "Check whether the ID exists and the resource is unavailable.\n";
    }
}

// Task 3 menu
void Task3::displayMenu() {
    int choice;

    do {
        cout << "\n====================================\n";
        cout << " TASK 3 - RESOURCE MANAGEMENT\n";
        cout << "====================================\n";
        cout << "1. Register Resource\n";
        cout << "2. Display All Resources\n";
        cout << "3. Assign Resource to Parcel\n";
        cout << "4. Complete Assignment\n";
        cout << "5. Mark Resource Unavailable\n";
        cout << "6. Mark Resource Available\n";
        cout << "0. Return to Main Menu\n";
        cout << "\nEnter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                registerResource();
                break;

            case 2:
                displayResources();
                break;

            case 3:
                assignResourceToParcel();
                break;

            case 4:
                completeAssignment();
                break;

            case 5:
                markResourceUnavailable();
                break;

            case 6:
                markResourceAvailable();
                break;

            case 0:
                cout << "Returning to main menu...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);
}
