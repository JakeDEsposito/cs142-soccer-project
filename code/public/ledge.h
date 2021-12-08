#include <map>
#include <vector>
#include <algorithm>

#include <fstream>
#include <iostream>

#include "player.h"

class Ledge
{
public:
    //Default constructor that can take in an optional ledge year (in none is provided the program will detect a year)
    Ledge(int ledgeYear = -1);
    
    // Adds a player to the ledge.
    void addPlayer(Player player);

    // Removes a player from the ledge based of the player object.
    void removePlayer(Player player);

    // Removes a player from the ledge based of the players ledge key.
    void removePlayer(std::string lname, std::string fname);

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
    // Defaults for strings are "" and int are 0
    std::vector<Player> search(std::string fname, std::string lname, std::string keyword, int birth_year, int category, int registration);

    // Returns all players in ledge.
    std::vector<Player> allPlayers();

    // Saves the ledge into a file of name filename.
    void save(std::string filename);

    // Loads the ledge from a file of filename. Returns 0 for no error and 1 for error.
    int load(std::string filename);

    static int programYear;

private:
    //std::map<std::string, Player> ledgeMap;

    std::map<std::string, std::map<std::string, Player> > ledgeMap;
};