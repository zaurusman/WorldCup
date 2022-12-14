//
// Created by Yotam on 19/11/2022.
//

#ifndef WORLDCUP_TEAM_H
#define WORLDCUP_TEAM_H

#include "wet1util.h"
#include "AVLTree.h"
#include "Player.h"
#include "Stats.h"
#include <memory>

class Player;
class Stats;

class Team {
private:
    int id;
    int points;
    int goalkeepers;
    int total_goals;
    int total_cards;
    int games_played;
    AVLTree<int, shared_ptr<Player>> players;
    AVLTree<Stats, shared_ptr<Player>> players_score;
    shared_ptr<Node<Stats,shared_ptr<Player>>> top_scorer;

public:
    Team() = default;
    ~Team() = default;

    Team(int team_id, int points);

    bool is_empty();

    int get_id() const;

    int get_games_played() const;

    void add_games_played(int games);

    int get_players_count();

    int get_strength() const;

    int get_points() const;

    void add_goalkeeper(int goalkeeper);

    bool has_goalkeeper() const;

    int get_goalkeepers() const;

    void add_total_goals(int goals);

    void add_total_cards(int cards);

    int get_goals() const;

    int get_cards() const;

    AVLTree<int, shared_ptr<Player>>& get_players();

    shared_ptr<Node<Stats,shared_ptr<Player>>> get_top_scorer();

    void set_top_scorer(shared_ptr<Node<Stats,shared_ptr<Player>>> top_scorer);

    void set_players(AVLTree<int,shared_ptr<Player>>& players);

    void set_players_score(AVLTree<Stats,shared_ptr<Player>>& players_score);

    AVLTree<Stats, shared_ptr<Player>>& get_players_score();

    void add_points(int points);

    void empty_players();


};


#endif //WORLDCUP_TEAM_H
