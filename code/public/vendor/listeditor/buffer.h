// Code taken from cthorpe/public/142/listeditor

#include <vector>
#include <list>

class Buffer {
 private:
  int top_line = 0;
  int current_line = 0;
  int height = 5;
  std::list <std::string> buff;
  char fname[80];
  //  std::vector<std::string>::iterator top_itr;
  //  std::vector<std::string>::iterator current_itr;
  std::list<std::string>::iterator top_itr;
  std::list<std::string>::iterator current_itr;

 public:
  void next();
  void prev();
  bool open (char filename []);
  void display();
  void set_height(int h) {height = h; }
  bool search (std::string target);
  void down();
  void up();
  void jump (int l);
  void replace (std::string newstr);
  void erase();
  void insert(std:: string newstr);
  bool save(char filename []);
};
