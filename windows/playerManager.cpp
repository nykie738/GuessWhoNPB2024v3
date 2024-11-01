#include "PlayerManager.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

PlayerManager::PlayerManager() : rng(std::random_device{}()) {}

void PlayerManager::loadPlayers(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Unable to open player data file: " + filename);
    }

    players.clear();
    teamPlayerIndices.clear();
    pValueIndices.clear();
    nameIndices.clear();

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string name, team, pValue, imagePath;

        if (std::getline(iss, name, ',') &&
            std::getline(iss, team, ',') &&
            std::getline(iss, pValue, ',') &&
            std::getline(iss, imagePath))
        {
            players.emplace_back(name, team, pValue, imagePath);
            nameIndices[name].push_back(players.size() - 1);
            teamPlayerIndices[team].push_back(players.size() - 1);
            pValueIndices[pValue].push_back(players.size() - 1);
        }
    }

    if (players.empty())
    {
        throw std::runtime_error("No players loaded from file: " + filename);
    }
}

void PlayerManager::removePlayers(const std::string& playername)
{
    // Find all player indices that match the given name
    auto it = nameIndices.find(playername);
    if (it == nameIndices.end())
    {
        throw std::runtime_error("Player with name " + playername + " not found");
    }

    // Gather the indices to remove
    std::vector<size_t> indicesToRemove = it->second;

    // Remove players from the main players vector, starting from the end to avoid invalidating indices
    for (auto rit = indicesToRemove.rbegin(); rit != indicesToRemove.rend(); ++rit)
    {
        size_t index = *rit;

        // Remove the player from the main players vector
        players.erase(players.begin() + index);
    }

    // Clear the indices (they are no longer valid)
    nameIndices.clear();
    teamPlayerIndices.clear();
    pValueIndices.clear();

    // Rebuild the indices
    for (size_t i = 0; i < players.size(); ++i)
    {
        const std::string& name = players[i].getName();
        const std::string& team = players[i].getTeam();
        const std::string& pValue = players[i].getpValue();

        nameIndices[name].push_back(i);
        teamPlayerIndices[team].push_back(i);
        pValueIndices[pValue].push_back(i);
    }
}

const Player& PlayerManager::getRandomPlayer()
{
    if (players.empty())
    {
        throw std::runtime_error("No players loaded");
    }
    std::uniform_int_distribution<> dist(0, players.size() - 1);
    return players[dist(rng)];
}

const Player& PlayerManager::getRandomPlayerByTeam(const std::string& team, int pValue)
{
    auto it2 = teamPlayerIndices.find(team);
    if (it2 == teamPlayerIndices.end() || it2->second.empty())
    {
        throw std::runtime_error("No players found for team: " + team);
    }

    std::vector<int> matchingPlayers;
    for (int index : it2->second)
    {
        if (players[index].getpValue() == std::to_string(pValue))
        {
            matchingPlayers.push_back(index);
        }
    }

    if (matchingPlayers.empty())
    {
        throw std::runtime_error("Either team" + team + "N/A or player does not have picture no." + std::to_string(pValue));
    }
    std::uniform_int_distribution<> dist(0, matchingPlayers.size() - 1);
    return players[matchingPlayers[dist(rng)]];
}

const Player& PlayerManager::getNextImage(const std::string& name, int pValue)
{
    auto it3 = nameIndices.find(name);

    int nextImage = -727;
    for (int index : it3->second)
    {
        if (players[index].getpValue() == std::to_string(pValue))
        {
            nextImage = index;
        }
    }

    if (nextImage == -727)
    {
        throw std::runtime_error("The player does not have a picture number: " + std::to_string(pValue));
    }
    return players[nextImage];
}

std::vector<std::string> PlayerManager::getTeams() const
{
    std::vector<std::string> teams;
    teams.reserve(teamPlayerIndices.size());
    for (const auto& pair : teamPlayerIndices)
    {
        teams.push_back(pair.first);
    }
    return teams;
}