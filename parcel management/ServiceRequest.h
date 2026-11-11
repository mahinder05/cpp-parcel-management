#ifndef SERVICEREQUEST_H
#define SERVICEREQUEST_H

#include <string>
using namespace std;

class ServiceRequest {
private:
    string requestID;
    string parcelID;
    string serviceType;
    string recipientID;
    int priority;
    int sequenceNumber;
    string status;

public:
    ServiceRequest(string reqID, string pID, string type,
                   string recipient, int prio, int sequence);

    string getRequestID() const;
    string getParcelID() const;
    string getServiceType() const;
    string getRecipientID() const;
    int getPriority() const;
    int getSequenceNumber() const;
    string getStatus() const;

    void setStatus(string newStatus);
    void displayRequest() const;
};

#endif