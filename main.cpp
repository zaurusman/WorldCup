//
// Created by Amir on 20/11/2022.
//

#include "worldcup23a1.h"
//#include "AVLTree.h"
#include "AVLTree.h"
#include "LinkedList.h"

int main2() {
    world_cup_t my_wc;
    my_wc.add_team(111, 50);
    my_wc.add_team(222, 50);
    my_wc.add_player(1, 111, 0, 0, 0, false);
    my_wc.add_player(2, 111, 1, 2, 4, false);
    my_wc.add_player(3, 111, 1, 3, 5, false);
    my_wc.add_player(4, 111, 1, 4, 10, false);
    my_wc.add_player(11, 222, 1, 1, 0, false);
    my_wc.add_player(12, 222, 1, 23, 4, false);
    my_wc.add_player(13, 222, 13, 3, 54, false);
    my_wc.add_player(14, 222, 1, 4, 13, false);
    StatusType s1 = my_wc.remove_player(2);
    return 0;
}