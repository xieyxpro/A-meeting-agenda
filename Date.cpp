/*************************************************************************
	> File Name: Date.cpp
	> Author: LY
	> Mail: ly.franky@gmail.com
	> Created Time: Monday, June 30, 2014 PM05:28:22 HKT
 ************************************************************************/

#include <string>
#include <iostream>
#include <stdio.h>
#include "Date.h"
#include <stdlib.h>

const int leapYearDayInMonth[13] = {0, 31, 29, 31, 30, 31, 30,
    31, 31, 30, 31, 30, 31};
const int commonYearDayInMonth[13] = {0, 31, 28, 31, 30, 31, 30,
    31, 31, 30, 31, 30, 31};

bool isLeapYear(int y);

bool isNumber(char x);

std::string toString(int n);

Date::Date() {
    year_ = month_ = day_ = hour_ = minute_ = 0;
}

Date::Date(int y, int m, int d, int h, int mi) {
    year_ = y;
    month_ = m;
    day_ = d;
    hour_ = h;
    minute_ = mi;
}

int Date::getYear(void) const {
    return year_;
}

void Date::setYear(int year) {
    year_ = year;
}

int Date::getMonth(void) const {
    return month_;
}

void Date::setMonth(int month) {
    month_ = month;
}

int Date::getDay(void) const {
    return day_;
}

void Date::setDay(int day) {
    day_ = day;
}

int Date::getHour(void) const {
    return hour_;
}

void Date::setHour(int hour) {
    hour_ = hour;
}

int Date::getMinute(void) const {
    return minute_;
}

void Date::setMinute(int minute) {
    minute_ = minute;
}

bool Date::isValid(Date date) {
    int tempYear = date.getYear();
    int tempMonth = date.getMonth();
    int tempDay = date.getDay();
    int tempHour = date.getHour();
    int tempMinute = date.getMinute();
    if (tempYear < 1000 || tempYear > 9999) return false;
    if (tempMonth < 0 || tempMonth > 12) return false;
    if (isLeapYear(tempYear)) {
        int temp = leapYearDayInMonth[tempMonth];
        if (tempDay < 1 || tempDay > temp) return false;
    } else {
        int temp = commonYearDayInMonth[tempMonth];
        if (tempDay < 1 || tempDay > temp) return false;
    }
    if (tempHour < 0 || tempHour > 23) return false;
    if (tempMinute < 0 || tempMinute > 59) return false;
    return true;
}
// static

Date Date::stringToDate(std::string dateString) {
    Date *temp = new Date();
    char y[5]; y[0] = dateString[0];
    y[1] = dateString[1]; y[2] = dateString[2];
    y[3] = dateString[3]; y[4] = '\0';
    std::string year = y;
    temp->setYear(atoi(year.c_str()));
    int position = 5;
    char m[3]; int count = 0;
    while (dateString[position] != '-') {
        m[count] = dateString[position];
        count++; position++;
    }
    m[count] = '\0';
    std::string month = m;
    temp->setMonth(atoi(month.c_str()));
    position++;
    char d[3]; count = 0;
    while (dateString[position] != '/') {
        d[count] = dateString[position];
        count++; position++;
    }
    d[count] = '\0';
    std::string day = d;
    temp->setDay(atoi(day.c_str()));
    position++;

    char h[3]; count = 0;
    while(dateString[position] != ':') {
        h[count] = dateString[position];
        count++; position++;
    }
    h[count] = '\0';
    std::string hour = h;
    temp->setHour(atoi(hour.c_str()));
    position++;
    char mi[3]; count = 0;
    while (dateString[position] != '\0') {
        mi[count] = dateString[position];
        count++; position++;
    }
    mi[count] = '\0';
    std::string minute = mi;
    temp->setMinute(atoi(minute.c_str()));
    return *temp;
}
// static

std::string Date::dateToString(Date date) {
    std::string ans;
    ans += toString(date.getYear()) + "-";
    if (date.getMonth() < 10) ans += "0";
    ans += toString(date.getMonth()) + "-";
    if (date.getDay() < 10) ans += "0";
    ans += toString(date.getDay()) + "/";
    if (date.getHour() < 10) ans += "0";
    ans += toString(date.getHour()) + ":";
    if (date.getMinute() < 10) ans += "0";
    ans += toString(date.getMinute());
    return ans;
}
// static

