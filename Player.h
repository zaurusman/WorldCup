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
    shared_ptr<Team> his_team;
    int games_played;
    int goals;
    int cards;
    bool goalkeeper;
    int games_team_played_without;
    Player *next_closest;
    Player *prev_closest;
    friend class Stats;

public:
    Player(int id, shared_ptr<Team> team, int games_played, int goals, int cards, bool goalkeeper);

    int get_games_played();

    void set_games_played(int games_played);

    void set_goals(int goals);

    void set_cards(int cards);

    int get_id();

    int get_goals();

    int get_cards();

    shared_ptr<Team>& get_team();
};

class Stats{
    int *player_id;
    int *goals;
    int *cards;

    friend std::ostream &operator<<(std::ostream &os, const Stats &obj) {
        os << "goals: " << *obj.goals << ", cards: " << *obj.cards << ", player_id: " << *obj.player_id << endl;
        return os;
    }

public:
    //Stats(shared_ptr<int>& player_id,shared_ptr<int>& goals,shared_ptr<int>& cards):player_id(player_id), goals(goals), cards(cards){}
    Stats(Player &player) : player_id(&player.id), goals(&player.goals), cards(&player.cards) {}

    Stats &operator=(const Stats &other) {
        if (this != &other) {
            this->player_id = other.player_id;
            this->goals = other.goals;
            this->cards = other.cards;
        }
        return *this;
    }

    bool operator<(const Stats &other) const {
        if (*goals < *other.goals) {
            return true;
        } else if (*goals == *other.goals) {
            if (*cards > *other.cards) {
                return true;
            } else if (*cards == *other.cards) {
                if (*player_id < *other.player_id) {
                    return true;
                } else {
                    return false;
                }
            }
        }
        return false;
    }

    bool operator>(const Stats &other) const {
        if (goals < other.goals) {
            return true;
        } else if (goals == other.goals) {
            if (cards > other.cards) {
                return true;
            } else if (cards == other.cards) {
                if (player_id < other.player_id) {
                    return true;
                } else {
                    return false;
                }
            }
        }
        return false;
    }
};


#endif //WORLDCUP_PLAYER_H
