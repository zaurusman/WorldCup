//
// Created by Yotam on 19/11/2022.
//

#include "Team.h"

Team::Team(int team_id, int points):
        id(team_id),
        points(points),
        goalkeepers(0),
        total_goals(0),
        total_cards(0),
        games_played(0),
        players(),
        players_score(),
        top_scorer()
{}

bool Team::is_empty() {
    return get_players_count() == 0;
}

int Team::get_id() const {
    return id;
}

int Team::get_games_played() const {
    return games_played;
}

void Team::add_games_played(int games){
    games_played +=games;
}

int Team::get_players_count() {
    return players.get_node_count();
}

int Team::get_strength() const {
    return points + total_goals - total_cards;
}

int Team::get_points() const {
    return points;
}

void Team::add_goalkeeper(int goalkeeper) {
    goalkeepers += goalkeeper;
}

bool Team::has_goalkeeper() const {
    return goalkeepers > 0;
}

int Team::get_goalkeepers() const {
    return goalkeepers;
}

int Team::get_goals() const {
    return total_goals;
}

int Team::get_cards() const {
    return total_cards;
}

void Team::add_total_goals(int goals) {
    total_goals += goals;
}

void Team::add_total_cards(int cards) {
    total_cards += cards;
}

AVLTree<int, shared_ptr<Player>>& Team::get_players() {
    return players;
}

shared_ptr<Node<Stats,shared_ptr<Player>>> Team::get_top_scorer() {
    return top_scorer;
}

void Team::set_top_scorer(shared_ptr<Node<Stats,shared_ptr<Player>>> new_top_scorer) {
    this->top_scorer = new_top_scorer;
}

void Team::set_players(AVLTree<int,shared_ptr<Player>>& new_players) {
    this->players = new_players;
}
void Team::set_players_score(AVLTree<Stats,shared_ptr<Player>>& new_players_score) {
    this->players_score = new_players_score;
}

AVLTree<Stats, shared_ptr<Player>>& Team::get_players_score() {
    return players_score;
}

void Team::add_points(int new_points) {
    this->points+=new_points;
}

void Team::empty_players() {
    while(this->get_players().get_root())
    {
        this->get_players().remove(this->get_players().get_root()->key);
    }
    while(this->get_players_score().get_root())
    {
        this->get_players_score().remove(this->get_players_score().get_root()->key);
    }
}
