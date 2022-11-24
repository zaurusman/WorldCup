//
// Created by Yotam on 19/11/2022.
//

#include "Player.h"

Player::Player(int player_id, int team_id, int games_played, int goals, int cards, bool goalkeeper):
    player_id(player_id),
    team_id(team_id),
    games_played(games_played),
    goals(goals),
    cards(cards),
    goalkeeper(goalkeeper),
    his_team(nullptr),
    games_team_played_without(0),
    next_closest(nullptr),
    prev_closest(nullptr)
{}


int Player::get_games_played() {
    return games_played + his_team->get_games_played() - games_team_played_without;
}

void Player::set_games_played(int ngames_played) {
    games_played += ngames_played;
}

void Player::set_goals(int ngoals) {
    goals+=ngoals;
}

void Player::set_cards(int ncards) {
    cards+=ncards;
}

int Player::get_id() {
    return player_id;
}
int Player::get_goals() {
    return goals;
}

int Player::get_cards() {
    return cards;
}
Team* Player::get_team() {
    return his_team;
}