
#include "ParcelLinkedList.h"
#include <iostream>

using namespace std;

// Constructor
ParcelLinkedList::ParcelLinkedList() {
    head = nullptr;
    tail = nullptr;
    count = 0;
}

// Destructor - free dynamically allocated memory
ParcelLinkedList::~ParcelLinkedList() {

    Node* current = head;

    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }

    head = nullptr;
    tail = nullptr;
    count = 0;
}

// Check whether list is empty
bool ParcelLinkedList::isEmpty() const {
    return head == nullptr;
}

// Return number of parcels
int ParcelLinkedList::getCount() const {
    return count;
}

// Insert parcel at the end of the list
void ParcelLinkedList::insertParcel(Parcel parcel) {

    Node* newNode = new Node(parcel);

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }

    count++;

    cout << "Parcel successfully added to records.\n";
}

// Search for a parcel using Parcel ID
Parcel* ParcelLinkedList::searchParcel(string parcelID) {

    Node* current = head;

    while (current != nullptr) {

        if (current->data.getParcelID() == parcelID) {
            return &(current->data);
        }

        current = current->next;
    }

    return nullptr;
}

// Display all registered parcels
void ParcelLinkedList::displayAllParcels() const {

    if (isEmpty()) {
        cout << "\nNo parcel records available.\n";
        return;
    }

    Node* current = head;

    cout << "\n========== ALL PARCEL RECORDS ==========\n";

    while (current != nullptr) {

        current->data.displayParcel();

        current = current->next;
    }

    cout << "Total Parcels: " << count << endl;
}

// Delete a parcel using Parcel ID
bool ParcelLinkedList::deleteParcel(string parcelID) {

    if (head == nullptr) {
        cout << "Parcel records are empty.\n";
        return false;
    }

    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr) {

        if (current->data.getParcelID() == parcelID) {

            // Delete first node
            if (previous == nullptr) {
                head = current->next;
            }
            else {
                previous->next = current->next;
            }

            // Update tail if last node is deleted
            if (current == tail) {
                tail = previous;
            }

            delete current;
            count--;

            cout << "Parcel record deleted successfully.\n";
            return true;
        }

        previous = current;
        current = current->next;
    }

    cout << "Parcel ID not found.\n";
    return false;
}
