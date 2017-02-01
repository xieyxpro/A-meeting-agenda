/*************************************************************************
	> File Name: AgendaUI.cpp
	> Author: LY
	> Mail: ly.franky@gmail.com
	> Created Time: Wednesday, July 02, 2014 AM11:03:05 HKT
 ************************************************************************/

#include "AgendaService.h"
#include "AgendaUI.h"
#include <iostream>
#include <string>
#include <list>
#include <iomanip>

// public:
AgendaUI::AgendaUI() {
    userName_ = userPassword_ = "";
}

bool quit = false;

void AgendaUI::OperationLoop(void) {
    while(1) {
        if (userName_ == "") {
            std::cout << std::endl;
            std::cout << "==================================Agenda==================================" << std::endl;
            std::cout << "Action :" << std::endl;
            std::cout << "l   - log in Agenda by user name and password" << std::endl;
            std::cout << "r   - register an Agenda account" << std::endl;
            std::cout << "q   - quit Agenda" << std::endl;
            std::cout << "==========================================================================" << std::endl;
            std::cout << std::endl;
            std::cout << "Agenda : ~$ ";
        } else {
            std::cout << std::endl;
            std::cout << "==================================Agenda==================================" << std::endl;
            std::cout << "Action :" << std::endl;
            std::cout << "o   - log out Agenda" << std::endl;
            std::cout << "dc  - delete Agenda account" << std::endl;
            std::cout << "lu  - list all Agenda user" << std::endl;
            std::cout << "cm  - create a meeting" << std::endl;
            std::cout << "la  - list all meetings" << std::endl;
            std::cout << "las - list all sponsor meetings" << std::endl;
            std::cout << "lap - list all participator meetings" << std::endl;
            std::cout << "qm  - query meeting by title" << std::endl;
            std::cout << "qt  - query meeting by time interval" << std::endl;
            std::cout << "dm  - delete meeting by title" << std::endl;
            std::cout << "da  - delete all meetings" << std::endl;
            std::cout << "==========================================================================" << std::endl;
            std::cout << std::endl;
            std::cout << "Agenda@" << userName_ << " : # ";
        }
        std::string op = getOperation();
        if (!executeOperation(op)) std::cout << "Invalid operation" << std::endl;
        if (quit) return;
    }
}

// private:
// task functions
void AgendaUI::startAgenda(void) {}

std::string AgendaUI::getOperation() {
    std::string op;
    std::cin >> op;
    return op;
}

bool AgendaUI::executeOperation(std::string op) {
    if (userName_ == "") {
        if (op == "l") {userLogIn(); return true;}
        if (op == "r") {userRegister(); return true;}
        if (op == "q") {quitAgenda(); return true;}
        return false;
    } else {
        if (op == "o") {userLogOut(); return true;}
        if (op == "dc") {deleteUser(); return true;}
        if (op == "lu") {listAllUsers(); return true;}
        if (op == "cm") {createMeeting(); return true;}
        if (op == "la") {listAllMeetings(); return true;}
        if (op == "las") {listAllSponsorMeetings(); return true;}
        if (op == "lap") {listAllParticipateMeetings(); return true;}
        if (op == "qm") {queryMeetingByTitle(); return true;}
        if (op == "qt") {queryMeetingByTimeInterval(); return true;}
        if (op == "dm") {deleteMeetingByTitle(); return true;}
        if (op == "da") {deleteAllMeetings(); return true;}
        return false;
    }
}

void AgendaUI::userLogIn(void) {
    std::cout << std::endl;
    std::cout << "[log in] [user name] [password]" << std::endl;
    std::cout << "[log in] ";
    std::string un, pwd;
    std::cin >> un >> pwd;
    if (agendaService_.userLogIn(un, pwd)) {
        userName_ = un;
        userPassword_ = pwd;
        std::cout << "[log in] succeed!" << std::endl;
    } else {
        std::cout << "[error] log in fail!" << std::endl;
    }
    std::cout << std::endl;
}

