#ifndef ACTIVITYSTACK_H
#define ACTIVITYSTACK_H

#include "Activity.h"

class ActivityStack {
private:
    struct Node {
        Activity data;
        Node* next;

        Node(Activity activity)
            : data(activity), next(nullptr) {}
    };

    Node* top;
    int count;

    void displayParcelHistoryRecursive(Node* current,
                                       string parcelID) const;

public:
    ActivityStack();
    ~ActivityStack();

    bool isEmpty() const;
    int getCount() const;

    void push(Activity activity);
    Activity pop();
    Activity* peek();

    void displayRecentActivities() const;
    void displayParcelHistory(string parcelID) const;
};

#endif