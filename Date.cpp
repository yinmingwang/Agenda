#include<iostream>
#include<string>
#include<cstdio>
#include<sstream>
#include<iomanip>
#include"Date.h"
using namespace std;

Date::Date() :year_(1000), month_(1), day_(1),
              hour_(0), minute_(0) {}

Date::Date(int y, int m, int d, int h, int mi)
     :year_(y), month_(m), day_(d),
      hour_(h), minute_(mi) {}

int Date::getYear() const {
    return year_;
}

void Date::setYear(int year) {
    year_ = year;
}

int Date::getMonth() const {
    return month_;
}

void Date::setMonth(int month) {
    month_ = month;
}

int Date::getDay() const {
    return day_;
}

void Date::setDay(int day) {
    day_ = day;
}

int Date::getHour() const {
    return hour_;
}

void Date::setHour(int hour) {
    hour_ = hour;
}

int Date::getMinute() const {
    return minute_;
}

void Date::setMinute(int minute) {
    minute_ = minute;
}

bool Date::isValid(Date date) {
    int days[13] = {0, 31, 28, 31, 30, 31, 30,
                    31, 31, 30, 31, 30, 31};
    
    int y = date.getYear();
    int m = date.getMonth();
    int d = date.getDay();
    int h = date.getHour();
    int mi = date.getMinute();

    // check year and month       
    if ( y < 1000 || y > 9999 ||
         m <= 0 || m > 12 ) {
        return false;
    }

    // check leap year
    if ( isLeap(y) ) {
        days[2] = 29;
    }

    if ( d <= 0 || d > days[m] ||
         h < 0 || h >= 24 || 
         mi < 0 || mi >= 60 ) {
         return false;
    }

    return true;
}

bool Date::isLeap(int y) {
    if ( (y % 4 == 0 && y % 100 != 0) || y % 400 == 0 ) {
        return true;
    } else {
        return false;
    }
}

Date Date::stringToDate(string dateString) {
    int y, m, d, h, mi;

    sscanf(dateString.c_str(), "%d-%d-%d/%d:%d",
           &y, &m, &d, &h, &mi);
           
    Date date;
    date.setYear(y);
    date.setMonth(m);
    date.setDay(d);
    date.setHour(h);
    date.setMinute(mi);
    return date;
}

string Date::dateToString(Date date) {
    stringstream ss;
    ss << date.getYear() << "-"
       << setw(2) << setfill('0') << date.getMonth() << "-"
       << setw(2) << setfill('0') << date.getDay() << "/"
       << setw(2) << setfill('0') << date.getHour() << ":"
       << setw(2) << setfill('0') << date.getMinute();
    // no newline here
    string s = ss.str();
    return s;
}

// necessary???
Date& Date::operator=(const Date& date) {
    this->setYear(date.getYear());
    this->setMonth(date.getMonth());
    this->setDay(date.getDay());
    this->setHour(date.getHour());
    this->setMinute(date.getMinute());
    return *this;
}

bool Date::operator==(const Date& date) const {
    if ( date.getYear() == this->getYear() &&
         date.getMonth() == this->getMonth() &&
         date.getDay() == this->getDay() &&
         date.getHour() == this->getHour() &&
         date.getMinute() == this->getMinute() ) {
         return true;
    } else {
         return false;
    }
}

bool Date::operator>(const Date& date) const {
    if ( this->getYear() > date.getYear() ||
         (this->getYear() == date.getYear() &&
         this->getMonth() > date.getMonth()) ||
         (this->getYear() == date.getYear() &&
         this->getMonth() == date.getMonth() &&
         this->getDay() > date.getDay()) ||
         (this->getYear() == date.getYear() &&
         this->getMonth() == date.getMonth() &&
         this->getDay() == date.getDay() &&
         this->getHour() > date.getHour()) ||
         (this->getYear() == date.getYear() &&
         this->getMonth() == date.getMonth() &&
         this->getDay() == date.getDay() &&
         this->getHour() == date.getHour() &&
         this->getMinute() > date.getMinute()) ) {
         return true;
    }
    return false;
}

bool Date::operator<(const Date& date) const {
    if ( this->getYear() < date.getYear() ||
         (this->getYear() == date.getYear() &&
         this->getMonth() < date.getMonth()) ||
         (this->getYear() == date.getYear() &&
         this->getMonth() == date.getMonth() &&
         this->getDay() < date.getDay()) ||
         (this->getYear() == date.getYear() &&
         this->getMonth() == date.getMonth() &&
         this->getDay() == date.getDay() &&
         this->getHour() < date.getHour()) ||
         (this->getYear() == date.getYear() &&
         this->getMonth() == date.getMonth() &&
         this->getDay() == date.getDay() &&
         this->getHour() == date.getHour() &&
         this->getMinute() < date.getMinute()) ) {
         return true;
    }
    return false;
}

bool Date::operator>=(const Date& date) const {
    if ( !(*this < date) ) {
        return true;
    }
    return false;
}

bool Date::operator<=(const Date& date) const {
    if ( !(*this > date) ) {
        return true;
    }
    return false;
}

