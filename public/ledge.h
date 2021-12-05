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
    //Default constructor
    Ledge();
    
    // Adds a player to the ledge.
    void addPlayer(Player player);

    // Removes a player from the ledge based of the player object.
    void removePlayer(Player player);

    // Removes a player from the ledge based of the players ledge key.
    void removePlayer(std::string player);

    /*
        Params:
            player
        Function:
            sets the value of the player in the map to the player that is passed into the function.
        Example:
            Player p - fname = "mark"; lname = "park"

            editPlayer(p) ->
                p -> ledge key -> mark_park
            
            ledgeMap["mark_park"] = p;
    */
    void editPlayer(Player player);

    // Returns a vector of players in ledge based on the filter set.
    std::vector<Player> search(LedgeFilter filter);

    // Returns all players in ledge.
    std::vector<Player> allPlayers();

    // Saves the ledge into a file of name filename.
    void save(std::string filename);

    // Loads the ledge from a file of filename.
    std::string load(std::string filename);

private:
    std::map<std::string, Player> ledgeMap;

    std::map<std::vector<LedgeFilter::Filter>, std::vector<Player> > filterPlayerVectorMap;
};