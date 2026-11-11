#ifndef CIRCULARRESOURCELIST_H
#define CIRCULARRESOURCELIST_H

#include "Resource.h"

class CircularResourceList {
private:
    struct Node {
        Resource data;
        Node* next;

        Node(Resource resource)
            : data(resource), next(nullptr) {}
    };

    Node* head;
    Node* cursor;
    int count;

    Node* findResource(string resourceID) const;

public:
    CircularResourceList();
    ~CircularResourceList();

    bool isEmpty() const;
    int getCount() const;

    bool addResource(Resource resource);
    void displayResources() const;

    string assignResource(string parcelID, string requiredType);

    string getResourceType(string resourceID) const;
    string getAssignedParcel(string resourceID) const;

    bool releaseResource(string resourceID);
    bool setUnavailable(string resourceID);
    bool setAvailable(string resourceID);
};

#endif