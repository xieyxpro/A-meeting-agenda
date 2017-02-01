/*************************************************************************
	> File Name: Storage.cpp
	> Author: LY
	> Mail: ly.franky@gmail.com
	> Created Time: Monday, June 30, 2014 PM10:06:44 HKT
 ************************************************************************/

#include <list>
#include <string>
#include <functional>
#include <fstream>
#include <string.h>
#include <iostream>

#include "User.h"
#include "Meeting.h"
#include "Storage.h"

Storage* Storage::instance_ = 0;

int getCount(char* str);

Storage::Storage() {
    readFromFile("agenda.data");
}

// storage structure with list, or you have better structures e.g. balanced tree
// File IO

bool Storage::readFromFile(const char *fpath) {
    std::ifstream file(fpath);
    if (!file) return false;
    char outStr[1000];
    file.getline(outStr, 1000);
    int count = getCount(outStr);
    userList_.clear();
    meetingList_.clear();
    for (int i = 0; i < count; i++) {
        char str[1000];
        str[strlen(str)] = '\0';
        file.getline(str, 1000);
        int startPosition, endPosition, temp = 0;
        startPosition = 7;
        for (int j = startPosition; j < strlen(str); j++) {
            if (str[j] == ',' && str[j - 1] == '\"') {
                endPosition = j - 2;
                break;
            }
        }
        std::string name;
        for (int j = startPosition; j <= endPosition; j++) {
            name += str[j];
        }
        startPosition = endPosition + 13;
        for (int j = startPosition; j < strlen(str); j++) {
            if (str[j] == ',' && str[j - 1] == '\"') {
                endPosition = j - 2;
                break;
            }
        }
        std::string password;
        for (int j = startPosition; j <= endPosition; j++) {
            password += str[j];
        }
        startPosition = endPosition + 10;
        for (int j = startPosition; j < strlen(str); j++) {
            if (str[j] == ',' && str[j - 1] == '\"') {
                endPosition = j - 2;
                break;
            }
        }
        std::string email;
        for (int j = startPosition; j <= endPosition; j++) {
            email += str[j];
        }
        startPosition = endPosition + 10;
        for (int j = startPosition; j < strlen(str); j++) {
            if (str[j] == '\"' && str[j + 1] == '}') {
                endPosition = j - 1;
                break;
            }
        }
        std::string phone;
        for (int j = startPosition; j <= endPosition; j++) {
            phone += str[j];
        }
        User u(name, password, email, phone);
        userList_.push_back(u);
    }
    char anotherStr[1000];
    file.getline(anotherStr, 1000);
    count = getCount(anotherStr);
    for (int i = 0; i < count; i++) {
        char str[1000];
        str[strlen(str)] = '\0';
        file.getline(str, 1000);
        int startPosition, endPosition, temp = 0;
        startPosition = 10;
        for (int j = startPosition; j < strlen(str); j++) {
            if (str[j] == ',' && str[j - 1] == '\"') {
                endPosition = j - 2;
                break;
            }
        }
        std::string sponsor;
        for (int j = startPosition; j <= endPosition; j++) {
            sponsor += str[j];
        }
        startPosition = endPosition + 17;
        for (int j = startPosition; j < strlen(str); j++) {
            if (str[j] == ',' && str[j - 1] == '\"') {
                endPosition = j - 2;
                break;
            }
        }
        std::string participator;
        for (int j = startPosition; j <= endPosition; j++) {
            participator += str[j];
        }
        startPosition = endPosition + 10;
        for (int j = startPosition; j < strlen(str); j++) {
            if (str[j] == ',' && str[j - 1] == '\"') {
                endPosition = j - 2;
                break;
            }
        }
        std::string sdate;
        for (int j = startPosition; j <= endPosition; j++) {
            sdate += str[j];
        }
        startPosition = endPosition + 10;
        for (int j = startPosition; j < strlen(str); j++) {
            if (str[j] == ',' && str[j - 1] == '\"') {
                endPosition = j - 2;
                break;
            }
        }
        std::string edate;
        for (int j = startPosition; j <= endPosition; j++) {
            edate += str[j];
        }
        startPosition = endPosition + 10;
        for (int j = startPosition; j < strlen(str); j++) {
            if (str[j] == '\"' && str[j + 1] == '}') {
                endPosition = j - 1;
                break;
            }
        }
        std::string title;
        for (int j = startPosition; j <= endPosition; j++) {
            title += str[j];
        }
        Meeting mt(sponsor, participator, Date::stringToDate(sdate),
                Date::stringToDate(edate), title);
        meetingList_.push_back(mt);
    }
    file.close();
    return true;
}

