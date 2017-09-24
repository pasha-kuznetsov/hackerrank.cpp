//
// Linked Lists: Detect a Cycle
// https://www.hackerrank.com/challenges/ctci-linked-list-cycle
//
// Detect a cycle in a linked list.
// Note that the head pointer may be 'NULL' if the list is empty.
// 
// A Node is defined as: 
    struct Node {
        int data;
        struct Node* next;
    };

bool has_cycle(Node* head) {
    Node* slow = head;
    Node* fast = head ? head->next : nullptr;
    while (slow || fast) {
        if (slow == fast) return true;
        if (slow) slow = slow->next;
        if (fast) fast = fast->next;
        if (fast) fast = fast->next;
    }
    return false;
}
