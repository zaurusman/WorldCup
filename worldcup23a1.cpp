

#include "worldcup23a1.h"
#include "AVLTree.h"
#include "LinkedList.h"


world_cup_t::world_cup_t() = default;

world_cup_t::~world_cup_t() = default;

StatusType world_cup_t::add_team(int team_id, int points) {
    if (team_id <= 0 || points < 0)
        return StatusType::INVALID_INPUT;
    try {
        shared_ptr<Team> new_team = make_shared<Team>(team_id, points);
        teams.insert(team_id, new_team);
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
        if (teams.find(teamId)->info->get_players().get_node_count() == 0 && teams.find(teamId)->info->get_players_score().get_node_count() == 0) {
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
    if (playerId <= 0 || teamId <= 0 || gamesPlayed < 0 || goals < 0 || cards < 0 || (gamesPlayed == 0  && (goals > 0 || cards > 0))) {
        return StatusType::INVALID_INPUT;
    }

    if (all_players.does_exist(playerId) || !teams.does_exist(teamId)) {
        return StatusType::FAILURE;
    }

    try {
        shared_ptr<Team> his_team = teams.find(teamId)->info;
        add_player_to_team(gamesPlayed,goals,cards, playerId, &*his_team, goalKeeper);
        if (his_team->get_players_count() >= VALID_SIZE && his_team->has_goalkeeper() &&
            !valid_teams.does_exist(teamId)) {
            valid_teams.insert(teamId, his_team);
        }
        return StatusType::SUCCESS;
    }catch(std::bad_alloc &e){
        return StatusType::ALLOCATION_ERROR;
    }
}

void world_cup_t::add_player_to_team(int gamesPlayed,int goals, int cards,int playerId,Team* his_team, bool goalKeeper) {
    shared_ptr<Player> to_add = make_shared<Player>(playerId, his_team, gamesPlayed, goals, cards, goalKeeper);
    Stats stats_to_add(*to_add);
    int added_goals = to_add->get_goals();
    int added_cards = to_add->get_cards();
    int games_not_played = his_team->get_games_played();
    to_add->set_games_not_played(games_not_played);

    his_team->get_players().insert(playerId, to_add);
    shared_ptr<Node<Stats,shared_ptr<Player>>> team_parent;
    his_team->get_players_score().insert_p(stats_to_add, to_add,team_parent);

    all_players.insert(playerId, to_add);
    shared_ptr<Node<Stats,shared_ptr<Player>>> all_players_parent;
    all_players_score.insert_p(stats_to_add, to_add,all_players_parent);

    if (goalKeeper) {
        his_team->add_goalkeeper(1);
    }

    his_team->add_total_goals(added_goals);
    his_team->add_total_cards(added_cards);

    if (all_players_parent) {
        if (all_players_parent->key > stats_to_add) {
            to_add->set_all_players_node(players_list.insert_before(all_players_parent->info->get_all_players_node(),  *all_players_score.find(stats_to_add)));
        } else {
            to_add->set_all_players_node(players_list.insert_after(all_players_parent->info->get_all_players_node(),  *all_players_score.find(stats_to_add)));
        }
    } else {
        to_add->set_all_players_node(players_list.insert_before(nullptr, *all_players_score.find(stats_to_add)));
    }

    his_team->set_top_scorer(his_team->get_players_score().get_max());
}

StatusType world_cup_t::remove_player(int playerId) {
    if (playerId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if (!all_players.does_exist(playerId)) {
        return StatusType::FAILURE;
    }
    try {
        shared_ptr<Player> player_to_remove = all_players.find(playerId)->info;
        Team* his_team = player_to_remove->get_team();
        remove_player_aux(player_to_remove,his_team, playerId);
        if ((his_team->get_players_count() < VALID_SIZE || !his_team->has_goalkeeper()) && valid_teams.does_exist(his_team->get_id())) {
            valid_teams.remove(his_team->get_id());
        }
    }
    catch (const KeyDoesNotExist &e) {
        return StatusType::FAILURE;
    } catch (const std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

void world_cup_t::remove_player_aux(shared_ptr<Player>& player_to_remove,Team* his_team,int playerId) {
    Stats stats_to_remove(*player_to_remove);
    int removed_goals = player_to_remove->get_goals();
    int removed_cards = player_to_remove->get_cards();
    bool goalkeeper = player_to_remove->is_goalkeeper();

    all_players.remove(playerId);
    all_players_score.remove(stats_to_remove);
    his_team->get_players().remove(playerId);
    his_team->get_players_score().remove(stats_to_remove);

    players_list.remove_node(player_to_remove->get_all_players_node());
    his_team->set_top_scorer(his_team->get_players_score().get_max());

    his_team->add_total_goals(-1 * removed_goals);
    his_team->add_total_cards(-1 * removed_cards);
    if (goalkeeper) {
        his_team->add_goalkeeper(-1);
    }
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                            int scoredGoals, int cardsReceived) {
    if (playerId <= 0 || gamesPlayed < 0 || scoredGoals < 0 || cardsReceived < 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        shared_ptr<Player> to_update = all_players.find(playerId)->info;
        remove_player_aux(to_update,to_update->get_team(),to_update->get_id());
        to_update->add_games_played(gamesPlayed);
        to_update->add_goals(scoredGoals);
        to_update->add_cards(cardsReceived);
        add_player_to_team(to_update->get_games_played(),to_update->get_goals(),to_update->get_cards(),to_update->get_id(),to_update->get_team(),to_update->is_goalkeeper());
        to_update->get_team()->add_total_goals(scoredGoals);
        to_update->get_team()->add_total_cards(cardsReceived);

    } catch (KeyDoesNotExist &e) {
        return StatusType::FAILURE;
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2) {
    if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2) {
        return StatusType::INVALID_INPUT;
    }

    if (!valid_teams.does_exist(teamId1) || !valid_teams.does_exist(teamId2)) {
        return StatusType::FAILURE;
    }

    shared_ptr<Team> team1 = valid_teams.find(teamId1)->info;
    shared_ptr<Team> team2 = valid_teams.find(teamId2)->info;
    if (team1->get_strength() > team2->get_strength()) {
        team1->add_points(WINNER_POINTS);
    } else if (team1->get_strength() < team2->get_strength()) {
        team2->add_points(WINNER_POINTS);
    } else {//Draw
        team1->add_points(DRAW_POINTS);
        team2->add_points(DRAW_POINTS);
    }
    team1->add_games_played(1);
    team2->add_games_played(1);
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId) {
    if (playerId <= 0) {
        return {StatusType::INVALID_INPUT};
    } else if (!all_players.does_exist(playerId)) {
        return {StatusType::FAILURE};
    }
    return all_players.find(playerId)->info->get_games_played();
}

output_t<int> world_cup_t::get_team_points(int teamId) {
    if (teamId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if (!teams.does_exist(teamId)) {
        return StatusType::FAILURE;
    }
    return teams.find(teamId)->info->get_points();
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId) {
    if (teamId1 <= 0 || teamId2 <= 0 || newTeamId <= 0 || teamId1 == teamId2) {
        return StatusType::INVALID_INPUT;
    }
    if (!teams.does_exist(teamId1) || !teams.does_exist(teamId2)) {
        return StatusType::FAILURE;
    }

    if (teams.does_exist(newTeamId) && (teamId1 != newTeamId && teamId2 != newTeamId)) {
        return StatusType::FAILURE;
    }

    shared_ptr<Node<int,shared_ptr<Team>>> team1 = teams.find(teamId1);
    shared_ptr<Node<int,shared_ptr<Team>>> team2 = teams.find(teamId2);
    int node_count1 = team1->info->get_players().get_node_count();
    int node_count2 = team2->info->get_players().get_node_count();
    LinkedList<Node<int,shared_ptr<Player>>> players_list1;
    LinkedList<Node<int,shared_ptr<Player>>> players_list2;
    LinkedList<Node<int,shared_ptr<Player>>> players_list_merged;
    LinkedList<Node<Stats,shared_ptr<Player>>> players_score1;
    LinkedList<Node<Stats,shared_ptr<Player>>> players_score2;
    LinkedList<Node<Stats,shared_ptr<Player>>> players_score_merged;
    LinkedList<Node<Stats,shared_ptr<Player>>> players_score_merge2;
    AVLTree<int,shared_ptr<Player>>::AVL_to_list_inorder(team1->info->get_players().get_root(), players_list1);
    AVLTree<int,shared_ptr<Player>>::AVL_to_list_inorder(team2->info->get_players().get_root(), players_list2);
    AVLTree<Stats,shared_ptr<Player>>::AVL_to_list_inorder(team1->info->get_players_score().get_root(), players_score1);
    AVLTree<Stats,shared_ptr<Player>>::AVL_to_list_inorder(team2->info->get_players_score().get_root(), players_score2);

    LinkedList<Node<int,shared_ptr<Player>>>::merge_sorted(players_list1, players_list2, players_list_merged);

    LinkedList<Node<Stats,shared_ptr<Player>>>::merge_sorted(players_score1, players_score2, players_score_merged);
    LinkedList<Node<Stats,shared_ptr<Player>>>::merge_sorted(players_score1, players_score2, players_score_merge2);

    ListNode<Node<int,shared_ptr<Player>>>* temp_player = players_list_merged.get_first();
    while (temp_player) {
        temp_player->data.info->set_games_played(temp_player->data.info->get_games_played());
        temp_player = temp_player->next;
    }

    AVLTree<int,shared_ptr<Player>> united_players = AVLTree<int,shared_ptr<Player>>::make_almost_complete_tree(node_count1 + node_count2);
    AVLTree<Stats,shared_ptr<Player>> united_players_score = AVLTree<Stats,shared_ptr<Player>>::make_almost_complete_tree(node_count1 + node_count2);

    AVLTree<int,shared_ptr<Player>>::fill_empty_tree(united_players.get_root(), players_list_merged);
    AVLTree<Stats,shared_ptr<Player>>::fill_empty_tree(united_players_score.get_root(), players_score_merged);
    team1->info->empty_players();
    team2->info->empty_players();
    shared_ptr<Team> new_team = make_shared<Team>(newTeamId, (teams.find(teamId1)->info->get_points() + teams.find(teamId2)->info->get_points()));
    remove_team(teamId1);
    remove_team(teamId2);

    new_team->set_players(united_players);
    new_team->set_players_score(united_players_score);
    teams.insert(newTeamId, new_team);
    new_team->add_goalkeeper(team1->info->get_goalkeepers() + team2->info->get_goalkeepers());
    new_team->add_total_goals(team1->info->get_goals() + team2->info->get_goals());
    new_team->add_total_cards(team1->info->get_cards() + team2->info->get_cards());
    new_team->set_top_scorer(new_team->get_players_score().get_max());

    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId) {
    if (teamId == 0) {
        return StatusType::INVALID_INPUT;
    } else if (((teamId > 0 )&& (!teams.does_exist(teamId) || teams.find(teamId)->info->get_players_count() == 0)) || ((teamId < 0) && all_players.get_node_count() == 0)) {
        return StatusType::FAILURE;
    } else if (teamId < 0) {
        return players_list.get_last()->data.key.get_id();

    } else {
        return teams.find(teamId)->info->get_top_scorer()->info->get_id();
    }

}

output_t<int> world_cup_t::get_all_players_count(int teamId) {
    if (teamId < 0) {
        return all_players.get_node_count();
    } else if (teamId > 0) {
        try {
            shared_ptr<Team> team_obj = teams.find(teamId)->info;
            return team_obj->get_players().get_node_count();
        } catch (const KeyDoesNotExist &e) {
            return StatusType::FAILURE;
        }
    } else {
        return StatusType::INVALID_INPUT;
    }
}

StatusType world_cup_t::get_all_players(int teamId, int *const output) {
    if(teamId == 0||output == nullptr) {
        return StatusType::INVALID_INPUT;
    }
    int *arr = output;
    if(teamId>0) {
        try {
            if (teams.find(teamId)->info->is_empty()) {
                return StatusType::FAILURE;
            }
            LinkedList<Node<Stats, shared_ptr<Player>>> list;
            AVLTree<Stats, shared_ptr<Player>>::AVL_to_list_inorder(teams.find(teamId)->info->get_players_score().get_root(), list);
            ListNode<Node<Stats, shared_ptr<Player>>> *node = list.get_first();
            while (node) {
                *arr = node->data.info->get_id();
                node = node->next;
                arr++;
            }

            return StatusType::SUCCESS;
        }catch(KeyDoesNotExist &e) {
            return StatusType::FAILURE;
        }
    }
    //teamId<0
    LinkedList<Node<Stats, shared_ptr<Player>>> list;
    AVLTree<Stats, shared_ptr<Player>>::AVL_to_list_inorder(all_players_score.get_root(), list);
    ListNode<Node<Stats, shared_ptr<Player>>> *node = list.get_first();
    while (node) {
        *arr = node->data.info->get_id();
        node = node->next;
        arr++;
    }

    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId) {
    if (teamId <= 0 || playerId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    if (!teams.does_exist(teamId)) {
        return StatusType::FAILURE;
    }

    shared_ptr<Team> his_team = teams.find(teamId)->info;
    if (!his_team->get_players().does_exist(playerId) || all_players.get_node_count() == 1) {
        return StatusType::FAILURE;
    }

    shared_ptr<Player> player = his_team->get_players().find(playerId)->info;
    ListNode<Node<Stats,shared_ptr<Player>>>* player_node = player->get_all_players_node();
    ListNode<Node<Stats,shared_ptr<Player>>>* next_node = player_node->next;
    ListNode<Node<Stats,shared_ptr<Player>>>* prev_node = player_node->prev;

    if (!next_node) {
        return prev_node->data.key.get_id();
    }
    if (!prev_node) {
        return next_node->data.key.get_id();
    }

    Stats player_stats = Stats(*player);
    Stats next_stats = next_node->data.key;
    Stats prev_stats = prev_node->data.key;
    if(player_stats.is_next_closer(prev_stats, next_stats)) {
        return next_stats.get_id();
    } else {
        return prev_stats.get_id();
    }
}


static bool does_first_team_win(int first_strength, int second_strength) {
    if (first_strength > second_strength) {
        return true;
    } else { // if strengths are equal, second team has a larger id
        return false;
    }
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId) {
    if (maxTeamId < 0 || minTeamId < 0 || minTeamId > maxTeamId) {
        return StatusType::INVALID_INPUT;
    }

    LinkedList<Node<int, shared_ptr<Team>>> valid_nodes;
    LinkedList<Node<int, int>> tourney;
    AVLTree<int, shared_ptr<Team>>::AVL_to_list_inorder(valid_teams.get_root(), valid_nodes);
    ListNode<Node<int, shared_ptr<Team>>>* curr_team = valid_nodes.get_first();
    ListNode<Node<int, int>>* team1;
    ListNode<Node<int, int>>* team2;

    while (curr_team && curr_team->data.info->get_id() < minTeamId) {
        curr_team = curr_team->next;
    }
    if (!curr_team || curr_team->data.info->get_id() > maxTeamId) { // no teams in given range
        return StatusType::FAILURE;
    }

    while (curr_team && curr_team->data.info->get_id() <= maxTeamId) {
        int strength = curr_team->data.info->get_strength();
        int id = curr_team->data.info->get_id();
        tourney.push_back(Node<int, int>(id, strength));
        curr_team = curr_team->next;
    }

    while (tourney.get_first()->next) {
        team1 = tourney.get_first();
        while (team1 && team1->next) {
            team2 = team1->next;
            int first_strength = team1->data.info;
            int second_strength = team2->data.info;
            if (does_first_team_win(first_strength, second_strength)) {
                team1->data.info = first_strength + second_strength + 3;
                tourney.remove_node(team2);
                team1 = team1->next;
            } else {
                team2->data.info = first_strength + second_strength + 3;
                tourney.remove_node(team1);
                team1 = team2->next;
            }
        }
    }
    return tourney.get_first()->data.key;
}

