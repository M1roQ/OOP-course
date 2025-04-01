#include "GameOfLife.hpp"


GameState::GameState()
    : game_version("1.0"),
      universe_name("Default"),
      size(0),
      count_of_iterations(0),
      B_conditions(),
      S_conditions(),
      field() {}


GameState::~GameState() {}


std::string GameState::get_game_version() const
{
    return game_version;
}

std::string GameState::get_universe_name() const
{
    return universe_name;
}

int GameState::get_size() const
{
    return size;
}

int GameState::get_count_of_iterations() const
{
    return count_of_iterations;
}

std::set<int> GameState::get_B_conditions() const
{
    return B_conditions;
}

std::set<int> GameState::get_S_conditions() const
{
    return S_conditions;
}

std::vector<std::vector<bool> > GameState::get_field() const
{
    return field;
}


void GameState::set_game_version(const std::string &version)
{
    game_version = version;
}

void GameState::set_universe_name(const std::string &name)
{
    universe_name = name;
}

void GameState::set_size(int new_size)
{
    size = new_size;
}

void GameState::set_count_of_iterations(int iterations)
{
    count_of_iterations = iterations;
}

void GameState::set_B_conditions(const std::set<int> &conditions)
{
    B_conditions = conditions;
}

void GameState::set_S_conditions(const std::set<int> &conditions)
{
    S_conditions = conditions;
}

void GameState::set_field(const std::vector<std::vector<bool> > &new_field)
{
    field = new_field;
}
