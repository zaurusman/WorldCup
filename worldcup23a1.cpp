

#include "worldcup23a1.h"
#include "AVLTree.h"
#include "LinkedList.h"


world_cup_t::world_cup_t() : teams(AVLTree<int, shared_ptr<Team>>()) {}

world_cup_t::~world_cup_t() = default;

StatusType world_cup_t::add_team(int team_id, int points) {
    if (team_id <= 0 || points < 0)
        return StatusType::INVALID_INPUT;
    try {
        shared_ptr<Team> new_team(new Team(team_id, points));
        teams.insert(team_id, new_team);
        // should not add to valid teams when team has no players
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
    Stats stats_to_add(*to_add);
    int added_goals = to_add->get_goals();
    int added_cards = to_add->get_cards();

    his_team->get_players().insert(playerId, to_add);
    his_team->get_players_score().insert(stats_to_add, to_add);

    all_players.insert(playerId, to_add);
    all_players_score.insert(stats_to_add, to_add);

    if (goalKeeper) {
        his_team->add_goalkeeper(1);
    }
    if (his_team->get_players_count() >= VALID_SIZE && his_team->has_goalkeeper() &&
        !valid_teams.does_exist(teamId)) {
        valid_teams.insert(teamId, his_team);
    }

    his_team->add_total_goals(added_goals);
    his_team->add_total_cards(added_cards);


    //TODO: add next and prev check for closest players, and top_scorer

    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId) {//TODO: add check for top_scorer
    if (playerId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if (!all_players.does_exist(playerId)) {
        return StatusType::FAILURE;
    }
    // TODO: Q: can we remove try and catch (failure caught on above if, bad_alloc only happens in new)
    try {
        shared_ptr<Player> player_to_remove = all_players.find(playerId)->info;
        shared_ptr<Team> his_team = player_to_remove->get_team();
        Stats stats_to_remove(*player_to_remove);
        int removed_goals = player_to_remove->get_goals();
        int removed_cards = player_to_remove->get_cards();
        bool goalkeeper = player_to_remove->is_goalkeeper();

        all_players.remove(playerId);
        all_players_score.remove(stats_to_remove);
        his_team->get_players().remove(playerId);
        his_team->get_players_score().remove(stats_to_remove);
        if ((his_team->get_players_count() < VALID_SIZE || !his_team->has_goalkeeper()) &&
            valid_teams.does_exist(his_team->get_id())) {
            valid_teams.remove(his_team->get_id());
        }

        his_team->add_total_goals(-1 * removed_goals);
        his_team->add_total_cards(-1 * removed_cards);
        if (goalkeeper) {
            his_team->add_goalkeeper(-1);
        }
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
    if (playerId <= 0 || gamesPlayed < 0 || scoredGoals < 0 || cardsReceived < 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        shared_ptr<Player> to_update = all_players.find(playerId)->info;
        to_update->add_games_played(gamesPlayed);
        to_update->add_goals(scoredGoals);
        to_update->add_cards(cardsReceived);
        to_update->get_team()->add_total_goals(scoredGoals);
        to_update->get_team()->add_total_cards(cardsReceived);
        //TODO:update both trees in team and world_cup_t , check top_scorer
    } catch(KeyDoesNotExist& e) {
        return StatusType::FAILURE;
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
    if(teamId1<=0||teamId2<=0||teamId1==teamId2) {
        return StatusType::INVALID_INPUT;
    }

    if(!valid_teams.does_exist(teamId1)||!valid_teams.does_exist(teamId2)) {
        return StatusType::FAILURE;
    }

    shared_ptr<Team> team1 = valid_teams.find(teamId1)->info;
    shared_ptr<Team> team2 = valid_teams.find(teamId2)->info;
    if(team1->get_strength() > team2->get_strength()){
        team1->add_points(WINNER_POINTS);
    }else if(team1->get_strength() < team2->get_strength()){
        team2->add_points(WINNER_POINTS);
    }else {//Draw
        team1->add_points(DRAW_POINTS);
        team2->add_points(DRAW_POINTS);
    }
    team1->add_games_played(1);
    team2->add_games_played(1);
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId) {
    if(playerId>=0) {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    else if(!all_players.does_exist(playerId)) {
        return output_t<int>(StatusType::FAILURE);
    }
    return output_t<int>(all_players.find(playerId)->info->get_games_played());
    return 22;
}

output_t<int> world_cup_t::get_team_points(int teamId) {
    if(teamId>=0) {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    if(!teams.does_exist(teamId)) {
        return output_t<int>(StatusType::FAILURE);
    }
    return output_t<int>(teams.find(teamId)->info->get_points());
    return 30003;
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId) {
    if(teamId1<=0||teamId2<=0||newTeamId<=0||teamId1==teamId2) {
        return StatusType::INVALID_INPUT;
    }
    else if(teams.does_exist(teamId1)&&teams.does_exist(teamId2)) {
        if(teams.does_exist(newTeamId)&&(teamId1!=newTeamId&&teamId2!=newTeamId)) {
            return StatusType::FAILURE;
        }
        shared_ptr<Team> newTeam = make_shared<Team>(newTeamId,(teams.find(teamId1)->info->get_points() + teams.find(teamId2)->info->get_points()));
        teams.insert(newTeamId,newTeam);


        //TODO: transfer players to the new group, delete old groups, update power and other stats.
        return StatusType::SUCCESS;
    }
    else {
        return StatusType::FAILURE;
    }
}

output_t<int> world_cup_t::get_top_scorer(int teamId) {
    if(teamId==0) {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    else if(teamId>0&&(!teams.does_exist(teamId)||teams.find(teamId)->info->get_players_count()==0)||teamId<0&&all_players.get_nodes_count()==0) {
        return output_t<int>(StatusType::FAILURE);
    }
    else if(teamId<0) {
        return output_t<int>(top_scorer->get_id());

    }
    else {
        return output_t<int>(teams.find(teamId)->info->get_top_scorer()->get_id());
    }
    return 2008;
}

output_t<int> world_cup_t::get_all_players_count(int teamId) {
    if (teamId < 0) {
        return all_players.get_nodes_count();
    } else if (teamId > 0) {
        try {
            shared_ptr<Team> team_obj = teams.find(teamId)->info;
            return team_obj->get_players().get_nodes_count();
        } catch (const KeyDoesNotExist &e) {
            return StatusType::FAILURE;
        }
    } else {
        return output_t<int>(StatusType::INVALID_INPUT);
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

