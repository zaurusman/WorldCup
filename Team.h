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
private:
    int id;
    int points;
    AVLTree<int, shared_ptr<Player>> players;
    AVLTree<Stats, shared_ptr<Player>> players_score;
    int total_goals;
    int total_cards;
    int games_played;
    shared_ptr<Player> top_scorer;
    bool has_goalkeeper = false;

    //static int calc_strength(shared_ptr<Node<int, shared_ptr<Player>>& root);

public:
    Team() = default;
    ~Team() = default;

    Team(int team_id, int points);

    bool is_empty();

    int get_id();

    int get_team_power();

    int get_games_played();

    void add_games_played(int games);

    int get_players_count();

    int get_strength();

    int get_points();

    shared_ptr<Player>& get_top_scorer();

    bool goalkeeper();

    void add_total_goals(int goals);

    void add_total_cards(int cards);

    AVLTree<int, shared_ptr<Player>>& get_players();

    AVLTree<Stats, shared_ptr<Player>>& get_players_score();

//    void update_strength();

    void add_points(int points);
};


#endif //WORLDCUP_TEAM_H
