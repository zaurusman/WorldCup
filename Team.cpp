//
// Created by Yotam on 19/11/2022.
//

#include "Team.h"

Team::Team(int team_id, int points):
        id(team_id),
        points(points),
        players()//TODO: goalkeeper = false. strength = 0;
{}

bool Team::is_empty() {
    return get_players_count() == 0;
}

int Team::get_id() {
    return id;
}

int Team::get_team_power() {
    return points + get_players_count() * (total_goals - total_cards);
}

int Team::get_games_played() {
    return games_played;
}

void Team::add_games_played(int games){
    games_played +=games;
}

int Team::get_players_count() {
    return players.get_nodes_count();
}

int Team::get_strength() { //TODO: what is it for?
    return points + total_goals - total_cards;
}

int Team::get_points() {
    return points;
}

shared_ptr<Player>& Team::get_top_scorer() {
    return top_scorer;
}

bool Team::goalkeeper(){
    return has_goalkeeper;
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

AVLTree<Stats, shared_ptr<Player>>& Team::get_players_score() {
    return players_score;
}

//void calc_strength(shared_ptr<Node<int,shared_ptr<Player>>>& root,int *strength){
//    if(!root) {
//        return;
//    }
//    *strength = (root->info->get_goals()-root->info->get_cards());
//    calc_strength(root->left,strength);
//    calc_strength(root->right,strength);
//}

//void Team::update_strength() {
//    calc_strength(players.get_root(),&points);
//}
//

void Team::add_points(int points) {
    points+=points;
}

