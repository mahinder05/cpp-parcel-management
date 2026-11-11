
#ifndef PARCELBST_H
#define PARCELBST_H

#include <string>
using namespace std;

class Task1;

class ParcelBST {
private:
    struct Node {
        string parcelID;
        Node* left;
        Node* right;

        Node(string id) {
            parcelID = id;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;

    Node* insertNode(Node* current, string parcelID, bool& inserted);
    Node* searchNode(Node* current, string parcelID) const;
    Node* deleteNode(Node* current, string parcelID, bool& deleted);
    Node* findMinimum(Node* current) const;
    void destroyTree(Node* current);
    void displayInOrder(Node* current, Task1& parcelSystem) const;

public:
    ParcelBST();
    ~ParcelBST();

    bool isEmpty() const;
    bool insert(string parcelID);
    bool search(string parcelID) const;
    bool remove(string parcelID);

    void displayAll(Task1& parcelSystem) const;
};

#endif
