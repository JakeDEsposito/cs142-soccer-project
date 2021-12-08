#include "ledge.h"

Ledge::Ledge(int ledgeYear)
{
    lastLedgeMapSize = 0;
    if(ledgeYear != -1)
        programYear = ledgeYear;
    else
        programYear = currentYear();
}

void Ledge::addPlayer(Player player)
{
    ledgeMap[player.getLedgeMapKey()] = player;
}

void Ledge::removePlayer(Player player)
{
    ledgeMap.erase(player.getLedgeMapKey());
}

void Ledge::removePlayer(std::string player)
{
    ledgeMap.erase(player);
}

void Ledge::editPlayer(Player player)
{
    ledgeMap[player.getLedgeMapKey()] = player;
}

std::vector<Player> Ledge::search(LedgeFilter filter)
{
    std::vector<LedgeFilter::Filter> filters = filter.getCurrentFiltersInUse();

    if(filterPlayerVectorMap.find(filters) == filterPlayerVectorMap.end() || lastLedgeMapSize != ledgeMap.size())
    {
        lastLedgeMapSize = ledgeMap.size();
        
        std::vector<Player> result;

        if(filters.size() > 0)
            for(auto i = ledgeMap.begin(); i != ledgeMap.end(); i++)
            {
                if(filter[LedgeFilter::Filter::birth_year] && i->second.getYOB() == filter[LedgeFilter::Filter::birth_year])
                    result.push_back(i->second);

                if(filter[LedgeFilter::Filter::category] && i->second.getCategory() == filter[LedgeFilter::Filter::category])
                    result.push_back(i->second);

                if(filter[LedgeFilter::Filter::registration] && i->second.getRegistration() == filter[LedgeFilter::Filter::registration])
                    result.push_back(i->second);
            }
        else
            for(auto i = ledgeMap.begin(); i != ledgeMap.end(); i++)
                result.push_back(i->second);

        filterPlayerVectorMap[filters] = result;
        return result;
    }
    else
    {
        return filterPlayerVectorMap[filters];
    }
}

std::vector<Player> Ledge::allPlayers()
{
    return search(LedgeFilter());
}

void Ledge::save(std::string filename)
{
    std::ofstream file(filename);
    std::vector<Player> players = allPlayers();

    for(Player p : players)
    {
        file << p.save();
        file << std::endl;
    }

    file.close();
}

int Ledge::load(std::string filename)
{
    try
    {
        std::ifstream file(filename);

        while(!file.eof())
        {
            std::string data;
            file >> data;
            Player newPlayer(data);
            addPlayer(newPlayer);
        }
        file.close();
    }
    catch(const std::exception& e)
    {
        return 1;
    }
    return 0;
}

//https://stackoverflow.com/questions/58151350/more-elegant-way-to-get-the-current-year-in-c
int currentYear()
{
    std::time_t t = std::time(nullptr);
    std::tm *const pTInfo = std::localtime(&t);
    return 1900 + pTInfo->tm_year;
}
