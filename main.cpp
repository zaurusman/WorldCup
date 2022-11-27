//
// Created by Amir on 20/11/2022.
//

#include "worldcup23a1.h"
//#include "AVLTree.h"
#include "AVLTree.h"
#include "LinkedList.h"

int main2() {
    LinkedList<int> my_list1;
    LinkedList<int> my_list2;
//    ListNode<int> one = my_list1.insert_between(nullptr,1,nullptr);

//    my_list.print_list();
    my_list1.push_front(40);
    my_list1.push_front(3);
    my_list1.push_front(1);

//    ListNode<int>* three = my_list1.insert_between(nullptr, 3, nullptr);
//    ListNode<int>* one = my_list1.insert_between(nullptr, 1, three);
//    ListNode<int>* fourty = my_list1.insert_between(three, 40, nullptr);

    ListNode<int>* two = my_list2.insert_between(nullptr,2,nullptr);
    ListNode<int>* five = my_list2.insert_between(two,5,nullptr);
    ListNode<int>* eight = my_list2.insert_between(five,8,nullptr);
    ListNode<int>* eleven = my_list2.insert_between(eight,11,nullptr);

    my_list1.print_list();
    my_list2.print_list();

    LinkedList<int> merged;
    LinkedList<int>::merge_sorted(my_list1, my_list2, merged);
    merged.print_list();


    world_cup_t my_wc;
    my_wc.add_team(111, 99);
    my_wc.add_team(222, 99);
    my_wc.add_team(333, 99);
    my_wc.add_team(555, 99);
    my_wc.add_team(444, 99);
    my_wc.add_player(2, 111, 0, 0, 0, false);
    my_wc.add_player(4, 111, 0, 0, 0, false);
    my_wc.add_player(5, 111, 0, 0, 0, false);
    my_wc.add_player(7, 111, 0, 0, 0, false);
    my_wc.add_player(8, 111, 0, 0, 0, false);
    LinkedList<Node<int,shared_ptr<Team>>> out;
    AVLTree<int,shared_ptr<Team>>::AVL_to_list_inorder(my_wc.teams.get_root(),out);

    cout << "hi" << endl;


    //    my_list.remove_node(three);
//    my_list.print_list();
//    int* arr = my_list.list_to_array();
//    int n = my_list.get_number_of_nodes();
//    for (int i=0; i<n; i++) {
//        cout << arr[i] << ",,";
//    }
//

}