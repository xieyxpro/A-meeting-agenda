/*************************************************************************
	> File Name: AgendaService.cpp
	> Author: LY
	> Mail: ly.franky@gmail.com
	> Created Time: Tuesday, July 01, 2014 PM01:55:41 HKT
 ************************************************************************/

#include "Storage.h"
#include "AgendaService.h"
#include <list>
#include <string>

// public:

AgendaService::AgendaService() {
    storage_ = Storage::getInstance();
}

AgendaService::~AgendaService() {
    delete storage_;
}

bool AgendaService::userLogIn(std::string userName, std::string password) {
    return (!(storage_->queryUser([userName, password](const User& user){
        return user.getName() == userName && user.getPassword() == password;
    }).empty()));
}

bool AgendaService::userRegister(std::string userName, std::string password, std::string email, std::string phone) {
    if (!(storage_->queryUser([userName](const User& user){
        return user.getName() == userName;
    }).empty())) {
        return false;
    }
    User user(userName, password, email, phone);
    storage_->createUser(user);
    return true;
}

bool AgendaService::deleteUser(std::string userName, std::string password) {
    if (storage_->queryUser([userName, password](const User& user){
        return user.getName() == userName && user.getPassword() == password;
    }).empty()) {
        return false;
    }
    deleteAllMeetings(userName);
    storage_->deleteUser([userName, password](const User& user) {
        return (user.getName() == userName && user.getPassword() == password);
    });
    return true;
}   // a user can only delete itself

std::list<User> AgendaService::listAllUsers(void) {
    return storage_->queryUser([](const User& user){
        return true;
    });
}

bool AgendaService::createMeeting(std::string userName, std::string title, std::string participator, std::string startDate, std::string endDate) {
    if ((storage_->queryUser([userName](const User& user){
        return user.getName() == userName;
    }).empty())) return false;
    if ((storage_->queryUser([participator](const User& user){
        return user.getName() == participator;
    }).empty())) return false;
    Date sd = Date::stringToDate(startDate);
    Date ed = Date::stringToDate(endDate);
    if (!Date::isValid(sd)) return false;
    if (!Date::isValid(ed)) return false;
    if (sd >= ed) return false;
    std::list<Meeting> listMeeting(listAllMeetings(userName));
    std::list<Meeting>::iterator it = listMeeting.begin();
    while (it != listMeeting.end()) {
        if (it->getStartDate() > sd && it->getStartDate() < ed) return false;
        if (it->getEndDate() > sd && it->getEndDate() < ed) return false;
        if (it->getStartDate() <= sd && it->getEndDate() >= ed) return false;
        if (it->getTitle() == title) return false;
        it++;
    }
    std::list<Meeting> listMeeting2(listAllMeetings(participator));
    it = listMeeting2.begin();
    while (it != listMeeting2.end()) {
        if (it->getStartDate() > sd && it->getStartDate() < ed) return false;
        if (it->getEndDate() > sd && it->getEndDate() < ed) return false;
        if (it->getStartDate() <= sd && it->getEndDate() >= ed) return false;
        if (it->getTitle() == title) return false;
        it++;
    }
    Meeting meeting(userName, participator, sd, ed, title);
    storage_->createMeeting(meeting);
    return true;
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName, std::string title) {
    return storage_->queryMeeting([userName, title](const Meeting& meeting) {
        return (meeting.getSponsor() == userName && meeting.getTitle() == title);
    });
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName, std::string startDate, std::string endDate) {
    return storage_->queryMeeting([userName, startDate, endDate](const Meeting& meeting) {
        if (!(meeting.getSponsor() == userName || meeting.getParticipator() == userName)) return false;
        if (meeting.getStartDate() > Date::stringToDate(startDate) && meeting.getStartDate() < Date::stringToDate(endDate)) return true;
        if (meeting.getEndDate() > Date::stringToDate(startDate) && meeting.getEndDate() < Date::stringToDate(endDate)) return true;
        if (meeting.getStartDate() <= Date::stringToDate(startDate) && meeting.getEndDate() >= Date::stringToDate(endDate)) return true;
        return false;
    });
}

std::list<Meeting> AgendaService::listAllMeetings(std::string userName) {
    return storage_->queryMeeting([userName](const Meeting& meeting){
        return meeting.getSponsor() == userName || meeting.getParticipator() == userName;
    });
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(std::string userName) {
    return storage_->queryMeeting([userName](const Meeting& meeting){
        return meeting.getSponsor() == userName;
    });
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(std::string userName) {
    return storage_->queryMeeting([userName](const Meeting& meeting){
        return meeting.getParticipator() == userName;
    });
}

bool AgendaService::deleteMeeting(std::string userName, std::string title) {
    if ((storage_->queryUser([userName](const User& user){
        return user.getName() == userName;
    }).empty())) return false;
    if (storage_->queryMeeting([userName, title](const Meeting& m){
        return (m.getSponsor() == userName && m.getTitle() == title);
    }).empty()) {
        return false;
    }
    storage_->deleteMeeting([userName, title](const Meeting& meeting) {
        return (meeting.getSponsor() == userName && meeting.getTitle() == title);
    });
    return true;
}

bool AgendaService::deleteAllMeetings(std::string userName) {
    if ((storage_->queryUser([userName](const User& user){
        return user.getName() == userName;
    }).empty())) return false;
    if (storage_->queryMeeting([userName](const Meeting& m){
        return m.getSponsor() == userName || m.getParticipator() == userName;
    }).empty()) {
        return false;
    }
    storage_->deleteMeeting([userName](const Meeting& meeting) {
        return meeting.getSponsor() == userName || meeting.getParticipator() == userName;
    });
    return true;
}

void AgendaService::startAgenda(void) {}

void AgendaService::quitAgenda(void) {}

// private:
// Storage *storage_;

