//
// Created by Yotam on 19/11/2022.
//

#include "Team.h"

Team::Team(int team_id, int points):
        team_id(team_id),
        points(points),
        players()//TODO: goalkeeper = false. strength = 0;
{}

bool Team::is_empty() {
    return number_of_players == 0;
}

int Team::get_team_power() {
    return points + number_of_players * (total_goals - total_cards);
}

int Team::get_games_played() {
    return games_played;
}

void Team::add_games_played(int games){
    games_played +=games;
}

int Team::get_number_of_players() {
    return number_of_players;
}

int Team::get_strength() {
    return strength;
}

bool Team::goalkeeper(){
    return has_goalkeeper;
}

AVLTree<int, shared_ptr<Player>>& Team::get_players() {
    return players;
}

AVLTree<Stats, shared_ptr<Player>>& Team::get_players_score() {
    return players_score;
}

int calc_strength(shared_ptr<Node<int,shared_ptr<Player>>>& root,int *strength){
    if(!root) {
        return 0;
    }
    *strength = (root->info->get_goals()-root->info->get_cards());
    calc_strength(root->left,strength);
    calc_strength(root->right,strength);
}
void Team::update_strength() {
    calc_strength(players.get_root(),&points);
}

void Team::set_points(int points) {
    points+=points;
}

