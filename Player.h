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
    Team *team;
    int games_played;
    int goals;
    int cards;
    bool goalkeeper;
    int games_not_played;
    ListNode<Node<Stats,shared_ptr<Player>>>* all_players_node;
    friend class Stats;

public:
    Player(int id, Team* team, int games_played, int goals, int cards, bool goalkeeper);

    ~Player() = default;

    Player& operator=(const Player & other) = default;

    int get_games_played();

    void add_games_played(int games_played);

    void add_goals(int goals);

    void add_cards(int cards);

    int get_id() const;

    int get_goals() const;

    int get_cards() const;

    ListNode<Node<Stats,shared_ptr<Player>>>* get_all_players_node();

    bool is_goalkeeper() const;

    void set_games_not_played(int games_not_played);

    void set_games_played(int games_played);

    void set_all_players_node(ListNode<Node<Stats,shared_ptr<Player>>>*);

    Team* get_team();

    void set_team(Team*);
};


#endif //WORLDCUP_PLAYER_H
