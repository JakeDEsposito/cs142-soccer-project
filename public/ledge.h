#include <map>
#include <vector>
#include <algorithm>

#include <fstream>
#include <iostream>

#include "ledgefilter.h"
#include "player.h"

class Ledge
{
public:
    Ledge();
    
    void addPlayer(Player player);
    void removePlayer(Player player);
    void removePlayer(std::string player);
    void editPlayer(Player player);

    std::vector<Player> search(LedgeFilter filter);

    std::vector<Player> allPlayers();

    void save(std::string filename);
    std::string load(std::string filename);

private:
    std::map<std::string, Player> ledgeMap;

    std::map<std::vector<LedgeFilter::Filter>, std::vector<Player> > filterPlayerVectorMap;
};