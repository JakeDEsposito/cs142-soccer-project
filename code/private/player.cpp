#ifndef PlayerClass
#include "./../public/player.h"
#endif

Player::Player(std::string fn, std::string ln, int birthdate, bool rs, const int year)
{
  fname = fn;
  lname = ln;
  birthYear = birthdate;
  category = calculateCategory(year);
  regStat = rs;
}

Player::Player(std::string fn, std::string ln, int birthdate, int cat, bool rs)
{
  fname = fn;
  lname = ln;
  birthYear = birthdate;
  category = cat;
  regStat = rs;
}

Player::Player(std::string data)
{
  load(data);
}

Player::~Player()
{
  auto fnamePtr = &fname;
  auto lnamePtr = &lname;
  auto birthYearPtr = &birthYear;
  auto categoryPtr = &category;
  auto regStatPtr = &regStat;

  delete fnamePtr;
  delete lnamePtr;
  delete birthYearPtr;
  delete categoryPtr;
  delete regStatPtr;
}

std::string Player::getName()
{
  return fname + " " + lname;
}

int Player::getYOB()
{
  return birthYear;
}

int Player::getCategory()
{
  return category;
}

std::string Player::getCategoryAsString()
{
  return "U" + category;
}

bool Player::getRegistration()
{
  return regStat;
}

void Player::setRegistration(bool rs)
{
  regStat = rs;
}

std::string Player::operator[](const std::string & query)
{
  if(query == "first_name" || query == "fn")
    return fname;
  else if(query == "last_name" || query == "ln")
    return lname;
  else if(query == "birth_year" || query == "by")
    {
      std::string t=std::to_string(birthYear);
      return t;
    }
  else if(query == "category" || query == "ca")
    {
      std::string t=std::to_string(category);
      return t;
    }
  else if(query == "registration_status" || query == "rs")
    {
      if(regStat)
	{
	  return std::string("true");
	}
      else
	{
	  return std::string("false");
	}
    }
  else
    return std::string("error: Faulty player query!");
}

std::string Player::save()
{
  return fname + "_" + lname + ":" + std::to_string(birthYear) + "." + std::to_string(category) + "," + std::to_string(regStat);
}

void Player::load(std::string data)
{
  fname = data.substr(0, data.find("_"));
  lname = data.substr(data.find("_"), data.find(":") - data.find("_"));
  birthYear = std::stoi(data.substr(data.find(":"), data.find(".") - data.find(":")));
  category = std::stoi(data.substr(data.find("."), data.find(",") - data.find(".")));
  regStat = std::stoi(data.substr(data.find(",")));
}

int Player::calculateCategory(const int year)
{
  int yearAge = year - birthYear;
    
  if(yearAge < 6)
    return 6;
  else if(yearAge < 8)
    return 8;
  else if(yearAge < 10)
    return 10;
  else if(yearAge < 12)
    return 12;
  else if(yearAge < 14)
    return 14;
  else if(yearAge < 17)
    return 17;
  else 
    return -1;
}
