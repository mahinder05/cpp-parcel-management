#include "ServiceRequest.h"
#include <iostream>
using namespace std;

ServiceRequest::ServiceRequest(string reqID, string pID, string type,
                               string recipient, int prio, int sequence) {
    requestID = reqID;
    parcelID = pID;
    serviceType = type;
    recipientID = recipient;
    priority = prio;
    sequenceNumber = sequence;
    status = "Pending";
}

string ServiceRequest::getRequestID() const { return requestID; }
string ServiceRequest::getParcelID() const { return parcelID; }
string ServiceRequest::getServiceType() const { return serviceType; }
string ServiceRequest::getRecipientID() const { return recipientID; }
int ServiceRequest::getPriority() const { return priority; }
int ServiceRequest::getSequenceNumber() const { return sequenceNumber; }
string ServiceRequest::getStatus() const { return status; }

void ServiceRequest::setStatus(string newStatus) {
    status = newStatus;
}

void ServiceRequest::displayRequest() const {
    cout << "\nRequest ID: " << requestID << endl;
    cout << "Parcel ID: " << parcelID << endl;
    cout << "Service Type: " << serviceType << endl;
    cout << "Recipient ID: " << recipientID << endl;
    cout << "Priority: ";

    if (priority == 2)
        cout << "High";
    else
        cout << "Normal";

    cout << "\nStatus: " << status << endl;
}