void AgendaUI::userRegister(void) {
    std::cout << std::endl;
    std::cout << "[register] [user name] [password] [email] [phone]" << std::endl;
    std::cout << "[register] ";
    std::string un, pwd, em, ph;
    std::cin >> un >> pwd >> em >> ph;
    if (agendaService_.userRegister(un, pwd, em, ph)) {
        std::cout << "[register] succeed!" << std::endl;
    } else {
        std::cout << "[error] register fail!" << std::endl;
    }
    std::cout << std::endl;
}

void AgendaUI::quitAgenda(void) {
    std::cout << std::endl;
    quit = true;
}

void AgendaUI::userLogOut(void) {
    userName_ = "";
    userPassword_ = "";
}

void AgendaUI::deleteUser(void) {
    std::cout << std::endl;
    if (agendaService_.deleteUser(userName_, userPassword_)) {
        userLogOut();
        std::cout << "[delete agenda account] succeed!" << std::endl;
    }
    std::cout << std::endl;
}

void AgendaUI::listAllUsers(void) {
    std::cout << std::endl;
    std::cout << "[list all users]" << std::endl;
    std::cout << std::endl;
    std::cout << std::setw(10) << std::left << "name" << std::setw(20) <<
        "email" << std::setw(20) << "phone" << std::endl;
    std::list<User> usr = agendaService_.listAllUsers();
    std::list<User>::iterator it = usr.begin();
    while (it != usr.end()) {
        std::cout << std::setw(10) << std::left << it->getName() << std::setw(20) <<
            it->getEmail() << std::setw(20) << it->getPhone() << std::endl;
        it++;
    }
    std::cout << std::endl;
}

void AgendaUI::createMeeting(void) {
    std::cout << std::endl;
    std::cout << "[create meeting] [title] [participator] [start time<yyyy-mm-dd/hh:mm>] [end time<yyyy-mm-dd/hh:mm>]" << std::endl;
    std::cout << "[create meeting] ";
    std::string tt, ptcp, st, et;
    std::cin >> tt >> ptcp >> st >> et;
    if (agendaService_.createMeeting(userName_, tt, ptcp, st, et)) {
        std::cout << "[create meeting] succeed!" << std::endl;
    } else {
        std::cout << "[error] create meeting fail!" << std::endl;
    }
    std::cout << std::endl;
}

void AgendaUI::listAllMeetings(void) {
    std::cout << std::endl;
    std::list<Meeting> mt = agendaService_.listAllMeetings(userName_);
    std::list<Meeting>::iterator it = mt.begin();
    std::cout << "list all meetings" << std::endl;
    std::cout << std::endl;
    std::cout << std::left << std::setw(20) << "title" << std::setw(20) <<
        "sponsor" << std::setw(20) << "participator" << std::setw(20) <<
        "start time" << std::setw(20) << "end time" << std::endl;
    while (it != mt.end()) {
        std::cout << std::left << std::setw(20) << it->getTitle() << std::setw(20) <<
            it->getSponsor() << std::setw(20) << it->getParticipator() << std::setw(20) <<
            Date::dateToString(it->getStartDate()) << std::setw(20) << Date::dateToString(it->getEndDate()) << std::endl;
        it++;
    }
    std::cout << std::endl;
}

void AgendaUI::listAllSponsorMeetings(void) {
    std::cout << std::endl;
    std::list<Meeting> mt = agendaService_.listAllSponsorMeetings(userName_);
    std::list<Meeting>::iterator it = mt.begin();
    std::cout << "list all sponsor meetings" << std::endl;
    std::cout << std::endl;
    std::cout << std::left << std::setw(20) << "title" << std::setw(20) <<
        "sponsor" << std::setw(20) << "participator" << std::setw(20) <<
        "start time" << std::setw(20) << "end time" << std::endl;
    while (it != mt.end()) {
        std::cout << std::left << std::setw(20) << it->getTitle() << std::setw(20) <<
            it->getSponsor() << std::setw(20) << it->getParticipator() << std::setw(20) <<
            Date::dateToString(it->getStartDate()) << std::setw(20) << Date::dateToString(it->getEndDate()) << std::endl;
        it++;
    }
    std::cout << std::endl;
}

