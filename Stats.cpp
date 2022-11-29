//
// Created by Amir on 29/11/2022.
//

#include "Stats.h"

Stats::Stats(Player &player) : player_id(&player.id), goals(&player.goals), cards(&player.cards) {}
Stats& Stats::operator=(const Stats &other) {
    if (this != &other) {
        this->player_id = other.player_id;
        this->goals = other.goals;
        this->cards = other.cards;
    }
    return *this;
}

bool Stats::operator<(const Stats &other) const {
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

bool Stats::operator>(const Stats &other) const {
    if (*goals > *other.goals) {
        return true;
    } else if (*goals == *other.goals) {
        if (*cards < *other.cards) {
            return true;
        } else if (*cards == *other.cards) {
            if (*player_id > *other.player_id) {
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

int Stats::abs(int x) {
    if (x < 0) {
        return -x;
    }
    return x;
}

bool Stats::is_next_closer(Stats prev, Stats next) {
    if (*next.goals - *goals < *goals - *prev.goals) {
        return true;
    } else if (*next.goals - *goals > *goals - *prev.goals) {
        return false;
    } else if (abs(*cards - *next.cards) < abs(*prev.cards - *cards)) {
        return true;
    } else if (abs(*cards - *next.cards) > abs(*prev.cards - *cards)) {
        return false;
    } if (*next.player_id - *player_id <= *player_id - *prev.player_id) {
        return true;
    } else {
        return false;
    }
}

int Stats::get_id() {
    return *player_id;
}