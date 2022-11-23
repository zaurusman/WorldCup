//
// Created by Yotam on 19/11/2022.
//

#include "Team.h"

Team::Team(int team_id, int points):
        team_id(team_id),
        points(points),
        players()
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

AVLTree<int, Player> Team::get_players() {
    return players;
}