void AgendaUI::listAllParticipateMeetings(void) {
    std::cout << std::endl;
    std::list<Meeting> mt = agendaService_.listAllParticipateMeetings(userName_);
    std::list<Meeting>::iterator it = mt.begin();
    std::cout << "list all participator meetings" << std::endl;
    std::cout << std::endl;
    std::cout << std::left << std::setw(20) << "title" << std::setw(20) <<
        "sponsor" << std::setw(20) << "participator" << std::setw(20) <<
        "start time" << std::setw(20) << "end time" << std::endl;
    while (it != mt.end()) {
        std::cout << std::left << std::setw(20) << it->getTitle() << std::setw(20) <<
            it->getSponsor() << std::setw(20) << it->getParticipator() << std::setw(20) <<
            Date::dateToString(it->getStartDate()) << std::setw(20) << Date::dateToString(it->getEndDate()) << std::endl;
        it++;
    }
    std::cout << std::endl;
}

void AgendaUI::queryMeetingByTitle(void) {
    std::cout << std::endl;
    std::cout << "[query meeting] [title] :" << std::endl;
    std::cout << "[query meeting] ";
    std::string tt;
    std::cin >> tt;
    std::cout << std::endl;
    std::list<Meeting> mt = agendaService_.meetingQuery(userName_, tt);
    std::list<Meeting>::iterator it = mt.begin();
    std::cout << std::left << std::setw(20) <<
        "sponsor" << std::setw(20) << "participator" << std::setw(20) <<
        "start time" << std::setw(20) << "end time" << std::endl;
    while (it != mt.end()) {
        std::cout << std::left << std::setw(20) <<
            it->getSponsor() << std::setw(20) << it->getParticipator() << std::setw(20) <<
            Date::dateToString(it->getStartDate()) << std::setw(20) << Date::dateToString(it->getEndDate()) << std::endl;
        it++;
    }
    std::cout << std::endl;
}

void AgendaUI::queryMeetingByTimeInterval(void) {
    std::cout << std::endl;
    std::cout << "[query meetings] [start time<yyyy-mm-dd/hh:mm>] [end time<yyyy-mm-dd/hh:mm>] :" << std::endl;
    std::cout << "[query meetings] ";
    std::string sd, ed;
    std::cin >> sd >> ed;
    std::cout << std::endl;
    std::cout << "[query meetings]";
    std::list<Meeting> mt = agendaService_.meetingQuery(userName_, sd, ed);
    std::list<Meeting>::iterator it = mt.begin();
    std::cout << std::left << std::setw(20) << "title" << std::setw(20) <<
        "sponsor" << std::setw(20) << "participator" << std::setw(20) <<
        "start time" << std::setw(20) << "end time" << std::endl;
    while (it != mt.end()) {
        std::cout << std::left << std::setw(20) << it->getTitle() << std::setw(20) <<
            it->getSponsor() << std::setw(20) << it->getParticipator() << std::setw(20) <<
            Date::dateToString(it->getStartDate()) << std::setw(20) << Date::dateToString(it->getEndDate()) << std::endl;
        it++;
    }
    std::cout << std::endl;
}

void AgendaUI::deleteMeetingByTitle(void) {
    std::cout << std::endl;
    std::cout << "[delete meeting] [title]" << std::endl;
    std::cout << "[delete meeting] ";
    std::string tt;
    std::cin >> tt;
    std::cout << std::endl;
    if (agendaService_.deleteMeeting(userName_, tt)) {
        std::cout << "[delete meeting by title] succeed!" << std::endl;
    } else {
        std::cout << "[error] delete meeting fail!" << std::endl;
    } 
    std::cout << std::endl;
}

void AgendaUI::deleteAllMeetings(void) {
    std::cout << std::endl;
    if (agendaService_.deleteAllMeetings(userName_)) {
        std::cout << "[delete all meetings] succeed!" << std::endl;
    } else {
        std::cout << "[error] delete all meetings fail!" << std::endl;
    }
    std::cout << std::endl;
}

void AgendaUI::printMeetings(std::list<Meeting> meetings) {}

// dates
// std::string userName_;
// std::string userPassword_;
// AgendaService agendaService_;

