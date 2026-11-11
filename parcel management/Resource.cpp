#include "Resource.h"
#include <iostream>
using namespace std;

Resource::Resource(string id, string type) {
    resourceID = id;
    resourceType = type;
    status = "Available";
    assignedParcelID = "";
}

string Resource::getResourceID() const {
    return resourceID;
}

string Resource::getResourceType() const {
    return resourceType;
}

string Resource::getStatus() const {
    return status;
}

string Resource::getAssignedParcelID() const {
    return assignedParcelID;
}

void Resource::setStatus(string newStatus) {
    status = newStatus;
}

void Resource::setAssignedParcelID(string parcelID) {
    assignedParcelID = parcelID;
}

void Resource::displayResource() const {
    cout << "\nResource ID: " << resourceID << endl;
    cout << "Resource Type: " << resourceType << endl;
    cout << "Status: " << status << endl;

    if (assignedParcelID.empty())
        cout << "Assigned Parcel: None\n";
    else
        cout << "Assigned Parcel: " << assignedParcelID << endl;
}