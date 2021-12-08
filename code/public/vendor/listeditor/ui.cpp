// Code taken from cthorpe/public/142/listeditor

#include <iostream>
#include "buffer.h"
using namespace std;


int main()
{
  int height;
  char a;
  char filename[80];
  Buffer buffer;
  string target;
  bool error = false;
  bool error2 = false;
  string newstr;

  cout << "How high should the window be? ";
  cin >> height;
  buffer.set_height(height);

  while (true) {
    cout << "next previous open quit search \n";
    cout << "up down jump replace erase write insert ";
    cin >> a;
    cin.get();
    switch (a) {
    case 'w':
      cout << "Filename: ";
      cin >> filename;
      error2 = buffer.save(filename);
      break;
    case 'o':
      cout << "Filename: ";
      cin >> filename;
      buffer.open(filename);
      break;
    case 'n':
      buffer.next();
      break;
    case 'p':
      buffer.prev();
      break;
    case 'q':
      return 0;
      break;
    case 's':
      cout << "Target: ";
      cin >> target;
      error = buffer.search(target);
      break;
    case 'u':
      buffer.up();
      break;
    case 'd':
      buffer.down();
      break;
    case 'j':
      int l;
      cout << "Line number :";
      cin >> l;
      buffer.jump(l);
      break;
    case 'r':
      cout << "New line ";
      getline (cin, newstr);
      buffer.replace(newstr);
      break;
    case 'i':
      cout << "New line ";
      getline (cin, newstr);
      buffer.insert(newstr);
      break;
    case 'e':
      buffer.erase();
      break;
    default:
      break;
    }
    cout << static_cast<char> (12);
    buffer.display();
    if (error) {
      cout << "Can't find " << target << endl;
      error = false;
    }
    if (error2) {
      cout << "Can't write to " << filename << endl;
      error2 = false;
    }
  }
}
