#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
using namespace std;

class Resource {
private:
    string resourceID;
    string resourceType;
    string status;
    string assignedParcelID;

public:
    Resource(string id, string type);

    string getResourceID() const;
    string getResourceType() const;
    string getStatus() const;
    string getAssignedParcelID() const;

    void setStatus(string newStatus);
    void setAssignedParcelID(string parcelID);

    void displayResource() const;
};

#endif