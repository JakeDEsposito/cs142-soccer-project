// Code taken from cthorpe/public/142/listeditor

#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <cstring>
#include "buffer.h"
using namespace std;

const string long_dash(50, '-');

void Buffer::insert(string newstr) {
  //  buff.insert(buff.begin()+current_line, newstr);
  buff.insert(current_itr, newstr);
}

void Buffer::erase() {
  //  if (current_line < buff.size()) buff.erase(buff.begin()+current_line);
  current_itr = buff.erase(current_itr);
}

void Buffer::replace (string newstr) {
  if (current_line < buff.size()) *current_itr = newstr;
//buff[current_line] = newstr;
  if (current_line == buff.size()) buff.push_back(newstr);
}

void Buffer::jump (int l) {
  l = l - 1;
  if ((l > 0) && (l <= buff.size())) {
      top_line = current_line = l;
      top_itr = buff.begin();
      for (int i = 0; i < l; i++) top_itr++;
      current_itr = top_itr;
    }
}

bool Buffer::search (string s) {
  /*  for (int i = top_line; i < buff.size(); i++) {
    if (buff[i].find(s) != string::npos) {
      top_line = i;
      current_line = i;
      return 0;
    }
    } */
  int row = top_line;
  for (auto itr = current_itr; itr != buff.end(); itr++) {
    if ((*itr).find(s) != string::npos) {
      top_line = row;
      current_line = row;
      top_itr = itr;
      current_itr = itr;
      return 0;
    }
    row++;
  }
  return 1;
}


void Buffer::down(){
  if (current_line <= buff.size()) {
    current_line++;
    current_itr++;
  }
  if (current_line > (top_line + height - 1)) {
    top_line = current_line; 
    top_itr = current_itr;
  }
}

void Buffer::up() {
  if (current_line > 0) {
    current_line--;
    current_itr--;
  }
  if (current_line < top_line) {
    top_line = current_line;
    top_itr = current_itr;
  }
}

void Buffer::next(){
  if ((top_line + height) < buff.size()) {
      top_line += height;
      advance (top_itr, height);
    }
    else {
      int delta = buff.size() - top_line;
      top_line += delta;
      advance(top_itr, delta);
    }
    //  if (top_line > buff.size() - height) top_line = buff.size() - height;
    if (current_line < top_line) {
      current_line = top_line;
      current_itr = top_itr;
    }
    if (current_line > (top_line + height - 1)) {
      current_line = top_line;
      current_itr = top_itr;
    }
}

void Buffer::prev() {
  int delta;
  delta = top_line - height;
  if (delta < 0) delta = top_line;
  top_line -= delta;
  advance (top_itr, -delta);
  //  top_line -= height;
  //  if (top_line < 0) top_line = 0;
  if (current_line < top_line) {
    current_line = top_line;
    current_itr = top_itr;
  }
  if (current_line > (top_line + height - 1)) {
    current_line = top_line; 
    current_itr = top_itr;
  }
}

bool Buffer::save (char filename []) {
  ofstream outstr;
  outstr.open (filename);
  if (outstr.fail()) return true;
  for (string s : buff) outstr << s << endl;
  return false;
}

bool Buffer::open (char filename []) {
  string line;
  ifstream instr;
  buff.clear();
  instr.open (filename);
  while (getline (instr, line)) buff.push_back(line);
  instr.close();
  strcpy (fname, filename);
  top_line = current_line = 0;
  top_itr = current_itr = buff.begin();
}

void Buffer::display() {
  int i;
  int maxline;
  maxline = top_line + height;
  if (maxline > buff.size()+1) maxline = buff.size()+1;
  auto itr = top_itr;
  cout <<fname << endl;
  cout << long_dash << endl;
  for (int i = top_line; i < maxline;  i++) {
    if (i == current_line) cout << "> "; else cout << "  ";
    if (i < 9) cout << " ";
    cout << i+1 << " ";
    if (i < buff.size())
      cout << *itr++;
      //      cout << buff[i];
    cout << endl;
  }
  cout << long_dash << endl;

}
