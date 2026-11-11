
#include "Parcel.h"
#include <iostream>

using namespace std;

// Constructor
Parcel::Parcel(string id, string name, string recipient,
               string phone, string company, string type,
               string date, string time) {

    parcelID = id;
    recipientName = name;
    recipientID = recipient;
    recipientPhone = phone;
    deliveryCompany = company;
    parcelType = type;
    arrivalDate = date;
    arrivalTime = time;

    status = "Received";
    nextAction = "Pending Sorting";
}

// Getters
string Parcel::getParcelID() const {
    return parcelID;
}

string Parcel::getRecipientName() const {
    return recipientName;
}

string Parcel::getRecipientID() const {
    return recipientID;
}

string Parcel::getRecipientPhone() const {
    return recipientPhone;
}

string Parcel::getDeliveryCompany() const {
    return deliveryCompany;
}

string Parcel::getParcelType() const {
    return parcelType;
}

string Parcel::getArrivalDate() const {
    return arrivalDate;
}

string Parcel::getArrivalTime() const {
    return arrivalTime;
}

string Parcel::getStatus() const {
    return status;
}

string Parcel::getNextAction() const {
    return nextAction;
}

// Setters
void Parcel::setRecipientName(string name) {
    recipientName = name;
}

void Parcel::setRecipientID(string id) {
    recipientID = id;
}

void Parcel::setRecipientPhone(string phone) {
    recipientPhone = phone;
}

void Parcel::setDeliveryCompany(string company) {
    deliveryCompany = company;
}

void Parcel::setParcelType(string type) {
    parcelType = type;
}

void Parcel::setStatus(string newStatus) {
    status = newStatus;
}

void Parcel::setNextAction(string action) {
    nextAction = action;
}

// Display parcel information
void Parcel::displayParcel() const {

    cout << "\n========== PARCEL DETAILS ==========\n";

    cout << "Parcel ID: " << parcelID << endl;
    cout << "Recipient Name: " << recipientName << endl;
    cout << "Recipient ID: " << recipientID << endl;
    cout << "Phone Number: " << recipientPhone << endl;
    cout << "Delivery Company: " << deliveryCompany << endl;
    cout << "Parcel Type: " << parcelType << endl;
    cout << "Arrival Date: " << arrivalDate << endl;
    cout << "Arrival Time: " << arrivalTime << endl;
    cout << "Status: " << status << endl;
    cout << "Next Action: " << nextAction << endl;

    cout << "====================================\n";
}
