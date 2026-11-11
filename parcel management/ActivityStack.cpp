#include "ActivityStack.h"
#include <iostream>
using namespace std;

ActivityStack::ActivityStack() {
    top = nullptr;
    count = 0;
}

ActivityStack::~ActivityStack() {
    while (top != nullptr) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}

bool ActivityStack::isEmpty() const {
    return top == nullptr;
}

int ActivityStack::getCount() const {
    return count;
}

void ActivityStack::push(Activity activity) {
    Node* newNode = new Node(activity);

    newNode->next = top;
    top = newNode;

    count++;
}

Activity ActivityStack::pop() {
    if (isEmpty()) {
        cout << "Activity stack is empty.\n";
        return Activity(0, "", "", "", "");
    }

    Node* temp = top;
    Activity removedActivity = temp->data;

    top = top->next;

    delete temp;
    count--;

    return removedActivity;
}

Activity* ActivityStack::peek() {
    if (isEmpty())
        return nullptr;

    return &top->data;
}

void ActivityStack::displayRecentActivities() const {
    if (isEmpty()) {
        cout << "\nNo activities have been recorded.\n";
        return;
    }

    Node* current = top;

    cout << "\n========== RECENT PARCEL ACTIVITIES ==========\n";

    while (current != nullptr) {
        current->data.displayActivity();
        current = current->next;
    }

    cout << "\nTotal Activities: " << count << endl;
}

void ActivityStack::displayParcelHistoryRecursive(
    Node* current, string parcelID) const {

    if (current == nullptr)
        return;

    // Display older activities first.
    displayParcelHistoryRecursive(current->next, parcelID);

    if (current->data.getParcelID() == parcelID)
        current->data.displayActivity();
}

void ActivityStack::displayParcelHistory(string parcelID) const {
    if (isEmpty()) {
        cout << "\nNo activity history available.\n";
        return;
    }

    cout << "\n========== PARCEL ACTIVITY HISTORY ==========\n";
    cout << "Parcel ID: " << parcelID << endl;

    int originalCount = count;

    displayParcelHistoryRecursive(top, parcelID);

    cout << "\nTotal Activities Recorded: " << originalCount << endl;
}