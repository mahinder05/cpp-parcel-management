
#include "Task1.h"
#include <iostream>
#include <limits>
#include <cctype>

using namespace std;

// Constructor
Task1::Task1() {
    nextParcelNumber = 1;
}

// Check whether input is empty or contains only spaces
bool Task1::isValidInput(string input) {

    return input.find_first_not_of(" \t") != string::npos;
}

// Generate unique Parcel ID
string Task1::generateParcelID() {

    string id = "P";

    if (nextParcelNumber < 10)
        id += "000";
    else if (nextParcelNumber < 100)
        id += "00";
    else if (nextParcelNumber < 1000)
        id += "0";

    id += to_string(nextParcelNumber);

    nextParcelNumber++;

    return id;
}

// Register a new parcel
void Task1::registerParcel() {

    string name, recipient, phone;
    string company, type, date, time;

    cout << "\n========== REGISTER NEW PARCEL ==========\n";

    cout << "Recipient Name: ";
    getline(cin, name);

    cout << "Recipient ID: ";
    getline(cin, recipient);

    cout << "Recipient Phone: ";
    getline(cin, phone);

    cout << "Delivery Company: ";
    getline(cin, company);

    cout << "Parcel Type (Normal/Fragile/Oversized): ";
    getline(cin, type);

    cout << "Arrival Date: ";
    getline(cin, date);

    cout << "Arrival Time: ";
    getline(cin, time);

    // Validate required information
    if (!isValidInput(name) ||
        !isValidInput(recipient) ||
        !isValidInput(phone) ||
        !isValidInput(company) ||
        !isValidInput(type) ||
        !isValidInput(date) ||
        !isValidInput(time)) {

        cout << "\nRegistration failed: Missing information.\n";
        return;
    }

    // Validate phone number
    if (phone.length() < 8 || phone.length() > 15) {
        cout << "\nRegistration failed: Invalid phone number.\n";
        return;
    }

    for (char digit : phone) {
        if (!isdigit(static_cast<unsigned char>(digit))) {
            cout << "\nRegistration failed: Phone number must contain digits only.\n";
            return;
        }
    }

    // Generate Parcel ID
    string id = generateParcelID();

    // Create parcel object
    Parcel newParcel(
        id, name, recipient, phone,
        company, type, date, time
    );

    // Store parcel in linked list
    parcelList.insertParcel(newParcel);

    // Add parcel ID to incoming queue
    incomingQueue.enqueue(id);

    cout << "\nParcel registered successfully!\n";
    cout << "Generated Parcel ID: " << id << endl;
}

// Display all parcel records
void Task1::displayAllParcels() {

    parcelList.displayAllParcels();
}

// Search for a parcel
void Task1::searchParcel() {

    string id;

    cout << "\nEnter Parcel ID: ";
    getline(cin, id);

    Parcel* found = parcelList.searchParcel(id);

    if (found != nullptr) {
        cout << "\nParcel found!\n";
        found->displayParcel();
    }
    else {
        cout << "\nParcel ID not found.\n";
    }
}

// Update parcel information
void Task1::updateParcel() {

    string id;

    cout << "\nEnter Parcel ID to update: ";
    getline(cin, id);

    Parcel* found = parcelList.searchParcel(id);

    if (found == nullptr) {
        cout << "Parcel not found.\n";
        return;
    }

    if (found->getStatus() == "Collected" ||
        found->getStatus() == "Delivered" ||
        found->getStatus() == "Returned" ||
        found->getStatus() == "Cancelled") {

        cout << "Completed parcel records cannot be updated.\n";
        return;
    }

    int choice;

    cout << "\nWhat would you like to update?\n";
    cout << "1. Recipient Name\n";
    cout << "2. Recipient ID\n";
    cout << "3. Phone Number\n";
    cout << "4. Delivery Company\n";
    cout << "5. Parcel Type\n";
    cout << "Choice: ";

    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string newValue;

    cout << "Enter new information: ";
    getline(cin, newValue);

    if (!isValidInput(newValue)) {
        cout << "Update failed: Information cannot be empty.\n";
        return;
    }

    switch (choice) {

        case 1:
            found->setRecipientName(newValue);
            break;

        case 2:
            found->setRecipientID(newValue);
            break;

        case 3:
            if (newValue.length() < 8 ||
                newValue.length() > 15) {
                cout << "Invalid phone number.\n";
                return;
            }

            for (char digit : newValue) {
                if (!isdigit(static_cast<unsigned char>(digit))) {
                    cout << "Phone number must contain digits only.\n";
                    return;
                }
            }

            found->setRecipientPhone(newValue);
            break;

        case 4:
            found->setDeliveryCompany(newValue);
            break;

        case 5:
            found->setParcelType(newValue);
            break;

        default:
            cout << "Invalid selection.\n";
            return;
    }

    cout << "Parcel information updated successfully.\n";
}

// Remove a parcel record
void Task1::removeParcel() {

    string id;

    cout << "\nEnter Parcel ID to remove: ";
    getline(cin, id);

    Parcel* found = parcelList.searchParcel(id);

    if (found == nullptr) {
        cout << "Parcel not found.\n";
        return;
    }

    string status = found->getStatus();

    if (status != "Collected" &&
        status != "Delivered" &&
        status != "Returned" &&
        status != "Cancelled") {

        cout << "Cannot remove an active or pending parcel.\n";
        cout << "Complete or cancel its processing first.\n";
        return;
    }

    parcelList.deleteParcel(id);
}

// Display incoming queue
void Task1::displayIncomingQueue() {

    incomingQueue.displayQueue();
}

// Display Task 1 menu
void Task1::displayMenu() {

    int choice;

    do {

        cout << "\n====================================\n";
        cout << " SMART CAMPUS PARCEL MANAGEMENT\n";
        cout << " TASK 1 - PARCEL INTAKE MODULE\n";
        cout << "====================================\n";

        cout << "1. Register New Parcel\n";
        cout << "2. Display All Parcels\n";
        cout << "3. Search Parcel\n";
        cout << "4. Update Parcel Information\n";
        cout << "5. Remove Parcel Record\n";
        cout << "6. Display Incoming Queue\n";
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
                registerParcel();
                break;

            case 2:
                displayAllParcels();
                break;

            case 3:
                searchParcel();
                break;

            case 4:
                updateParcel();
                break;

            case 5:
                removeParcel();
                break;

            case 6:
                displayIncomingQueue();
                break;

            case 0:
                cout << "Returning to main menu...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);


}
Parcel* Task1::findParcelByID(string id) {
    return parcelList.searchParcel(id);
}

bool Task1::deleteParcelRecord(string id) {
    Parcel* found = parcelList.searchParcel(id);

    if (found == nullptr) {
        cout << "Parcel does not exist in the main records.\n";
        return false;
    }

    string status = found->getStatus();

    if (status != "Collected" &&
        status != "Delivered" &&
        status != "Returned" &&
        status != "Cancelled") {

        cout << "Cannot delete an active parcel.\n";
        cout << "Complete or cancel the parcel first.\n";
        return false;
    }

    return parcelList.deleteParcel(id);
}

