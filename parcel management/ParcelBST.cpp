
#include "ParcelBST.h"
#include "Task1.h"
#include <iostream>
using namespace std;

ParcelBST::ParcelBST() {
    root = nullptr;
}

ParcelBST::~ParcelBST() {
    destroyTree(root);
}

bool ParcelBST::isEmpty() const {
    return root == nullptr;
}

void ParcelBST::destroyTree(ParcelBST::Node* current) {
    if (current == nullptr) return;

    destroyTree(current->left);
    destroyTree(current->right);

    delete current;
}

// Insert a parcel ID into the BST
ParcelBST::Node* ParcelBST::insertNode(
    ParcelBST::Node* current,
    string parcelID,
    bool& inserted
) {
    if (current == nullptr) {
        inserted = true;
        return new ParcelBST::Node(parcelID);
    }

    if (parcelID < current->parcelID) {
        current->left = insertNode(current->left, parcelID, inserted);
    }
    else if (parcelID > current->parcelID) {
        current->right = insertNode(current->right, parcelID, inserted);
    }
    else {
        inserted = false;
    }

    return current;
}

bool ParcelBST::insert(string parcelID) {
    bool inserted = false;
    root = insertNode(root, parcelID, inserted);
    return inserted;
}

// Search for a parcel ID
ParcelBST::Node* ParcelBST::searchNode(
    ParcelBST::Node* current,
    string parcelID
) const {
    if (current == nullptr || current->parcelID == parcelID) {
        return current;
    }

    if (parcelID < current->parcelID) {
        return searchNode(current->left, parcelID);
    }

    return searchNode(current->right, parcelID);
}

bool ParcelBST::search(string parcelID) const {
    return searchNode(root, parcelID) != nullptr;
}

// Find the smallest value in a subtree
ParcelBST::Node* ParcelBST::findMinimum(
    ParcelBST::Node* current
) const {
    while (current != nullptr && current->left != nullptr) {
        current = current->left;
    }

    return current;
}

// Delete a node from the BST
ParcelBST::Node* ParcelBST::deleteNode(
    ParcelBST::Node* current,
    string parcelID,
    bool& deleted
) {
    if (current == nullptr) {
        return nullptr;
    }

    if (parcelID < current->parcelID) {
        current->left = deleteNode(current->left, parcelID, deleted);
    }
    else if (parcelID > current->parcelID) {
        current->right = deleteNode(current->right, parcelID, deleted);
    }
    else {
        deleted = true;

        // Case 1: No child
        if (current->left == nullptr && current->right == nullptr) {
            delete current;
            return nullptr;
        }

        // Case 2: Only right child
        if (current->left == nullptr) {
            ParcelBST::Node* temp = current->right;
            delete current;
            return temp;
        }

        // Case 2: Only left child
        if (current->right == nullptr) {
            ParcelBST::Node* temp = current->left;
            delete current;
            return temp;
        }

        // Case 3: Two children
        ParcelBST::Node* successor = findMinimum(current->right);

        current->parcelID = successor->parcelID;

        bool successorDeleted = false;

        current->right = deleteNode(
            current->right,
            successor->parcelID,
            successorDeleted
        );
    }

    return current;
}

bool ParcelBST::remove(string parcelID) {
    bool deleted = false;
    root = deleteNode(root, parcelID, deleted);
    return deleted;
}

// Display parcels using in-order traversal
void ParcelBST::displayInOrder(
    ParcelBST::Node* current,
    Task1& parcelSystem
) const {
    if (current == nullptr) return;

    displayInOrder(current->left, parcelSystem);

    cout << "\n----------------------------------\n";

    Parcel* parcel = parcelSystem.findParcelByID(current->parcelID);

    if (parcel != nullptr) {
        parcel->displayParcel();
    }
    else {
        cout << "Parcel " << current->parcelID
             << " no longer exists in the main records.\n";
    }

    displayInOrder(current->right, parcelSystem);
}

void ParcelBST::displayAll(Task1& parcelSystem) const {
    if (isEmpty()) {
        cout << "\nThe parcel BST is empty.\n";
        return;
    }

    cout << "\n========== PARCELS IN BST ==========\n";

    displayInOrder(root, parcelSystem);

    cout << "\n====================================\n";
}