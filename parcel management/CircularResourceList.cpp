#include "CircularResourceList.h"
#include <iostream>
using namespace std;

CircularResourceList::CircularResourceList() {
    head = nullptr;
    cursor = nullptr;
    count = 0;
}

CircularResourceList::~CircularResourceList() {
    if (head == nullptr)
        return;

    Node* current = head->next;

    while (current != head) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }

    delete head;

    head = nullptr;
    cursor = nullptr;
    count = 0;
}

bool CircularResourceList::isEmpty() const {
    return head == nullptr;
}

int CircularResourceList::getCount() const {
    return count;
}

CircularResourceList::Node*
CircularResourceList::findResource(string resourceID) const {
    if (isEmpty())
        return nullptr;

    Node* current = head;

    do {
        if (current->data.getResourceID() == resourceID)
            return current;

        current = current->next;

    } while (current != head);

    return nullptr;
}

bool CircularResourceList::addResource(Resource resource) {
    if (findResource(resource.getResourceID()) != nullptr)
        return false;

    Node* newNode = new Node(resource);

    if (head == nullptr) {
        head = newNode;
        newNode->next = head;
        cursor = head;
    }
    else {
        Node* last = head;

        while (last->next != head)
            last = last->next;

        last->next = newNode;
        newNode->next = head;
    }

    count++;
    return true;
}

void CircularResourceList::displayResources() const {
    if (isEmpty()) {
        cout << "\nNo resources have been registered.\n";
        return;
    }

    Node* current = head;
    int available = 0;
    int occupied = 0;
    int unavailable = 0;

    cout << "\n========== RESOURCE LIST ==========\n";

    do {
        current->data.displayResource();

        if (current->data.getStatus() == "Available")
            available++;
        else if (current->data.getStatus() == "Occupied")
            occupied++;
        else
            unavailable++;

        current = current->next;

    } while (current != head);

    cout << "\n========== RESOURCE SUMMARY ==========\n";
    cout << "Total Resources: " << count << endl;
    cout << "Available: " << available << endl;
    cout << "Occupied: " << occupied << endl;
    cout << "Unavailable: " << unavailable << endl;
}

string CircularResourceList::assignResource(
    string parcelID, string requiredType) {

    if (isEmpty())
        return "";

    Node* current = cursor;

    for (int i = 0; i < count; i++) {
        if (current->data.getStatus() == "Available" &&
            current->data.getResourceType() == requiredType) {

            current->data.setStatus("Occupied");
            current->data.setAssignedParcelID(parcelID);

            string assignedID = current->data.getResourceID();

            // Move cursor forward for the next allocation.
            cursor = current->next;

            return assignedID;
        }

        current = current->next;
    }

    return "";
}

string CircularResourceList::getResourceType(string resourceID) const {
    Node* found = findResource(resourceID);

    if (found == nullptr)
        return "";

    return found->data.getResourceType();
}

string CircularResourceList::getAssignedParcel(string resourceID) const {
    Node* found = findResource(resourceID);

    if (found == nullptr)
        return "";

    return found->data.getAssignedParcelID();
}

bool CircularResourceList::releaseResource(string resourceID) {
    Node* found = findResource(resourceID);

    if (found == nullptr ||
        found->data.getStatus() != "Occupied")
        return false;

    found->data.setStatus("Available");
    found->data.setAssignedParcelID("");

    return true;
}

bool CircularResourceList::setUnavailable(string resourceID) {
    Node* found = findResource(resourceID);

    if (found == nullptr ||
        found->data.getStatus() != "Available")
        return false;

    found->data.setStatus("Unavailable");
    return true;
}

bool CircularResourceList::setAvailable(string resourceID) {
    Node* found = findResource(resourceID);

    if (found == nullptr ||
        found->data.getStatus() != "Unavailable")
        return false;

    found->data.setStatus("Available");
    return true;
}