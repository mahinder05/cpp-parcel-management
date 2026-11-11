
#include "Task2.h"
#include <iostream>
#include <limits>

using namespace std;

// Constructor
Task2::Task2(Task1& system, Task4& activity)
    : parcelSystem(system),
      activitySystem(activity) {

    nextRequestNumber = 1;
    nextSequenceNumber = 1;
}

// Generate unique request ID
string Task2::generateRequestID() {
    string id = "REQ";

    if (nextRequestNumber < 10)
        id += "00";
    else if (nextRequestNumber < 100)
        id += "0";

    id += to_string(nextRequestNumber);
    nextRequestNumber++;

    return id;
}

// Create a new service request
void Task2::createRequest() {
    string parcelID;

    cout << "\n===== CREATE SERVICE REQUEST =====\n";

    cout << "Enter Parcel ID: ";
    getline(cin, parcelID);

    Parcel* parcel = parcelSystem.findParcelByID(parcelID);

    if (parcel == nullptr) {
        cout << "Error: Parcel does not exist.\n";
        return;
    }

    if (parcel->getStatus() != "Received") {
        cout << "Error: This parcel is not available for a new request.\n";
        cout << "Current status: " << parcel->getStatus() << "\n";
        return;
    }

    if (requestQueue.containsParcel(parcelID)) {
        cout << "Error: This parcel already has a pending request.\n";
        return;
    }

    string recipientID;

    cout << "Enter Recipient ID: ";
    getline(cin, recipientID);

    if (recipientID != parcel->getRecipientID()) {
        cout << "Error: Recipient ID does not match parcel records.\n";
        return;
    }

    int serviceChoice;

    cout << "\nSelect Service Type:\n";
    cout << "1. Recipient Collection\n";
    cout << "2. Campus Delivery\n";
    cout << "3. Special Handling\n";
    cout << "Enter choice: ";

    if (!(cin >> serviceChoice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string serviceType;

    switch (serviceChoice) {
        case 1:
            serviceType = "Recipient Collection";
            break;

        case 2:
            serviceType = "Campus Delivery";
            break;

        case 3:
            serviceType = "Special Handling";
            break;

        default:
            cout << "Invalid service type.\n";
            return;
    }

    int priority;

    if (serviceType == "Special Handling") {
        priority = 2;
        cout << "Special handling is automatically assigned high priority.\n";
    }
    else {
        cout << "\nSelect Urgency:\n";
        cout << "1. Normal Priority\n";
        cout << "2. Urgent Priority\n";
        cout << "Enter choice: ";

        if (!(cin >> priority)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (priority != 1 && priority != 2) {
            cout << "Invalid priority selection.\n";
            return;
        }
    }

    string requestID = generateRequestID();

    ServiceRequest newRequest(
        requestID,
        parcelID,
        serviceType,
        recipientID,
        priority,
        nextSequenceNumber
    );

    nextSequenceNumber++;

    // Add request to the priority queue
    requestQueue.enqueue(newRequest);

    // Update parcel status
    string oldStatus = parcel->getStatus();

    parcel->setStatus("Request Pending");

    // Automatically record the activity in Task 4
    activitySystem.logStatusChange(
        parcelID,
        "Service request created: " + requestID,
        oldStatus,
        parcel->getStatus()
    );

    cout << "\nService request created successfully!\n";
    cout << "Request ID: " << requestID << "\n";
    cout << "Parcel ID: " << parcelID << "\n";
    cout << "Service Type: " << serviceType << "\n";
    cout << "Priority: " << (priority == 2 ? "High" : "Normal") << "\n";
}

// Display all pending requests
void Task2::displayRequests() {
    cout << "\n===== PENDING SERVICE REQUESTS =====\n";

    if (requestQueue.isEmpty()) {
        cout << "There are currently no pending requests.\n";
        return;
    }

    requestQueue.displayQueue();
}

// Process the next request according to priority
void Task2::processNextRequest() {
    cout << "\n===== PROCESS NEXT REQUEST =====\n";

    if (requestQueue.isEmpty()) {
        cout << "No service requests are waiting to be processed.\n";
        return;
    }

    ServiceRequest* nextRequest = requestQueue.peek();

    if (nextRequest == nullptr) {
        cout << "Unable to retrieve the next request.\n";
        return;
    }

    cout << "\nNext request to be processed:\n";
    nextRequest->displayRequest();

    string requestID = nextRequest->getRequestID();
    string parcelID = nextRequest->getParcelID();
    string serviceType = nextRequest->getServiceType();

    Parcel* parcel = parcelSystem.findParcelByID(parcelID);

    if (parcel == nullptr) {
        cout << "Error: The parcel linked to this request does not exist.\n";
        return;
    }

    if (parcel->getStatus() != "Request Pending") {
        cout << "Error: Parcel is not in Request Pending status.\n";
        cout << "Request was not processed.\n";
        return;
    }

    string oldStatus = parcel->getStatus();

    // Remove the request from the queue
    ServiceRequest processedRequest = requestQueue.dequeue();
    processedRequest.setStatus("Completed");

    // Update parcel status based on service type
    if (serviceType == "Recipient Collection") {
        parcel->setStatus("Ready for Collection");
    }
    else if (serviceType == "Campus Delivery") {
        parcel->setStatus("Ready for Delivery");
    }
    else if (serviceType == "Special Handling") {
        parcel->setStatus("Special Handling");
    }
    else {
        cout << "Error: Unknown service type.\n";
        return;
    }

    // Automatically record the activity in Task 4
    activitySystem.logStatusChange(
        parcelID,
        "Service request processed: " + requestID,
        oldStatus,
        parcel->getStatus()
    );

    cout << "\nRequest processed successfully!\n";
    cout << "Request ID: " << requestID << "\n";
    cout << "Parcel ID: " << parcelID << "\n";
    cout << "Updated Parcel Status: " << parcel->getStatus() << "\n";
}

// Cancel a pending service request
void Task2::cancelRequest() {
    string requestID;

    cout << "\n===== CANCEL SERVICE REQUEST =====\n";

    if (requestQueue.isEmpty()) {
        cout << "There are no pending requests to cancel.\n";
        return;
    }

    cout << "Enter Request ID to cancel: ";
    getline(cin, requestID);

    if (!requestQueue.containsRequest(requestID)) {
        cout << "Error: Request ID does not exist in the pending queue.\n";
        return;
    }

    string parcelID = requestQueue.getParcelIDByRequest(requestID);

    Parcel* parcel = parcelSystem.findParcelByID(parcelID);

    if (parcel == nullptr) {
        cout << "Error: Linked parcel record could not be found.\n";
        return;
    }

    if (parcel->getStatus() != "Request Pending") {
        cout << "Error: This parcel is not waiting for request processing.\n";
        return;
    }

    string oldStatus = parcel->getStatus();

    if (!requestQueue.cancelRequest(requestID)) {
        cout << "Unable to cancel the request.\n";
        return;
    }

    // Restore parcel status
    parcel->setStatus("Received");

    // Automatically record the activity in Task 4
    activitySystem.logStatusChange(
        parcelID,
        "Service request cancelled: " + requestID,
        oldStatus,
        parcel->getStatus()
    );

    cout << "\nService request cancelled successfully.\n";
    cout << "Request ID: " << requestID << "\n";
    cout << "Parcel ID: " << parcelID << "\n";
    cout << "Parcel status restored to Received.\n";
}

// Task 2 menu
void Task2::displayMenu() {
    int choice;

    do {
        cout << "\n====================================\n";
        cout << "     SERVICE REQUEST MANAGEMENT\n";
        cout << "====================================\n";
        cout << "1. Create Service Request\n";
        cout << "2. Display Pending Requests\n";
        cout << "3. Process Next Request\n";
        cout << "4. Cancel Service Request\n";
        cout << "0. Back to Main Menu\n";
        cout << "====================================\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                createRequest();
                break;

            case 2:
                displayRequests();
                break;

            case 3:
                processNextRequest();
                break;

            case 4:
                cancelRequest();
                break;

            case 0:
                cout << "Returning to main menu...\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);
}

