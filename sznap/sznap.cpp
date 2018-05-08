#include <ctime>
#include <iostream>
#include <string.h>

using namespace std;

int addyear(int year, int dd) {
  while(year < 300){
    year++;
    if( ((year%4) == 0) && (((year%100) != 0) || ((year%400) == 0)) ) {
      dd = (dd+2)%7;
    }
    else {
      dd = (dd+1)%7;
    }
  }

  return dd;
}

int main() {
  int year, month, day;
  cout << "Év:";
  cin >> year;
  cout << "Hónap:";
  cin >> month;
  cout << "Nap:";
  cin >> day;
  std::tm time_in = {0, 0, 0, day, month-1, year-1900};

  std::time_t time_temp = std::mktime(&time_in);

  const std::tm * time_out = std::localtime(&time_temp);
  string s;
  switch(addyear(year, static_cast<int>(time_out->tm_wday))) {
    case 0: s="Vasarnap";
      break;
    case 1: s="Szombat";
      break;
    case 2: s="Pentek";
      break;
    case 3: s="Csutortok";
      break;
    case 4: s="Szerda";
      break;
    case 5: s="Kedd";
      break;
    case 6: s="Hetfo";
      break;
  }

  std::cout << "Szuletesnapod 3000-ben: " << s << "\n";

  return 0;

}

