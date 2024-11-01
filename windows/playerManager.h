#pragma once
#include "Player.h"
#include <vector>
#include <random>
#include <unordered_map>

class PlayerManager
{
public:
    PlayerManager();
    void loadPlayers(const std::string& filename);
    void removePlayers(const std::string& playername);
    const Player& getRandomPlayer();
    const Player& getRandomPlayerByTeam(const std::string& team, int pValue);
    const Player& getNextImage(const std::string& name, int pValue);
    const Player& getSamePlayer(const std::string& name);
    size_t getPlayerCount() const { return players.size(); }
    std::vector<std::string> getTeams() const;
    std::vector<std::string> getpValue() const;

private:
    std::vector<Player> players;
    std::unordered_map<std::string, std::vector<size_t>> teamPlayerIndices;
    std::unordered_map<std::string, std::vector<size_t>> nameIndices;
    std::unordered_map<std::string, std::vector<size_t>> pValueIndices;
    std::mt19937 rng;
};
