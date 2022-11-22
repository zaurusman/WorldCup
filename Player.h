//
// Created by Yotam on 19/11/2022.
//

#ifndef WORLDCUP_PLAYER_H
#define WORLDCUP_PLAYER_H

#include "Team.h"

class Team;
class Player {
    int player_id;
    int team_id;
    int games_played;
    int goals;
    int cards;
    bool goalkeeper;
    Team* his_team;
    int games_team_played_without;
    Player* next_closest;
    Player* prev_closest;

public:
    Player(int player_id, int team_id, int games_played, int goals, int cards, bool goalkeeper);

    int get_games_played();
    void set_games_played(int games_played);
    void set_goals(int goals);
    void set_cards(int cards);
};


#endif //WORLDCUP_PLAYER_H
