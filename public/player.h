#include <string>
#include <ctime>

class Player
{
public:
  Player(std::string fn, std::string ln, int yob, bool rs = false);
  Player(std::string fn, std::string ln, int yob, int cat, bool rs);
  Player(std::string data);
  std::string getName();
  int getYOB();
  int getCategory();
  std::string getCategoryAsString();
  bool getRegistration();
  void setRegistration(bool rs);

  std::string & operator [] (const std::string & query);

  std::string getLedgeMapKey();

  std::string save();
  void load(std::string data);

private:
  int calculateCategory();
  int currentYear();

  std::string fname;
  std::string lname;
  int birthYear;
  int category;
  bool regStat;
};