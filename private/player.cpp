#include "player.h"

Player::Player(std::string fn, std::string ln, int birthdate, bool rs)
{
    fname = fn;
    lname = ln;
    birthYear = birthdate;
    category = calculateCategory();
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

std::string & Player::operator[](const std::string & query)
{
    if(query == "first_name" || query == "fn")
        return fname;
    else if(query == "last_name" || query == "ln")
        return lname;
    else if(query == "birth_year" || query == "by")
        return std::to_string(birthYear);
    else if(query == "category" || query == "ca")
        return std::to_string(category);
    else if(query == "registration_status" || query == "rs")
        return std::to_string(regStat);
    else
        return std::string("error: Faulty player query!");
}

std::string Player::getLedgeMapKey()
{
    return fname + "_" + lname;
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

int Player::calculateCategory()
{
    int yearAge = currentYear() - birthYear;
    
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
}

//https://stackoverflow.com/questions/58151350/more-elegant-way-to-get-the-current-year-in-c
int Player::currentYear()
{
    std::time_t t = std::time(nullptr);
    std::tm *const pTInfo = std::localtime(&t);
    return 1900 + pTInfo->tm_year;
}