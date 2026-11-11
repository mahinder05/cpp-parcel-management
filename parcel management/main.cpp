
#include <iostream>
#include <limits>

#include "Task1.h"
#include "Task2.h"
#include "Task3.h"
#include "Task4.h"
#include "Task5.h"

using namespace std;

int main() {
    Task1 parcelSystem;

    Task4 activitySystem(parcelSystem);

    Task2 serviceSystem(parcelSystem, activitySystem);

    Task3 resourceSystem(parcelSystem, activitySystem);

    Task5 categorySystem(parcelSystem);

    int choice;

    cout << "Welcome to Smart Campus Parcel Management System!\n";

    do {
        cout << "\n====================================\n";
        cout << " SMART CAMPUS PARCEL MANAGEMENT\n";
        cout << "====================================\n";
        cout << "1. Parcel Intake Management (Task 1)\n";
        cout << "2. Service Request Management (Task 2)\n";
        cout << "3. Resource Management (Task 3)\n";
        cout << "4. Activity Management (Task 4)\n";
        cout << "5. Parcel Category Organization (Task 5)\n";
        cout << "0. Exit System\n";
        cout << "\nEnter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a number.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: parcelSystem.displayMenu(); break;
            case 2: serviceSystem.displayMenu(); break;
            case 3: resourceSystem.displayMenu(); break;
            case 4: activitySystem.displayMenu(); break;
            case 5: categorySystem.displayMenu(); break;
            case 0: cout << "Thank you for using the system.\n"; break;
            default: cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}
