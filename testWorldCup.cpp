//
// Created by Amir on 25/11/2022.
//


#define RUN_TEST(test) \
do { \
  cout << "     Running " << #test << "... "; \
  if (test()) { \
    cout << "[SUCCESS!]"; \
  }                    \
    else { \
    cout << "[Error]"; \
  } \
  cout << endl; \
} while(0)

#define RUN_TEST_GROUP(test) \
cout <<endl<< "Running Test Group " << #test <<":"<< endl; \
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


void test_add_team() {
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

void test_remove_team() {
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

bool test_add_player_becomes_valid() {
    world_cup_t my_wc;
    StatusType s1 = my_wc.add_team(111, 99);
    StatusType s2 = my_wc.add_player(2, 111, 0, 0, 0, false);
    StatusType s3 = my_wc.add_player(3, 111, 0, 0, 0, false);
    StatusType s4 = my_wc.add_player(4, 111, 0, 0, 0, false);
    StatusType s5 = my_wc.add_player(5, 111, 0, 0, 0, false);
    StatusType s6 = my_wc.add_player(6, 111, 0, 0, 0, false);
    StatusType s7 = my_wc.add_player(7, 111, 0, 0, 0, false);
    StatusType s8 = my_wc.add_player(8, 111, 0, 0, 0, false);
    StatusType s9 = my_wc.add_player(9, 111, 0, 0, 0, false);
    StatusType s10 = my_wc.add_player(10, 111, 0, 0, 0, false);
    StatusType s11 = my_wc.add_player(1, 111, 0, 0, 0, false);
    bool no_players = my_wc.valid_teams.get_nodes_count()==0;
    StatusType s12 = my_wc.add_player(11, 111, 0, 0, 0, false);
    bool no_keeper = my_wc.valid_teams.get_nodes_count()==0;
    StatusType s13 = my_wc.add_player(111, 111, 0, 0, 0, true);
    return my_wc.valid_teams.get_nodes_count()==1 && no_players && no_keeper;
}

void test_add_player() {
    RUN_TEST(test_add_player_valid);
    RUN_TEST(test_add_player_invalid_inputs);
    RUN_TEST(test_add_player_exists);
    RUN_TEST(test_add_player_no_team);
    RUN_TEST(test_add_player_becomes_valid);
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

bool test_remove_player_remove_add() {
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
    StatusType s2 = my_wc.remove_player(4);
    StatusType s3 = my_wc.remove_player(12);
    StatusType s4 = my_wc.remove_player(13);

    StatusType s5 = my_wc.add_player(2, 111, 12, 22, 24, false);
    StatusType s6 = my_wc.add_player(12, 222, 1, 23, 4, false);

    return s1 == StatusType::SUCCESS && s2 == StatusType::SUCCESS && s3 == StatusType::SUCCESS
        && s4 == StatusType::SUCCESS && s5 == StatusType::SUCCESS && s6 == StatusType::SUCCESS;
}

void test_remove_player() {
    RUN_TEST(test_remove_player_valid);
    RUN_TEST(test_remove_player_invalid_id);
    RUN_TEST(test_remove_player_no_player);
    RUN_TEST(test_remove_player_remove_add);
}

bool test_update_player_stats_valid() {
    world_cup_t my_wc;
    StatusType s1 = my_wc.add_team(111, 99);
    StatusType s2 = my_wc.add_player(2, 111, 0, 0, 0, false);
    StatusType s3 = my_wc.update_player_stats(2, 3, 4, 5);
    return s3==StatusType::SUCCESS && my_wc.all_players.get_root()->info->get_games_played() == 3
        && my_wc.all_players.get_root()->info->get_cards() == 5 && my_wc.all_players.get_root()->info->get_goals() == 4;
}

bool test_update_player_stats_invalid() {
    world_cup_t my_wc;
    StatusType s1 = my_wc.add_team(111, 99);
    StatusType s2 = my_wc.add_player(2, 111, 0, 0, 0, false);
    StatusType s3 = my_wc.update_player_stats(2, 3, 4, -5);
    StatusType s4 = my_wc.update_player_stats(2, 3, -4, 5);
    StatusType s5 = my_wc.update_player_stats(2, -3, 4, 5);
    return s3==StatusType::INVALID_INPUT && s4==StatusType::INVALID_INPUT && s5==StatusType::INVALID_INPUT && my_wc.all_players.get_root()->info->get_games_played() == 0
           && my_wc.all_players.get_root()->info->get_cards() == 0 && my_wc.all_players.get_root()->info->get_goals() == 0;
}

bool test_update_player_stats_no_player() {
    world_cup_t my_wc;
    StatusType s1 = my_wc.add_team(111, 99);
    StatusType s2 = my_wc.add_player(2, 111, 0, 0, 0, false);
    StatusType s3 = my_wc.update_player_stats(333, 3, 4, 5);
    return s3==StatusType::FAILURE && my_wc.all_players.get_root()->info->get_games_played() == 0
           && my_wc.all_players.get_root()->info->get_cards() == 0 && my_wc.all_players.get_root()->info->get_goals() == 0;
}

void test_update_player_stats() {
    RUN_TEST(test_update_player_stats_valid);
    RUN_TEST(test_update_player_stats_invalid);
    RUN_TEST(test_update_player_stats_no_player);
}

bool test_play_match_win() {
    world_cup_t my_wc;
    my_wc.add_team(111, 99);
    my_wc.add_player(1, 111, 0, 0, 0, false);
    my_wc.add_player(2, 111, 0, 0, 0, false);
    my_wc.add_player(3, 111, 0, 0, 0, false);
    my_wc.add_player(4, 111, 0, 0, 0, false);
    my_wc.add_player(5, 111, 0, 0, 0, false);
    my_wc.add_player(6, 111, 0, 0, 0, false);
    my_wc.add_player(7, 111, 0, 0, 0, false);
    my_wc.add_player(8, 111, 0, 0, 0, false);
    my_wc.add_player(9, 111, 0, 0, 0, false);
    my_wc.add_player(10, 111, 0, 0, 0, false);
    my_wc.add_player(11, 111, 0, 0, 0, true);

    my_wc.add_team(11, 50);
    my_wc.add_player(80, 11, 0, 0, 0, false);
    my_wc.add_player(12, 11, 0, 0, 0, false);
    my_wc.add_player(13, 11, 0, 0, 0, false);
    my_wc.add_player(14, 11, 0, 0, 0, false);
    my_wc.add_player(15, 11, 0, 0, 0, false);
    my_wc.add_player(16, 11, 0, 0, 0, false);
    my_wc.add_player(17, 11, 0, 0, 0, false);
    my_wc.add_player(18, 11, 0, 0, 0, false);
    my_wc.add_player(19, 11, 0, 0, 0, false);
    my_wc.add_player(110, 11, 0, 0, 0, false);
    my_wc.add_player(111, 11, 0, 0, 0, true);

    StatusType s1 = my_wc.play_match(11, 111);
    StatusType s2 = my_wc.play_match(111, 11);
    my_wc.add_player(999, 11, 0, 0, 0, true);
    int eee = 111; int ee = 11; int n = 999;

    return s1 == StatusType::SUCCESS && s2 == StatusType::SUCCESS && my_wc.teams.find(eee)->info->get_points() == 105
        && my_wc.teams.find(ee)->info->get_points() == 50 && my_wc.all_players.find(ee)->info->get_games_played() == 2
        && my_wc.all_players.find(n)->info->get_games_played() == 0;
}

bool test_play_match_tie() {
    world_cup_t my_wc;
    my_wc.add_team(111, 50);
    my_wc.add_player(1, 111, 0, 0, 0, false);
    my_wc.add_player(2, 111, 0, 0, 0, false);
    my_wc.add_player(3, 111, 0, 0, 0, false);
    my_wc.add_player(4, 111, 0, 0, 0, false);
    my_wc.add_player(5, 111, 0, 0, 0, false);
    my_wc.add_player(6, 111, 0, 0, 0, false);
    my_wc.add_player(7, 111, 0, 0, 0, false);
    my_wc.add_player(8, 111, 0, 0, 0, false);
    my_wc.add_player(9, 111, 0, 0, 0, false);
    my_wc.add_player(10, 111, 0, 0, 0, false);
    my_wc.add_player(11, 111, 0, 0, 0, true);

    my_wc.add_team(11, 50);
    my_wc.add_player(80, 11, 0, 0, 0, false);
    my_wc.add_player(12, 11, 0, 0, 0, false);
    my_wc.add_player(13, 11, 0, 0, 0, false);
    my_wc.add_player(14, 11, 0, 0, 0, false);
    my_wc.add_player(15, 11, 0, 0, 0, false);
    my_wc.add_player(16, 11, 0, 0, 0, false);
    my_wc.add_player(17, 11, 0, 0, 0, false);
    my_wc.add_player(18, 11, 0, 0, 0, false);
    my_wc.add_player(19, 11, 0, 0, 0, false);
    my_wc.add_player(110, 11, 0, 0, 0, false);
    my_wc.add_player(111, 11, 0, 0, 0, true);

    StatusType s1 = my_wc.play_match(11, 111);
    StatusType s2 = my_wc.play_match(111, 11);
    int eee = 111;
    int ee = 11;
    return s1 == StatusType::SUCCESS && s2 == StatusType::SUCCESS && my_wc.teams.find(eee)->info->get_points() == 52
           && my_wc.teams.find(ee)->info->get_points() == 52;
}

bool test_play_match_invalid_input() {
    world_cup_t my_wc;
    my_wc.add_team(111, 50);
    my_wc.add_team(11, 50);
    StatusType s1 = my_wc.play_match(-11, 111);
    StatusType s2 = my_wc.play_match(-111, 11);
    StatusType s3 = my_wc.play_match(11, 11);
    StatusType s4 = my_wc.play_match(10, 11);
    StatusType s5 = my_wc.play_match(11, 10);
    StatusType s6 = my_wc.play_match(111, 11);
    return s1 == StatusType::INVALID_INPUT && s2 == StatusType::INVALID_INPUT && s3 == StatusType::INVALID_INPUT
        && s4 == StatusType::FAILURE && s5 == StatusType::FAILURE && s6 == StatusType::FAILURE;
}

void test_play_match() {
    RUN_TEST(test_play_match_win);
    RUN_TEST(test_play_match_tie);
    RUN_TEST(test_play_match_invalid_input);
}

bool test_knockout_winner_win_by_id() {
    world_cup_t my_wc;
    my_wc.add_team(111, 80);
    my_wc.add_player(1, 111, 0, 0, 0, false);
    my_wc.add_player(2, 111, 0, 0, 0, false);
    my_wc.add_player(3, 111, 0, 0, 0, false);
    my_wc.add_player(4, 111, 0, 0, 0, false);
    my_wc.add_player(5, 111, 0, 0, 0, false);
    my_wc.add_player(6, 111, 0, 0, 0, false);
    my_wc.add_player(7, 111, 0, 0, 0, false);
    my_wc.add_player(8, 111, 0, 0, 0, false);
    my_wc.add_player(9, 111, 0, 0, 0, false);
    my_wc.add_player(10, 111, 0, 0, 0, false);
    my_wc.add_player(11, 111, 0, 0, 0, true);

    my_wc.add_team(17, 50);
    my_wc.add_player(80, 17, 0, 0, 0, false);
    my_wc.add_player(12, 17, 0, 0, 0, false);
    my_wc.add_player(13, 17, 0, 0, 0, false);
    my_wc.add_player(14, 17, 0, 0, 0, false);
    my_wc.add_player(15, 17, 0, 0, 0, false);
    my_wc.add_player(16, 17, 0, 0, 0, false);
    my_wc.add_player(17, 17, 0, 0, 0, false);
    my_wc.add_player(18, 17, 0, 0, 0, false);
    my_wc.add_player(19, 17, 0, 0, 0, false);
    my_wc.add_player(110, 17, 0, 0, 0, false);
    my_wc.add_player(111, 17, 0, 0, 0, true);

    my_wc.add_team(13, 50);
    my_wc.add_player(91, 13, 0, 0, 0, false);
    my_wc.add_player(92, 13, 0, 0, 0, false);
    my_wc.add_player(93, 13, 0, 0, 0, false);
    my_wc.add_player(94, 13, 0, 0, 0, false);
    my_wc.add_player(95, 13, 0, 0, 0, false);
    my_wc.add_player(96, 13, 0, 0, 0, false);
    my_wc.add_player(97, 13, 0, 0, 0, false);
    my_wc.add_player(98, 13, 0, 0, 0, false);
    my_wc.add_player(99, 13, 0, 0, 0, false);
    my_wc.add_player(100, 13, 0, 0, 0, false);
    my_wc.add_player(101, 13, 0, 0, 0, true);

    my_wc.add_team(1000, 1);
    my_wc.add_player(71, 1000, 0, 0, 0, false);
    my_wc.add_player(72, 1000, 0, 0, 0, false);
    my_wc.add_player(73, 1000, 0, 0, 0, false);
    my_wc.add_player(74, 1000, 0, 0, 0, false);
    my_wc.add_player(75, 1000, 0, 0, 0, false);
    my_wc.add_player(76, 1000, 0, 0, 0, false);
    my_wc.add_player(77, 1000, 0, 0, 0, false);
    my_wc.add_player(78, 1000, 0, 0, 0, false);
    my_wc.add_player(79, 1000, 0, 0, 0, false);
    my_wc.add_player(700, 1000, 0, 0, 0, false);
    my_wc.add_player(701, 1000, 0, 0, 0, true);

    return my_wc.knockout_winner(10, 1000).ans() == 17;
}

bool test_knockout_winner_invalid_input() {
    world_cup_t my_wc;
    my_wc.add_team(111, 50);
    my_wc.add_player(1, 111, 0, 0, 0, false);
    my_wc.add_player(2, 111, 0, 0, 0, false);
    my_wc.add_player(3, 111, 0, 0, 0, false);
    my_wc.add_player(4, 111, 0, 0, 0, false);
    my_wc.add_player(5, 111, 0, 0, 0, false);
    my_wc.add_player(6, 111, 0, 0, 0, false);
    my_wc.add_player(7, 111, 0, 0, 0, false);
    my_wc.add_player(8, 111, 0, 0, 0, false);
    my_wc.add_player(9, 111, 0, 0, 0, false);
    my_wc.add_player(10, 111, 0, 0, 0, false);
    my_wc.add_player(11, 111, 0, 0, 0, true);
    StatusType s1 = my_wc.knockout_winner(-50, 100).status();
    StatusType s2 = my_wc.knockout_winner(50, -100).status();
    StatusType s3 = my_wc.knockout_winner(50, 40).status();

    return s1 == StatusType::INVALID_INPUT && s2 == StatusType::INVALID_INPUT && s3 == StatusType::INVALID_INPUT;
}

bool test_knockout_winner_none_in_range() {
    world_cup_t my_wc;
    my_wc.add_team(111, 50);
    my_wc.add_player(1, 111, 0, 0, 0, false);
    my_wc.add_player(2, 111, 0, 0, 0, false);
    my_wc.add_player(3, 111, 0, 0, 0, false);
    my_wc.add_player(4, 111, 0, 0, 0, false);
    my_wc.add_player(5, 111, 0, 0, 0, false);
    my_wc.add_player(6, 111, 0, 0, 0, false);
    my_wc.add_player(7, 111, 0, 0, 0, false);
    my_wc.add_player(8, 111, 0, 0, 0, false);
    my_wc.add_player(9, 111, 0, 0, 0, false);
    my_wc.add_player(10, 111, 0, 0, 0, false);
    my_wc.add_player(11, 111, 0, 0, 0, true);
    StatusType s1 = my_wc.knockout_winner(50, 100).status();
    return s1 == StatusType::FAILURE;
}

void test_knockout_winner() {
    RUN_TEST(test_knockout_winner_win_by_id);
    RUN_TEST(test_knockout_winner_invalid_input);
    RUN_TEST(test_knockout_winner_none_in_range);
}

bool test_get_closest_valid() {
    world_cup_t my_wc;
    my_wc.add_team(111, 50);
    my_wc.add_player(1, 111, 0, 0, 0, false);
    my_wc.add_player(2, 111, 1, 2, 4, false);
    my_wc.add_player(3, 111, 1, 3, 5, false);
    my_wc.add_player(4, 111, 1, 4, 6, false);

    return my_wc.get_closest_player(1, 111).ans() == 2
        && my_wc.get_closest_player(4, 111).ans() == 3
        && my_wc.get_closest_player(3, 111).ans() == 4;
}

bool test_get_closest_remove() {
    world_cup_t my_wc;
    my_wc.add_team(111, 50);
    my_wc.add_player(1, 111, 0, 0, 0, false);
    my_wc.add_player(2, 111, 1, 2, 4, false);
    my_wc.add_player(3, 111, 1, 3, 5, false);
    my_wc.add_player(4, 111, 1, 4, 10, false);
    my_wc.remove_player(3);

    return my_wc.get_closest_player(2, 111).ans() == 1
        && my_wc.get_closest_player(4, 111).ans() == 2
        && my_wc.get_closest_player(3, 111).status() == StatusType::FAILURE;
}


void test_get_closest() {
    RUN_TEST(test_get_closest_valid);
    RUN_TEST(test_get_closest_remove);
}

bool test_top_scorer_valid() {
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

    return my_wc.get_top_scorer(-1).ans() == 12;
}

bool test_top_scorer_team() {
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

    return my_wc.get_top_scorer(111).ans() == 4 && my_wc.get_top_scorer(222).ans() == 12;
}


bool test_top_scorer_remove() {
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
    StatusType s2 =my_wc.remove_player(4);
    my_wc.remove_player(12);
    my_wc.remove_player(13);

    return my_wc.get_top_scorer(111).ans() == 3 && my_wc.get_top_scorer(222).ans() == 14 && s1 == StatusType::SUCCESS && s2 == StatusType::SUCCESS;
}

bool test_top_scorer_update() {
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
    StatusType s2 = my_wc.remove_player(4);
    StatusType s3 = my_wc.remove_player(12);
    StatusType s4 = my_wc.remove_player(13);
    StatusType s5 = my_wc.update_player_stats(1,2,100,1);
    StatusType s6 = my_wc.update_player_stats(11,3,300,1);

    return my_wc.get_top_scorer(111).ans() == 1 && my_wc.get_top_scorer(222).ans() == 11 && s1 == StatusType::SUCCESS && s2 == StatusType::SUCCESS && s3 == StatusType::SUCCESS && s4 == StatusType::SUCCESS && s5 == StatusType::SUCCESS && s6 == StatusType::SUCCESS;
}

void test_top_scorer() {
    RUN_TEST(test_top_scorer_valid);
    RUN_TEST(test_top_scorer_team);
    RUN_TEST(test_top_scorer_remove);
    RUN_TEST(test_top_scorer_update);
}

bool test_unite_teams_valid() {
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

    my_wc.unite_teams(111, 222, 333);
}

void test_unite_teams() {
    RUN_TEST(test_unite_teams_valid);
}

void test_world_cup() {
    RUN_TEST_GROUP(test_add_team);
    RUN_TEST_GROUP(test_remove_team);
    RUN_TEST_GROUP(test_add_player);
    RUN_TEST_GROUP(test_remove_player);
    RUN_TEST_GROUP(test_update_player_stats);
    RUN_TEST_GROUP(test_play_match);
    RUN_TEST_GROUP(test_knockout_winner);
    RUN_TEST_GROUP(test_get_closest);
    RUN_TEST_GROUP(test_top_scorer);
    RUN_TEST_GROUP(test_unite_teams);
}

int main() {
    RUN_TEST_GROUP(test_world_cup);
    return 0;
}