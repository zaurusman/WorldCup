//
// Created by Yotam on 19/11/2022.
//

#include "Player.h"

Player::Player(int id, shared_ptr<Team>& team, int games_played, int goals, int cards, bool goalkeeper):
    id(id),
    team(team),
    games_played(games_played),
    goals(goals),
    cards(cards),
    goalkeeper(goalkeeper),
    games_team_played_without(0),
    next_closest(nullptr),
    prev_closest(nullptr)
{}


int Player::get_games_played() {
    return games_played + team->get_games_played() - games_team_played_without;
}

void Player::add_games_played(int games_played) {
    this->games_played += games_played;
}

void Player::add_goals(int goals) {
    this->goals += goals;
}

void Player::add_cards(int cards) {
    this->cards += cards;
}

int Player::get_id() {
    return id;
}
int Player::get_goals() {
    return goals;
}

int Player::get_cards() {
    return cards;
}

bool Player::is_goalkeeper() {
    return goalkeeper;
}

shared_ptr<Team>& Player::get_team() {
    return team;
}