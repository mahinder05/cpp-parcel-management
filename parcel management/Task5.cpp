
#include "Task5.h"
#include <iostream>
#include <limits>
#include <cctype>
using namespace std;

Task5::Task5(Task1& system)
    : parcelSystem(system) {
}

void Task5::insertParcel() {
    string id;

    cout << "\nEnter Parcel ID to insert into BST: ";
    getline(cin, id);

    // Check whether the parcel exists in Task 1
    Parcel* found = parcelSystem.findParcelByID(id);

    if (found == nullptr) {
        cout << "Parcel does not exist in the main records.\n";
        return;
    }

    if (parcelTree.search(id)) {
        cout << "This parcel is already in the BST.\n";
        return;
    }

    if (parcelTree.insert(id)) {
        cout << "Parcel successfully inserted into BST.\n";
    }
}

void Task5::searchParcel() {
    string id;

    cout << "\nEnter Parcel ID to search: ";
    getline(cin, id);

    if (!parcelTree.search(id)) {
        cout << "Parcel not found in the BST.\n";
        return;
    }

    Parcel* found = parcelSystem.findParcelByID(id);

    if (found != nullptr) {
        cout << "\nParcel found!\n";
        found->displayParcel();
    }
    else {
        cout << "Parcel is missing from the main records.\n";
    }
}

void Task5::displayParcels() {
    parcelTree.displayAll(parcelSystem);
}

void Task5::updateParcel() {
    string id;

    cout << "\nEnter Parcel ID to update: ";
    getline(cin, id);

    if (!parcelTree.search(id)) {
        cout << "Parcel not found in the BST.\n";
        return;
    }

    Parcel* found = parcelSystem.findParcelByID(id);

    if (found == nullptr) {
        cout << "Parcel does not exist in the main records.\n";
        return;
    }

    string status = found->getStatus();

    if (status == "Collected" || status == "Delivered" ||
        status == "Returned" || status == "Cancelled") {
        cout << "Completed parcel information cannot be updated.\n";
        return;
    }

    int choice;

    cout << "\n========== UPDATE PARCEL ==========\n";
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

    if (newValue.find_first_not_of(" \t") == string::npos) {
        cout << "Information cannot be empty.\n";
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
            if (newValue.length() < 8 || newValue.length() > 15) {
                cout << "Invalid phone number length.\n";
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

void Task5::deleteParcel() {
    string id;

    cout << "\nEnter Parcel ID to delete: ";
    getline(cin, id);

    if (!parcelTree.search(id)) {
        cout << "Parcel not found in the BST.\n";
        return;
    }

    cout << "\nAre you sure you want to delete this parcel?\n";
    cout << "This will remove it from both the BST and main records.\n";
    cout << "1. Yes\n";
    cout << "0. No\n";
    cout << "Choice: ";

    int confirm;

    if (!(cin >> confirm)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (confirm != 1) {
        cout << "Deletion cancelled.\n";
        return;
    }

    // Delete from main records first
    if (parcelSystem.deleteParcelRecord(id)) {
        parcelTree.remove(id);
        cout << "Parcel successfully deleted from the BST.\n";
    }
}

void Task5::displayMenu() {
    int choice;

    do {
        cout << "\n====================================\n";
        cout << " TASK 5 - PARCEL CATEGORY ORGANIZATION\n";
        cout << "====================================\n";
        cout << "1. Insert Parcel into BST\n";
        cout << "2. Search Parcel\n";
        cout << "3. Display All BST Parcels\n";
        cout << "4. Update Parcel Information\n";
        cout << "5. Delete Parcel\n";
        cout << "0. Return to Main Menu\n";
        cout << "\nEnter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: insertParcel(); break;
            case 2: searchParcel(); break;
            case 3: displayParcels(); break;
            case 4: updateParcel(); break;
            case 5: deleteParcel(); break;
            case 0: cout << "Returning to main menu...\n"; break;
            default: cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}
