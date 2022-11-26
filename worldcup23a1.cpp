

#include "worldcup23a1.h"
#include "AVLTree.h"
#include "LinkedList.h"


world_cup_t::world_cup_t() : teams(AVLTree<int, shared_ptr<Team>>(int(), shared_ptr<Team>())) {}

world_cup_t::~world_cup_t() {}//are all necessary destructors being called?

StatusType world_cup_t::add_team(int teamId, int points) {
    if (teamId <= 0 || points < 0)
        return StatusType::INVALID_INPUT;
    try {
        shared_ptr<Team> new_team(new Team(teamId, points));
        teams.insert(teamId, new_team);
        valid_teams.insert(teamId, new_team);
    } catch (const KeyAlreadyExists &e) {
        return StatusType::FAILURE;
    } catch (const std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId) {
    if (teamId <= 0)
        return StatusType::INVALID_INPUT;

    try {
        if (teams.find(teamId)->info->get_players().get_tree_height() != 0) {//PlayersTree need to be added to team.
            teams.remove(teamId);
            return StatusType::SUCCESS;
        }
    } catch (const KeyDoesNotExist &e) {
        return StatusType::FAILURE;
    } catch (const std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::FAILURE;
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper) {
    if (playerId <= 0 || teamId <= 0 || gamesPlayed < 0 || goals < 0 || cards < 0 || gamesPlayed == 0 && (goals > 0 || cards > 0)) {
        return StatusType::INVALID_INPUT;
    }

    if (all_players.does_exist(playerId) || !teams.does_exist(teamId)) {
        return StatusType::FAILURE;
    }

    shared_ptr<Team> his_team = teams.find(teamId)->info;
    shared_ptr<Player> to_add = make_shared<Player>(playerId, his_team, gamesPlayed, goals, cards, goalKeeper);
    his_team->get_players().insert(playerId, to_add);
    if (his_team->get_number_of_players() >= VALID_SIZE && his_team->goalkeeper() &&
        !valid_teams.find(teamId)) {
        valid_teams.insert(teamId, his_team);
    }
    all_players.insert(playerId, to_add);
    //TODO: add next and prev check.

    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId) {
    if (playerId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if (!all_players.does_exist(playerId)) {
        return StatusType::FAILURE;
    }
    try {
        all_players.find(playerId)->info->get_team()->get_players().remove(playerId);
        all_players.remove(playerId);
        //TODO: update the other trees as necessary.

    }
    catch (const KeyDoesNotExist &e) {
        return StatusType::FAILURE;
    } catch (const std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                            int scoredGoals, int cardsReceived) {
    if (playerId <= 0 || gamesPlayed < 0 || scoredGoals < 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        Player &to_update = *all_players.find(playerId)->info;
        to_update.set_games_played(gamesPlayed);
        to_update.set_goals(scoredGoals);
        to_update.set_cards(cardsReceived);
    } catch (KeyDoesNotExist &e) {
        return StatusType::FAILURE;
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2) {

    // TODO: Your code goes here
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId) {
    // TODO: Your code goes here
    return 22;
}

output_t<int> world_cup_t::get_team_points(int teamId) {
    // TODO: Your code goes here
    return 30003;
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId) {
    // TODO: Your code goes here
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId) {
    // TODO: Your code goes here
    return 2008;
}

output_t<int> world_cup_t::get_all_players_count(int teamId) {
    if (teamId < 0) {
        return all_players.get_number_of_nodes();
    } else if (teamId > 0) {
        try {
            shared_ptr<Team> team_obj = teams.find(teamId)->info;
            return team_obj->get_players().get_number_of_nodes();
        } catch (const KeyDoesNotExist &e) {
            return StatusType::FAILURE;
        }
    } else {
        output_t<int> err(StatusType::INVALID_INPUT);
        return err;
    }
}

StatusType world_cup_t::get_all_players(int teamId, int *const output) {
    // TODO: Your code goes here
    output[0] = 4001;
    output[1] = 4002;
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId) {
    // TODO: Your code goes here
    return 1006;
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId) {
    // TODO: Your code goes here
    return 2;
}

