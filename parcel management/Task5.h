
#ifndef TASK5_H
#define TASK5_H

#include "Task1.h"
#include "ParcelBST.h"

class Task5 {
private:
    Task1& parcelSystem;
    ParcelBST parcelTree;

public:
    Task5(Task1& system);

    void insertParcel();
    void searchParcel();
    void displayParcels();
    void updateParcel();
    void deleteParcel();

    void displayMenu();
};

#endif
