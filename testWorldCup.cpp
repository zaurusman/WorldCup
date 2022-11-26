//
// Created by Amir on 25/11/2022.
//


#define RUN_TEST(test) \
do { \
  cout << "     Running " << #test << "... "; \
  if (test()) { \
    cout << "[OK]"; \
  }                    \
    else { \
    cout << "[Error]"; \
  } \
  cout << endl; \
} while(0)

#define RUN_TEST_GROUP(test) \
cout << "Running Test Group " << #test << "..." << endl; \
test()


#include "worldcup23a1.h"

bool test_add_team_valid() {
    world_cup_t my_wc;
    StatusType s1 = my_wc.add_team(111, 99);
    return s1==StatusType::SUCCESS && my_wc.teams.get_nodes_count()==1 && my_wc.teams.get_tree_height()==0;
}

bool test_add_team_invalid_points() {
    world_cup_t my_wc;
    StatusType s1 = my_wc.add_team(110, -3);
    return s1==StatusType::INVALID_INPUT && my_wc.teams.get_nodes_count()==0 && my_wc.teams.get_tree_height()==-1;
}

bool test_add_team_invalid_id() {
    world_cup_t my_wc;
    StatusType s1 = my_wc.add_team(0, 89);
    StatusType s2 = my_wc.add_team(-2, 82);
    return s1==StatusType::INVALID_INPUT && s2==StatusType::INVALID_INPUT && my_wc.teams.get_nodes_count()==0 && my_wc.teams.get_tree_height()==-1;
}


bool test_add_team_existing() {
    world_cup_t my_wc;
    StatusType s1 = my_wc.add_team(111, 99);
    StatusType s2 = my_wc.add_team(111, 39);
    return s1==StatusType::SUCCESS && s2==StatusType::FAILURE && my_wc.teams.get_nodes_count()==1 && my_wc.teams.get_tree_height()==0;
}


bool test_add_team() {
    RUN_TEST(test_add_team_valid);
    RUN_TEST(test_add_team_invalid_points);
    RUN_TEST(test_add_team_invalid_id);
    RUN_TEST(test_add_team_existing);
}

bool test_remove_team_valid() {
    world_cup_t my_wc;
    StatusType s1 = my_wc.add_team(111, 99);
    StatusType s2 = my_wc.remove_team(111);
    return s1==StatusType::SUCCESS && s2==StatusType::SUCCESS && my_wc.teams.get_nodes_count()==0 && my_wc.teams.get_tree_height()==-1;
}

bool test_remove_non_existing() {
    world_cup_t my_wc;
    StatusType s1 = my_wc.add_team(111, 99);
    StatusType s2 = my_wc.remove_team(1);
    return s1==StatusType::SUCCESS && s2==StatusType::FAILURE && my_wc.teams.get_nodes_count()==1 && my_wc.teams.get_tree_height()==0;
}

bool test_remove_not_empty() {
    world_cup_t my_wc;
    StatusType s1 = my_wc.add_team(111, 99);
    StatusType s2 = my_wc.add_player(2, 111, 0, 0, 0, false);
    StatusType s3 = my_wc.remove_team(111);
    return s1==StatusType::SUCCESS && s3==StatusType::FAILURE
        && my_wc.teams.get_nodes_count()==1 && my_wc.teams.get_tree_height()==0;
}

bool test_remove_team_invalid_id() {
    world_cup_t my_wc;
    StatusType s1 = my_wc.remove_team(0);
    StatusType s2 = my_wc.remove_team(-2);
    return s1==StatusType::INVALID_INPUT && s2==StatusType::INVALID_INPUT && my_wc.teams.get_nodes_count()==0 && my_wc.teams.get_tree_height()==-1;
}

bool test_remove_team() {
    RUN_TEST(test_remove_team_valid);
    RUN_TEST(test_remove_non_existing);
    RUN_TEST(test_remove_not_empty);
    RUN_TEST(test_remove_team_invalid_id);
}

bool test_add_player_valid() {
    world_cup_t my_wc;
    StatusType s1 = my_wc.add_team(111, 99);
    StatusType s2 = my_wc.add_player(2, 111, 0, 0, 0, false);
    return s1==StatusType::SUCCESS && s2==StatusType::SUCCESS && my_wc.teams.get_nodes_count()==1 && my_wc.teams.get_tree_height()==0
        && my_wc.all_players.get_nodes_count()==1 && my_wc.all_players.get_tree_height()==0
        && my_wc.all_players_score.get_nodes_count()==1 && my_wc.all_players_score.get_tree_height()==0;
}

