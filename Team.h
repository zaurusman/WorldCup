//
// Created by Yotam on 19/11/2022.
//

#ifndef WORLDCUP_TEAM_H
#define WORLDCUP_TEAM_H

#include "wet1util.h"
#include "AVLTree.h"
#include "Player.h"
#include <memory>
class Team {
    int team_id;
    int points;
    AVL<int, Player> players;
    int number_of_players;
    int total_goals;
    int total_cards;
    int games_played;
    int top_scorer_id;
    char* top_scorer_name;
    bool has_goalkeeper;

public:
    Team(int team_id, int points);

    int is_empty();

    int get_team_power();

    int get_games_played();

};


#endif //WORLDCUP_TEAM_H
