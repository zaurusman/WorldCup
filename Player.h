//
// Created by Yotam on 19/11/2022.
//

#ifndef WORLDCUP_PLAYER_H
#define WORLDCUP_PLAYER_H

#include "Team.h"

class Team;

class Stats;
class Player {
    int id;
    shared_ptr<Team> team;
    int games_played;
    int goals;
    int cards;
    bool goalkeeper;
    int games_not_played = 0;
    ListNode<Node<Stats,shared_ptr<Player>>>* player_node;
    Player *next_closest;
    Player *prev_closest;
    friend class Stats;

public:
    Player(int id, shared_ptr<Team>& team, int games_played, int goals, int cards, bool goalkeeper);

    int get_games_played();

    void add_games_played(int games_played);

    void add_goals(int goals);

    void add_cards(int cards);

    int get_id();

    int get_goals();

    int get_cards();

    ListNode<Node<Stats,shared_ptr<Player>>>* get_player_node();

    bool is_goalkeeper();

    void set_games_not_played(int games_not_played);

    void set_player_node(ListNode<Node<Stats,shared_ptr<Player>>>*);

    shared_ptr<Team>& get_team();
};


#endif //WORLDCUP_PLAYER_H
