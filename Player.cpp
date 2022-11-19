//
// Created by Yotam on 19/11/2022.
//

#include "Player.h"

Player::Player(player_id, team_id, games_played, goals, cards, goalkeeper):
    player_id(player_id),
    team_id(team_id),
    games_played(games_played),
    goals(goals),
    cards(cards),
    goalkeeper(goalkeeper)
{
    his_team = nullptr;
    games_team_played_without = 0;
    closest_player_id = -1;
    closest_player_goals = -1;
    closest_player_cards = -1;
}


int Player::get_games_played() {
    return games_played + his_team->get_games_played() - games_team_played_without;
}