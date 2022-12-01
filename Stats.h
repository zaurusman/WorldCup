//
// Created by Amir on 29/11/2022.
//

#ifndef WORLDCUP_STATS_H
#define WORLDCUP_STATS_H

#include <iostream>
#include "Player.h"

class Player;
class Stats{
    int *player_id;
    int *goals;
    int *cards;

    friend std::ostream &operator<<(std::ostream &os, const Stats &obj) {
        os << "goals: " << *obj.goals << ", cards: " << *obj.cards << ", player_id: " << *obj.player_id << endl;
        return os;
    }

public:
    explicit Stats(Player &player);

    Stats() = default;

    Stats &operator=(const Stats &other);

    bool operator<(const Stats &other) const;

    bool operator>(const Stats &other) const;

    bool is_next_closer(Stats prev, Stats next);

    int get_id();

};

#endif //WORLDCUP_STATS_H
