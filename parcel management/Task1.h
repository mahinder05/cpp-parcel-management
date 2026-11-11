
#ifndef TASK1_H
#define TASK1_H

#include "ParcelLinkedList.h"
#include "ParcelQueue.h"

class Task1 {

private:
    ParcelLinkedList parcelList;

    // Processing queues
    ParcelQueue incomingQueue;
    ParcelQueue collectionQueue;
    ParcelQueue deliveryQueue;
    ParcelQueue specialQueue;
    ParcelQueue returnQueue;
    ParcelQueue holdQueue;

    int nextParcelNumber;

    string generateParcelID();
    bool isValidInput(string input);

public:
    Task1();

    void registerParcel();
    void displayAllParcels();
    void searchParcel();
    void updateParcel();
    void removeParcel();

    void displayIncomingQueue();
    void displayMenu();
    Parcel* findParcelByID(string id);
    bool deleteParcelRecord(string id);
};

#endif
