// Player header file
// Written by Jake D'Esposito in 2021

#include <string>
#include <ctime>

#ifndef PlayerClass
#define PlayerClass

/*
#ifndef LedgeClass
#include "./ledge.h"
#endif
*/

class Player
{
 public:
  // sets the fn to fname, ln to lname, yob to birthYear, and rs to
  // regStat. Also calculates the category based on the birthYear and
  // current year of the computer
  Player(std::string fn, std::string ln, int yob, bool rs, const int year);
  Player () {};

  // sets the fn to fname, ln to lname, yob to birthYear, cat to
  // category, and rs to regStat.
  Player(std::string fn, std::string ln, int yob, int cat, bool rs);

  // takes in a data string and sets all nessisarry variables.
  Player(std::string data);

  ~Player();

  // returns fname [space] lname.
  std::string getName();

  // returns birthYear.
  int getYOB();

  // returns category.
  int getCategory();

  // returns "U" + category.
  std::string getCategoryAsString();

  // returns regStat.
  bool getRegistration();

  // sets regStat to the value of rs.
  void setRegistration(bool rs);

  // Params: query
  /* returns a string based on the query.
  if query then string
    if fn then fname
    if ln then lname
    if by then birthYear
    if ca then category
    if rs then regStat
  */
  std::string operator [] (const std::string & query);

  // Returns a string that can be saved and later reloaded into a
  // player
  std::string save();

  // Loads a data string into the nessisary variables
  void load(std::string data);

 private:
  int calculateCategory(const int year);

  std::string fname;
  std::string lname;
  int birthYear;
  int category;
  bool regStat;
};
#endif
