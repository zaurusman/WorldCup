//
// Created by Amir on 24/11/2022.
//

#ifndef WORLDCUP_LINKEDLIST_H
#define WORLDCUP_LINKEDLIST_H

#include <iostream>

using namespace std;


template<class T>
struct ListNode {
    ListNode *next = nullptr;
    ListNode *prev = nullptr;
    T data;
};

template<class T>
class LinkedList {
    ListNode<T> *first = nullptr;
    int number_of_nodes = 0;

public:
    LinkedList<T>() = default;

    virtual ~LinkedList() {
        if (!first) {
            return;
        }
        while (first->next) {
            first = first->next;
            first->prev->next = nullptr;
            delete first->prev;
            first->prev = nullptr;
        }

        delete first;
    }

    ListNode<T> *insert_between(ListNode<T> *before, T node, ListNode<T> *after) {
        ListNode<T> *to_insert = new ListNode<T>();
        to_insert->data = node;

        if (before && !after) {
            // insert to end of list
            before->next = to_insert;
            to_insert->prev = before;
            to_insert->next = nullptr;
        } else if (!before && after) {
            // insert to start of list
            to_insert->next = after;
            after->prev = to_insert;
            to_insert->prev = nullptr;
            first = to_insert;
        } else if (!before && !after) {
            // insert to empty list
            to_insert->next = nullptr;
            to_insert->prev = nullptr;
            first = to_insert;
        } else {
            // insert to middle of list
            before->next = to_insert;
            to_insert->prev = before;
            to_insert->next = after;
            after->prev = to_insert;
        }

        number_of_nodes++;
        return to_insert;
    }

    void print_list() {
        ListNode<T> *temp = first;

        if (!temp) {
            return;
        }

        while (temp->next) {
            cout << temp->data << ",";
            temp = temp->next;
        }
        cout << temp->data << "," << endl;
    }

    void remove_node(ListNode<T> *node) {
        ListNode<T> *before = node->prev;
        ListNode<T> *after = node->next;

        if (!before && after) {
            // removing first node
            first = after;
        } else if (before && !after) {
            // removing last node
            before->next = nullptr;
        } else if (!before && !after) {
            // removing only node
            first = nullptr;
        } else {
            // removing middle node
            before->next = after;
            after->prev = before;
        }

        number_of_nodes--;
        delete node;
    }

    int get_number_of_nodes() {
        return number_of_nodes;
    }

    void list_to_array(T* output) {
        // output is the array allocated by the caller
        ListNode<T> *temp = first;
        for (int i = 0; i < number_of_nodes; i++) {
            output[i] = temp->data;
            temp = temp->next;
        }
    }
};

#endif //WORLDCUP_LINKEDLIST_H
