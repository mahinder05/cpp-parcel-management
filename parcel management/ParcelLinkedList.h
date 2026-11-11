
#ifndef PARCELLINKEDLIST_H
#define PARCELLINKEDLIST_H

#include "Parcel.h"

class ParcelLinkedList {

private:
    // Node structure
    struct Node {
        Parcel data;
        Node* next;

        Node(Parcel parcel) : data(parcel), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int count;

public:
    // Constructor and destructor
    ParcelLinkedList();
    ~ParcelLinkedList();

    // Linked list operations
    bool isEmpty() const;
    int getCount() const;

    void insertParcel(Parcel parcel);
    Parcel* searchParcel(string parcelID);
    void displayAllParcels() const;
    bool deleteParcel(string parcelID);
};

#endif
