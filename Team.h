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
    private:
        unsigned int id;
        AVL<int, Player> players;
        int numberOfPlayers;
        int teamPower;
        int gamesPlayed;
        unsigned int topScorerId;
        char* topScorerName;
        bool hasGoalkeeper;
        bool isEmpty;

    public:
    Team() = default;
};


#endif //WORLDCUP_TEAM_H
