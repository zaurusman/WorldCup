//
// Created by Amir on 20/11/2022.
//

#include "worldcup23a1.h"
//#include "AVLTree.h"
#include "AVLTree.h"
#include "LinkedList.h"

int main2() {
//    LinkedList<int> my_list;
//    my_list.print_list();
//    ListNode<int>* three = my_list.insert_between(nullptr, 3, nullptr);
//    my_list.print_list();
//    ListNode<int>* one = my_list.insert_between(three, 1, nullptr);
//    my_list.print_list();
//    ListNode<int>* fourty = my_list.insert_between(nullptr, 40, three);
//    my_list.print_list();
//    my_list.remove_node(three);
//    my_list.print_list();
//    int* arr = my_list.list_to_array();
//    int n = my_list.get_number_of_nodes();
//    for (int i=0; i<n; i++) {
//        cout << arr[i] << ",,";
//    }
//
//    return 1;

    world_cup_t my_world_cup;
//    cout << my_world_cup.teams.get_tree_height() << endl;
//    my_world_cup.add_team(222, 99);
//    my_world_cup.add_team(200, 22);
    StatusType s1 = my_world_cup.add_team(111, 99);
//    my_world_cup.add_team(333, 99);
//    my_world_cup.teams.inorder();
    StatusType s2 = my_world_cup.add_player(3, 111, 1 ,4, 1, false);
    cout << "add_team status is success " << (s1==StatusType::SUCCESS) << endl;
    cout << "add_player status is success " << (s2==StatusType::SUCCESS) << endl;
//    cout << "number of all players is: " << my_world_cup.get_all_players_count(-1).ans() << endl;
    //    my_world_cup.remove_team(111);
//    StatusType s3 = my_world_cup.remove_team(111);
//    cout << "remove_team status is success " << (s3==StatusType::SUCCESS) << endl;
//    my_world_cup.remove_team(333);
//    my_world_cup.remove_team(222);
//    cout << my_world_cup.teams.get_tree_height() << endl;


//    AVLTree<Stats,shared_ptr<Player>> my_avl_tree;
//    shared_ptr<Player> player1 = make_shared<Player>(3, 1, 0, 4, 1, false);
//    shared_ptr<Player> player2 = make_shared<Player>(5, 1, 0, 5, 1, false);
//    shared_ptr<Player> player3 = make_shared<Player>(8, 1, 0, 2, 0, false);
//    shared_ptr<Player> player4 = make_shared<Player>(1, 1, 0, 5, 2, false);
//    shared_ptr<Player> player5 = make_shared<Player>(33, 1, 0, 4, 0, false);

//    Stats s1 = Stats(*player1);
//    my_avl_tree.insert(s1,player1);
//    my_avl_tree.insert(Stats(*player2),player2);
//    my_avl_tree.insert(Stats(*player3),player3);
//    my_avl_tree.insert(Stats(*player4),player4);
//    my_avl_tree.insert(Stats(*player5),player5);
//    my_avl_tree.inorder();
//    my_avl_tree.find(s1)->info->set_goals(12);
//    my_avl_tree.inorder();

//    my_avl_tree.remove(s1);
    //my_avl_tree.remove(3);
//    my_avl_tree.inorder();
    //my_avl_tree.remove(33);
   // my_avl_tree.inorder();

//    cout << "tree height is: " << my_avl_tree.get_tree_height() << endl;

//    my_avl_tree.remove(11);
//    my_avl_tree.inorder();
//    cout << "tree height is: " << my_avl_tree.get_tree_height() << endl;


//    my_avl_tree.remove(9);
//    my_avl_tree.inorder();
//    my_avl_tree.remove(10);
//    my_avl_tree.inorder();
//    my_avl_tree.insert(10, Player(10, 1, 0, 0, 0, false));
//    my_avl_tree.inorder();

}