Date& Date::operator=(const Date& date) {
    year_ = date.getYear();
    month_ = date.getMonth();
    day_ = date.getDay();
    hour_ = date.getHour();
    minute_ = date.getMinute();
    return *this;
}

bool Date::operator==(const Date& date) const {
    if (year_ != date.getYear()) return false;
    if (month_ != date.getMonth()) return false;
    if (day_ != date.getDay()) return false;
    if (hour_ != date.getHour()) return false;
    if (minute_ != date.getMinute()) return false;
    return true;
}

bool Date::operator>(const Date& date) const {
    if (year_ < date.getYear()) return false;
    if (year_ > date.getYear()) return true;
    if (month_ < date.getMonth()) return false;
    if (month_ > date.getMonth()) return true;
    if (day_ < date.getDay()) return false;
    if (day_ > date.getDay()) return true;
    if (hour_ < date.getHour()) return false;
    if (hour_ > date.getHour()) return true;
    if (minute_ < date.getMinute()) return false;
    if (minute_ > date.getMinute()) return true;
    if (year_ == date.getYear() && month_ == date.getMonth()
            && day_ == date.getDay() && hour_ == date.getHour()
            && minute_ == date.getMinute()) {
        return false;
    }
}

bool Date::operator<(const Date& date) const {
    if (year_ > date.getYear()) return false;
    if (year_ < date.getYear()) return true;
    if (month_ > date.getMonth()) return false;
    if (month_ < date.getMonth()) return true;
    if (day_ > date.getDay()) return false;
    if (day_ < date.getDay()) return true;
    if (hour_ > date.getHour()) return false;
    if (hour_ < date.getHour()) return true;
    if (minute_ > date.getMinute()) return false;
    if (minute_ < date.getMinute()) return true;
    if (year_ == date.getYear() && month_ == date.getMonth()
            && day_ == date.getDay() && hour_ == date.getHour()
            && minute_ == date.getMinute()) {
        return false;
    }
}

bool Date::operator>=(const Date& date) const {
    if (year_ < date.getYear()) return false;
    if (year_ > date.getYear()) return true;
    if (month_ < date.getMonth()) return false;
    if (month_ > date.getMonth()) return true;
    if (day_ < date.getDay()) return false;
    if (day_ > date.getDay()) return true;
    if (hour_ < date.getHour()) return false;
    if (hour_ > date.getHour()) return true;
    if (minute_ < date.getMinute()) return false;
    if (minute_ > date.getMinute()) return true;
    if (year_ == date.getYear() && month_ == date.getMonth()
            && day_ == date.getDay() && hour_ == date.getHour()
            && minute_ == date.getMinute()) {
        return true;
    }
}

bool Date::operator<=(const Date& date) const {
    if (year_ > date.getYear()) return false;
    if (year_ < date.getYear()) return true;
    if (month_ > date.getMonth()) return false;
    if (month_ < date.getMonth()) return true;
    if (day_ > date.getDay()) return false;
    if (day_ < date.getDay()) return true;
    if (hour_ > date.getHour()) return false;
    if (hour_ < date.getHour()) return true;
    if (minute_ > date.getMinute()) return false;
    if (minute_ < date.getMinute()) return true;
    if (year_ == date.getYear() && month_ == date.getMonth()
            && day_ == date.getDay() && hour_ == date.getHour()
            && minute_ == date.getMinute()) {
        return true;
    }
}

bool isLeapYear(int y) {
    if (y % 400 == 0) return true;
    if (y % 100 == 0) return false;
    if (y % 4 == 0) return true;
    return false;
}

std::string toString(int n) {
    char temp[1000];
    snprintf(temp, sizeof(temp), "%d", n);
    std::string result = temp;
    return result;
}

bool isNumber(char x) {
    if (x >= '0' && x <= '9') return true;
    return false;
}

