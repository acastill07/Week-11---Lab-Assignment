#include <iostream>
#include <string>
#include <memory>
using namespace std;

struct SmartListNode {
    int id;
    string name;
    unique_ptr<SmartListNode> next;

    SmartListNode(int i, string n, unique_ptr<SmartListNode> nx)
        : id(i), name(n), next(move(nx)) {}
};

class SmartNodeList {
private:
    unique_ptr<SmartListNode> head;
    int count;

public:
    SmartNodeList() : head(nullptr), count(0) {}

    void addNode(int id, string name) {
        head = make_unique<SmartListNode>(id, name, move(head));
        count++;
    }

    void removeNode(int id) {
        SmartListNode* prev = nullptr;
        SmartListNode* curr = head.get();

        while (curr && curr->id != id) {
            prev = curr;
            curr = curr->next.get();
        }
        if (!curr) return;   

        if (prev) {
            
            prev->next = move(curr->next);
        } else {
            head = move(head->next);
        }
        count--;
    }

    void display() const {
        SmartListNode* curr = head.get();   
        while (curr) {
            cout << "[" << curr->id << ": " << curr->name << "] -> ";
            curr = curr->next.get();
        }
        cout << "null\n";
    }
};