bool Storage::writeToFile(const char *fpath) {
    std::ofstream file(fpath);
    if (!file) return false;
    file << "{collection:\"User\",total:" << userList_.size() << "}\n";
    std::list<User>::iterator it = userList_.begin();
    while (it != userList_.end()) {
        file << "{name:\"" << it->getName() << "\",password:\"" <<
            it->getPassword() << "\",email:\"" << it->getEmail() <<
            "\",phone:\"" << it->getPhone() << "\"}\n";
        it++;
    }
    file << "{collection:\"Meeting\",total:" << meetingList_.size() << "}\n";
    std::list<Meeting>::iterator mit = meetingList_.begin();
    while (mit != meetingList_.end()) {
        file << "{sponsor:\"" << mit->getSponsor() << "\",participator:\"";
        file << mit->getParticipator() << "\",sdate:\"" <<
            Date::dateToString(mit->getStartDate());
        file << "\",edate:\"" << Date::dateToString(mit->getEndDate())
            << "\",title:\"";
        file << mit->getTitle() << "\"}\n";
        mit++;
    }
    file.close();
}

// singleton

Storage* Storage::getInstance(void) {
    if (instance_ == 0) {
        instance_ = new Storage();
    }
    return instance_;
}

Storage::~Storage() {
    writeToFile("agenda.data");
    userList_.clear();
    meetingList_.clear();
    instance_ = 0;
}

// CRUD for User & Meeting using C++11 Function Template and Lambda Expressions

void Storage::createUser(const User& user) {
    userList_.push_back(user);
}

std::list<User> Storage::queryUser(std::function<bool(const User&)> filter) {
    std::list<User> temp;
    std::list<User>::iterator it = userList_.begin();
    while (it != userList_.end()) {
        if (filter(*it)) {
            temp.push_back(*it);
        }
        it++;
    }
    return temp;
}   // return found users

int Storage::updateUser(std::function<bool(const User&)> filter,
        std::function<void(User&)> switcher) {
    std::list<User>::iterator it = userList_.begin();
    int count = 0;
    while (it != userList_.end()) {
        if (filter(*it)) {
            count++;
            switcher(*it);
        }
        it++;
    }
    return count;
}   // return the number of updated users

int Storage::deleteUser(std::function<bool(const User&)> filter) {
    std::list<User>::iterator it = userList_.begin();
    int count = 0;
    while (it != userList_.end()) {
        if (filter(*it)) {
            count++;
            //deleteMeeting([it](const Meeting& meeting){
                //return meeting.getSponsor() == it->getName() || meeting.getParticipator() == it->getName();
            //});
            userList_.erase(it);
            it--;
        }
        it++;
    }
    return count;
}   // return the number of deleted users

void Storage::createMeeting(const Meeting& meeting) {
    meetingList_.push_back(meeting);
}

std::list<Meeting> Storage::queryMeeting(std::function
        <bool(const Meeting&)> filter) {
    std::list<Meeting> temp;
    std::list<Meeting>::iterator it = meetingList_.begin();
    while (it != meetingList_.end()) {
        if (filter(*it)) {
            temp.push_back(*it);
        }
        it++;
    }
    return temp;
}   // return found meetings

int Storage::updateMeeting(std::function<bool(const Meeting&)> filter,
        std::function<void(Meeting&)> switcher) {
    std::list<Meeting>::iterator it = meetingList_.begin();
    int count = 0;
    while (it != meetingList_.end()) {
        if (filter(*it)) {
            count++;
            switcher(*it);
        }
        it++;
    }
    return count;
}   // return the number of updated meetings

int Storage::deleteMeeting(std::function<bool(const Meeting&)> filter) {
    std::list<Meeting>::iterator it = meetingList_.begin();
    int count = 0;
    while (it != meetingList_.end()) {
        if (filter(*it)) {
            meetingList_.erase(it);
            count++;
            it--;
        }
        it++;
    }
    return count;
}   // return the number of deleted meetings

// File IO

bool Storage::sync(void) {
    return writeToFile("agenda.data");
}

int getCount(char* str) {
    int p[100];
    int c = 0;
    int temp = strlen(str) - 2;
    while (1) {
        if (str[temp] >= '0' && str[temp] <= '9') {
            p[c] = str[temp] - '0';
            c++;
            temp--;
        } else {
            break;
        }
    }
    int ans = 0, base = 1;
    for (int i = 0; i < c; i++) {
        ans += p[i] * base;
        base *= 10;
    }
    return ans;
}

