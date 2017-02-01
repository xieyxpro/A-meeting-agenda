/*************************************************************************
	> File Name: fileTest.cpp
	> Author: LY
	> Mail: ly.franky@gmail.com
	> Created Time: Tuesday, July 01, 2014 PM08:26:55 HKT
 ************************************************************************/

#include <list>
#include <string>
#include <functional>
#include <fstream>
#include <string.h>

#include "User.h"
#include "Date.h"
#include "Meeting.h"
using namespace std;
int getCount(char* str);

int main() {
    list<User> userList_;
    list<Meeting> meetingList_;
    std::ifstream ifile;
    ifile.open("origin.data");
    char outStr[1000];
    ifile.getline(outStr, 1000);
    int count = getCount(outStr);
    userList_.clear();
    meetingList_.clear();
    for (int i = 0; i < count; i++) {
        char str[1000];
        str[strlen(str)] = '\0';
        ifile.getline(str, 1000);
        int startPosition = 0, endPosition = 0, temp = 0;
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
        std::string password = "";
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
    ifile.getline(anotherStr, 1000);
    count = getCount(anotherStr);
    for (int i = 0; i < count; i++) {
        char str[1000];
        str[strlen(str)] = '\0';
        ifile.getline(str, 1000);
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
    ifile.close();

    std::ofstream file;
    file.open("agenda.data");
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

