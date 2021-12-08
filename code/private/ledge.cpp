#include "ledge.h"

Ledge::Ledge(int ledgeYear)
{
    if(ledgeYear != -1)
        programYear = ledgeYear;
    else
        programYear = currentYear();
}

Ledge::~Ledge()
{
    for(auto i = ledgeMap.begin(); i != ledgeMap.end(); i++)
    {
        for(auto j = i->second.begin(); j != i->second.end(); j++)
        {
            auto playerPtr = &(j->second);
            delete playerPtr;
        }
        auto innerLedgeMapPtr = &(i->second);
        delete innerLedgeMapPtr;
    }
    auto ledgeMapPtr = &ledgeMap;
    delete ledgeMapPtr;

    auto programYearPtr = &programYear;
    delete programYearPtr;
}

void Ledge::addPlayer(Player player)
{
    //ledgeMap[player.getLedgeMapKey()] = player;
    ledgeMap[player["ln"]][player["fn"]] = player;
}

void Ledge::removePlayer(Player player)
{
    //ledgeMap.erase(player.getLedgeMapKey());
    ledgeMap[player["ln"]].erase(player["fn"]);
}

void Ledge::removePlayer(std::string lname, std::string fname)
{
    //ledgeMap.erase(player);
    ledgeMap[lname].erase(fname);
}

void Ledge::editPlayer(Player player)
{
    //ledgeMap[player.getLedgeMapKey()] = player;
    ledgeMap[player["ln"]][player["fn"]] = player;
}

std::vector<Player> Ledge::search(std::string fname, std::string lname, std::string keyword, int birth_year, int category, int registration)
{
    std::vector<Player> result = allPlayers();

    if(lname != "")
    {
        std::vector<Player> insideVector;
        for(auto i = ledgeMap.begin(); i != ledgeMap.end(); i++)
            if(i->first == lname)
                for(auto j = i->second.begin(); j != i->second.end(); j++)
                    insideVector.push_back(j->second);
        result = insideVector;
    }
    if(fname != "")
    {
        std::vector<Player> insideVector;
        for(auto i = result.begin(); i != result.end(); i++)
            if((*i)["fn"] == fname)
                insideVector.push_back(*i);
        result = insideVector;
    }
    if(keyword != "")
    {
        std::vector<Player> insideVector;
        for(auto i = result.begin(); i != result.end(); i++)
            if(((*i)["fn"] + (*i)["ln"]).find(keyword) != std::string::npos)
                insideVector.push_back(*i);
        result = insideVector;
    }
    if(birth_year != 0)
    {
        std::vector<Player> insideVector;
        for(auto i = result.begin(); i != result.end(); i++)
            if((*i).getYOB() == birth_year)
                insideVector.push_back(*i);
        result = insideVector;
    }
    if(category != 0)
    {
        std::vector<Player> insideVector;
        for(auto i = result.begin(); i != result.end(); i++)
            if((*i).getCategory() == category)
                insideVector.push_back(*i);
        result = insideVector;
    }
    if(registration == 0 || registration == 1)
    {
        std::vector<Player> insideVector;
        for(auto i = result.begin(); i != result.end(); i++)
            if((*i).getRegistration() == registration)
                insideVector.push_back(*i);
        result = insideVector;
    }
    return result;
}

std::vector<Player> Ledge::allPlayers()
{
    std::vector<Player> result;
    for(auto i = ledgeMap.begin(); i != ledgeMap.end(); i++)
        for(auto j = i->second.begin(); j != i->second.end(); j++)
            result.push_back(j->second);
    return result;
}

void Ledge::save(std::string filename)
{
    std::ofstream file(filename);
    std::vector<Player> players = allPlayers();

    file << Ledge::programYear;
    file << std::endl;

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

        std::string temp;
        file >> temp;
        Ledge::programYear = std::stoi(temp);

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