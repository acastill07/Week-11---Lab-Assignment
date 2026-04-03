#include <iostream>
#include <string>
using namespace std;

struct ListNode {
    int id;
    string name;
    ListNode* next;
};

class NodeList {
private:
    ListNode* head;
    int count;

    ListNode* copyChain(ListNode* src) {
        if (!src) return nullptr;

        ListNode* newHead = new ListNode{src->id, src->name, nullptr};
        ListNode* newCurr = newHead;
        ListNode* srcCurr = src->next;

        while (srcCurr) {
            newCurr->next = new ListNode{srcCurr->id, srcCurr->name, nullptr};
            newCurr = newCurr->next;
            srcCurr = srcCurr->next;
        }
        return newHead;
    }

    void freeChain(ListNode* node) {
        while (node) {
            ListNode* tmp = node->next;
            delete node;
            node = tmp;
        }
    }

public:
    NodeList() : head(nullptr), count(0) {}


    ~NodeList() {
        freeChain(head);
    }

    NodeList(const NodeList& other)
        : head(copyChain(other.head)), count(other.count) {}


    NodeList& operator=(const NodeList& other) {
        if (this == &other)       
            return *this;

        freeChain(head);          
        head  = copyChain(other.head);
        count = other.count;
        return *this;
    }

    void addNode(int id, string name) {
        ListNode* n = new ListNode{id, name, head};
        head = n;
        count++;
    }

    void removeNode(int id) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr && curr->id != id) {
            prev = curr;
            curr = curr->next;
        }
        if (!curr) return;
        if (prev) prev->next = curr->next;
        else head = curr->next;
        delete curr;
        count--;
    }

    void display() const {
        ListNode* curr = head;
        while (curr) {
            cout << "[" << curr->id << ": " << curr->name << "] -> ";
            curr = curr->next;
        }
        cout << "null\n";
    }
};
