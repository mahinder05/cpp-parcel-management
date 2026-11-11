
#ifndef PARCEL_H
#define PARCEL_H

#include <string>
using namespace std;

class Parcel {
private:
    string parcelID;
    string recipientName;
    string recipientID;
    string recipientPhone;
    string deliveryCompany;
    string parcelType;
    string arrivalDate;
    string arrivalTime;
    string status;
    string nextAction;

public:
    // Constructor
    Parcel(string id, string name, string recipient,
           string phone, string company, string type,
           string date, string time);

    // Getters
    string getParcelID() const;
    string getRecipientName() const;
    string getRecipientID() const;
    string getRecipientPhone() const;
    string getDeliveryCompany() const;
    string getParcelType() const;
    string getArrivalDate() const;
    string getArrivalTime() const;
    string getStatus() const;
    string getNextAction() const;

    // Setters
    void setRecipientName(string name);
    void setRecipientID(string id);
    void setRecipientPhone(string phone);
    void setDeliveryCompany(string company);
    void setParcelType(string type);
    void setStatus(string newStatus);
    void setNextAction(string action);

    // Display parcel information
    void displayParcel() const;
};

#endif