bool test_add_player_invalid_inputs() {
    world_cup_t my_wc;
    StatusType s1 = my_wc.add_team(111, 99);
    StatusType s2 = my_wc.add_player(-1, 111, 0, 0, 0, false);
    StatusType s3 = my_wc.add_player(2, -3, 0, 0, 0, false);
    StatusType s4 = my_wc.add_player(2, 111, -100, 0, 0, false);
    StatusType s5 = my_wc.add_player(2, 111, 0, -23, 0, false);
    StatusType s6 = my_wc.add_player(2, 111, 0, 0, -1, false);
    StatusType s7 = my_wc.add_player(2, 111, 0, 0, 3, false);
    StatusType s8 = my_wc.add_player(2, 111, 0, 3, 0, false);
    return s1==StatusType::SUCCESS &&
           s2==StatusType::INVALID_INPUT &&
           s3==StatusType::INVALID_INPUT &&
           s4==StatusType::INVALID_INPUT &&
           s5==StatusType::INVALID_INPUT &&
           s6==StatusType::INVALID_INPUT &&
           s7==StatusType::INVALID_INPUT &&
           s8==StatusType::INVALID_INPUT;
}

bool test_add_player_exists() {
    world_cup_t my_wc;
    StatusType s0 = my_wc.add_team(222, 9);
    StatusType s1 = my_wc.add_team(111, 99);
    StatusType s2 = my_wc.add_player(2, 111, 0, 0, 0, false);
    StatusType s3 = my_wc.add_player(2, 111, 0, 0, 0, false);
    StatusType s4 = my_wc.add_player(2, 222, 0, 0, 0, false);
    return s0==StatusType::SUCCESS && s1==StatusType::SUCCESS && s2==StatusType::SUCCESS && s3==StatusType::FAILURE && s4==StatusType::FAILURE;
}

bool test_add_player_no_team() {
    world_cup_t my_wc;
    StatusType s1 = my_wc.add_player(2, 111, 0, 0, 0, false);
    return s1==StatusType::FAILURE;
}

bool test_add_player() {
    RUN_TEST(test_add_player_valid);
    RUN_TEST(test_add_player_invalid_inputs);
    RUN_TEST(test_add_player_exists);
    RUN_TEST(test_add_player_no_team);
}

bool test_remove_player_valid() {
    world_cup_t my_wc;
    StatusType s1 = my_wc.add_team(111, 99);
    StatusType s2 = my_wc.add_player(2, 111, 0, 0, 0, false);
    StatusType s3 = my_wc.remove_player(2);
    return s3==StatusType::SUCCESS && my_wc.teams.get_nodes_count()==1 && my_wc.all_players.get_nodes_count()==0
        && my_wc.teams.get_tree_height()==0 && my_wc.all_players.get_tree_height()==-1;
}

bool test_remove_player_invalid_id() {
    world_cup_t my_wc;
    StatusType s1 = my_wc.add_team(111, 99);
    StatusType s2 = my_wc.add_player(2, 111, 0, 0, 0, false);
    StatusType s3 = my_wc.remove_player(-2);
    return s3==StatusType::INVALID_INPUT && my_wc.teams.get_nodes_count()==1 && my_wc.all_players.get_nodes_count()==1
           && my_wc.teams.get_tree_height()==0 && my_wc.all_players.get_tree_height()==0;
}

bool test_remove_player_no_player() {
    world_cup_t my_wc;
    StatusType s1 = my_wc.add_team(111, 99);
    StatusType s2 = my_wc.add_player(2, 111, 0, 0, 0, false);
    StatusType s3 = my_wc.remove_player(3);
    return s3==StatusType::FAILURE && my_wc.teams.get_nodes_count()==1 && my_wc.all_players.get_nodes_count()==1
           && my_wc.teams.get_tree_height()==0 && my_wc.all_players.get_tree_height()==0;
}

bool test_remove_player() {
    RUN_TEST(test_remove_player_valid);
    RUN_TEST(test_remove_player_invalid_id);
    RUN_TEST(test_remove_player_no_player);
}

bool test_world_cup() {
    RUN_TEST_GROUP(test_add_team);
    RUN_TEST_GROUP(test_remove_team);
    RUN_TEST_GROUP(test_add_player);
    RUN_TEST_GROUP(test_remove_player);
//    RUN_TEST_GROUP(test_update_player_stats);
}

int main() {
    RUN_TEST_GROUP(test_world_cup);
//    return 0;
}