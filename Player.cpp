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
    all_players_node(nullptr)
{}


int Player::get_games_played() {
    return games_played + team->get_games_played() - games_not_played;
}

void Player::add_games_played(int new_games_played) {
    this->games_played += new_games_played;
}

void Player::add_goals(int new_goals) {
    this->goals += new_goals;
}

void Player::add_cards(int new_cards) {
    this->cards += new_cards;
}

int Player::get_id() const {
    return id;
}
int Player::get_goals() const {
    return goals;
}

int Player::get_cards() const {
    return cards;
}

ListNode<Node<Stats,shared_ptr<Player>>>* Player::get_all_players_node() {
    return all_players_node;
}


bool Player::is_goalkeeper() const {
    return goalkeeper;
}

void Player::set_games_not_played(int games) {
    games_not_played = games;
}

void Player::set_games_played(int games) {
    this->games_played = games;
}

void Player::set_all_players_node(ListNode<Node<Stats,shared_ptr<Player>>>* node) {
    all_players_node = node;
}

shared_ptr<Team>& Player::get_team() {
    return team;
}