#include <string>

class Player
{
public:
  Player();
  Player(std::string n, int yob, std::string cat, std::string rs);
  std::string getName();
  int getYOB();
  std::string getCatagory();
  std::string getRegistration();
private:
  std::string name;
  int yob;
  std::string cata;
  std::string regStat;
};