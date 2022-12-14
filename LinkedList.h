//
// Created by Amir on 24/11/2022.
//

#ifndef WORLDCUP_LINKEDLIST_H
#define WORLDCUP_LINKEDLIST_H

#include <iostream>
#include "Exception.h"

using namespace std;

template<class T>
class ListNode {
public:
    ListNode *next = nullptr;
    ListNode *prev = nullptr;
    T data;

    ListNode<T>() = default;


//    ListNode<T>(ListNode<T>& other) {
//        next = nullptr;
//        prev = nullptr;
//        data = other.data;
//    }
};

template<class T>
class LinkedList {
private:
    ListNode<T> *first = nullptr;
    ListNode<T> *last = nullptr;
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

    ListNode<T>* get_first() {
        return first;
    }

    ListNode<T>* get_last() {
        return last;
    }

    void push_front(const T& data) {
        auto *to_insert = new ListNode<T>();
        to_insert->data = data;
        if(first) {
            to_insert->next = first;
            first->prev = to_insert;
        } else {
            last = to_insert;
        }
        first = to_insert;
    }

    T pop_front() {
        if (!first) {
            throw EmptyList();
        }
        ListNode<T>* temp = first;
        T temp_val = temp->data;
        if (first->next) {
            first = first->next;
        } else {
            first = nullptr;
            last = nullptr;
        }

        delete temp;
        return temp_val;
    }

    void push_back(const T& data) {
        auto *to_insert = new ListNode<T>();
        to_insert->data = data;
        if(last) {
            to_insert->prev = last;
            last->next = to_insert;
        } else {
            first = to_insert;
        }
        last = to_insert;
        number_of_nodes++;
    }

    ListNode<T> *insert_after(ListNode<T> *before, const T& node) {
        auto *to_insert = new ListNode<T>();
        to_insert->data = node;
        if (!before && !last) {
            // insert to empty list
            to_insert->prev = nullptr;
            to_insert->next = nullptr;
            last = to_insert;
            first = to_insert;

        } else if (!before && last) {
            // insert to end of list
            to_insert->next = first;
            first->prev = to_insert;
            first = to_insert;

        } else if (before->next) {
            // insert to middle of list
            before->next->prev = to_insert;
            to_insert->next = before->next;
            before->next = to_insert;
            to_insert->prev = before;

        } else { //after && !after->next
            // insert to start of list
            to_insert->prev = last;
            last->next = to_insert;
            last = to_insert;
        }

        return to_insert;
    }

    ListNode<T> *insert_before(ListNode<T> *after, const T& node) {
        auto *to_insert = new ListNode<T>();
        to_insert->data = node;
        if (!after && !first) {
            // insert to empty list
            to_insert->next = nullptr;
            to_insert->prev = nullptr;
            first = to_insert;
            last = to_insert;

        } else if (!after && first) {
            // insert to end of list
            to_insert->prev = last;
            last->next = to_insert;
            last = to_insert;

        } else if (after->prev) {
            // insert to middle of list
            after->prev->next = to_insert;
            to_insert->prev = after->prev;
            after->prev = to_insert;
            to_insert->next = after;

        } else { //after && !after->prev
            // insert to start of list
            to_insert->next = first;
            first->prev = to_insert;
            first = to_insert;
        }

        return to_insert;
    }

    ListNode<T> *insert_between(ListNode<T> *before, const T& node, ListNode<T> *after) {
        auto *to_insert = new ListNode<T>();
        to_insert->data = node;

        if (before && !after) {
            // insert to end of list
            before->next = to_insert;
            to_insert->prev = before;
            to_insert->next = nullptr;
            last = to_insert;
        } else if (!before && after) {
            // insert to start of list
            to_insert->next = after;
            after->prev = to_insert;
            to_insert->prev = nullptr;
            first = to_insert;
        } else if (!before) {
            // insert to empty list
            to_insert->next = nullptr;
            to_insert->prev = nullptr;
            first = to_insert;
            last = to_insert;
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

//    void print_list() {
//        ListNode<T> *temp = first;
//
//        if (!temp) {
//            return;
//        }
//
//        while (temp->next) {
//            cout << temp->data << ",";
//            temp = temp->next;
//        }
//        cout << temp->data << "," << endl;
//    }

    void remove_node(ListNode<T> *node) {
        ListNode<T> *before = node->prev;
        ListNode<T> *after = node->next;
        if(!node){
            throw std::invalid_argument("the node to be removed is nullptr");
        }
        if (!before && after) {
            // removing first node
            first = after;
            first->prev = nullptr;
        } else if (before && !after) {
            // removing last node
            last = before;
            last->next = nullptr;
        } else if (!before) {
            // removing only node
            first = nullptr;
            last = nullptr;
        } else {
            // removing middle node
            before->next = after;
            after->prev = before;
        }

        number_of_nodes--;
        delete node;
    }

//    void list_to_array(T* output) {
//        // output is the array allocated by the caller
//        ListNode<T> *temp = first;
//        for (int i = 0; i < number_of_nodes; i++) {
//            output[i] = temp->data;
//            temp = temp->next;
//        }
//    }

    static void merge_sorted(LinkedList<T> &list1, LinkedList<T> &list2, LinkedList<T>& new_list) {
        ListNode<T> *node1 = list1.get_first();
        ListNode<T> *node2 = list2.get_first();
        ListNode<T> *new_node=nullptr;
        new_list.first = new_node;
        ListNode<T> *before = nullptr;
        while(node1 && node2) {
            if(node1->data > node2->data) {
                before = new_list.insert_between(before, node2->data, nullptr);
                node2 = node2->next;
            }
            else if(node1->data <= node2->data) {
                before = new_list.insert_between(before, node1->data, nullptr);
                node1 = node1->next;
            }
        }
        while(node1) {
            before = new_list.insert_between(before, node1->data, nullptr);
            node1 = node1->next;
        }
        while(node2) {
            before = new_list.insert_between(before, node2->data, nullptr);
            node2 = node2->next;
        }
    }
};


#endif //WORLDCUP_LINKEDLIST_H
