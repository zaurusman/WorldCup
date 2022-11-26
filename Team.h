//
// Created by Yotam on 19/11/2022.
//

#ifndef WORLDCUP_TEAM_H
#define WORLDCUP_TEAM_H

#include "wet1util.h"
#include "AVLTree.h"
#include "Player.h"
#include <memory>

class Player;
class Stats;

class Team {
    int team_id;
    int points;
    AVLTree<int, shared_ptr<Player>> players;
    AVLTree<Stats, shared_ptr<Player>> players_score;
    int number_of_players;
    int total_goals;
    int total_cards;
    int games_played;
    int top_scorer_id; // TODO: Player top_scorer, remove top_scorer_name also
    char *top_scorer_name;
    bool has_goalkeeper = false;
    int strength = 0;

    //static int calc_strength(shared_ptr<Node<int, shared_ptr<Player>>& root);

public:
    Team() = default;
    ~Team() = default;

    Team(int team_id, int points);

    bool is_empty();

    int get_team_power();

    int get_games_played();

    void add_games_played(int games);

    int get_number_of_players();

    int get_strength();

    bool goalkeeper();

    AVLTree<int, shared_ptr<Player>>& get_players();

    void update_strength();

    void set_points(int points);
};


#endif //WORLDCUP_TEAM_H
