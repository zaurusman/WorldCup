//
// Created by Amir on 20/11/2022.
//

#include "worldcup23a1.h"
//#include "AVLTree.h"
#include "AVLTree.h"

int main() {
//    world_cup_t my_world_cup;
//    cout << my_world_cup.teams.get_tree_height() << endl;
//    my_world_cup.add_team(222, 99);
//    my_world_cup.add_team(200, 22);
//    my_world_cup.add_team(111, 99);
//    my_world_cup.add_team(333, 99);
//    my_world_cup.teams.inorder();
//    my_world_cup.remove_team(111);
//    my_world_cup.remove_team(200);
//    my_world_cup.remove_team(333);
//    my_world_cup.remove_team(222);
//    cout << my_world_cup.teams.get_tree_height() << endl;


    AVLTree<int,Player> my_avl_tree;
    my_avl_tree.insert(3, Player(3, 1, 0, 0, 0, false));
    my_avl_tree.insert(33, Player(11, 1, 0, 0, 0, false));
    my_avl_tree.insert(22, Player(22, 1, 0, 0, 0, false));
    my_avl_tree.insert(1, Player(10, 1, 0, 0, 0, false));
    my_avl_tree.insert(4, Player(10, 1, 0, 0, 0, false));
    my_avl_tree.insert(5, Player(10, 1, 0, 0, 0, false));

    my_avl_tree.inorder();

    my_avl_tree.remove(1);
    my_avl_tree.remove(3);
    my_avl_tree.inorder();
    my_avl_tree.remove(33);
    my_avl_tree.inorder();

    cout << "tree height is: " << my_avl_tree.get_tree_height() << endl;
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