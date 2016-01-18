#include <iostream>

using namespace std;

struct date {
  int day, month, year;
};

void nextmonth(date& d) {
  d.month++;
  d.day = 1;
}

int main(int argc, char** argv) {
  
  date d;
  cout << "Enter a date on the following format, YYYY MM DD:";
  cin >> d.year;
  cin >> d.month;
  cin >> d.day;

  cout << "The next date is:";
  date nextd = d;
  if (d.month == 1 && d.day == 31) {
    nextmonth(d);
  } else if (d.month == 2 && d.day == 28) {
    nextmonth(d);
  } else if (d.month == 3 && d.day == 31) {
    nextmonth(d);
  } else if (d.month == 4 && d.day == 30) {
    nextmonth(d);
  } else if (d.month == 5 && d.day == 31) {
    nextmonth(d);
  } else if (d.month == 6 && d.day == 30) {
    nextmonth(d);
  } else if (d.month == 7 && d.day == 31) {
    nextmonth(d);
  } else if (d.month == 8 && d.day == 31) {
    nextmonth(d);
  } else if (d.month == 9 && d.day == 30) {
    nextmonth(d);
  } else if (d.month == 10 && d.day == 31) {
    nextmonth(d);
  } else if (d.month == 11 && d.day == 30) {
    nextmonth(d);
  } else if (d.month == 12 && d.day == 31) {
      nextd.month = 1;
      nextd.day = 1;
      nextd.year++;
  } else {
    nextd.day++;
  }

  cout << nextd.year << " " << nextd.month << " " << nextd.day << endl;
    

}
