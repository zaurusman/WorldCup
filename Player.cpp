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
    games_not_played(0),
    player_node(nullptr),
    next_closest(nullptr),
    prev_closest(nullptr)
{}


int Player::get_games_played() {
    return games_played + team->get_games_played() - games_not_played;
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

ListNode<Node<Stats,shared_ptr<Player>>>* Player::get_player_node(){
    return player_node;
}

bool Player::is_goalkeeper() {
    return goalkeeper;
}

void Player::set_games_not_played(int games) {
    games_not_played = games;
}

void Player::set_player_node(ListNode<Node<Stats,shared_ptr<Player>>>* node) {
    player_node = node;
}

shared_ptr<Team>& Player::get_team() {
    return team;
}