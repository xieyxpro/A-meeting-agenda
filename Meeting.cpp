/*************************************************************************
	> File Name: Meeting.cpp
	> Author: LY
	> Mail: ly.franky@gmail.com
	> Created Time: Monday, June 30, 2014 PM05:25:05 HKT
 ************************************************************************/

#include "Date.h"
#include "Meeting.h"

Meeting::Meeting() {
    sponsor_ = participator_ = title_ = "";
}

Meeting::Meeting(std::string sponsor, std::string participator,
        Date startTime, Date endTime, std::string title) {
    sponsor_ = sponsor;
    participator_ = participator;
    startDate_ = startTime;
    endDate_ = endTime;
    title_ = title;
}

std::string Meeting::getSponsor(void) const {
    return sponsor_;
}

void Meeting::setSponsor(std::string sponsor) {
    sponsor_ = sponsor;
}

std::string Meeting::getParticipator(void) const {
    return participator_;
}

void Meeting::setParticipator(std::string participator) {
    participator_ = participator;
}

Date Meeting::getStartDate(void) const {
    return startDate_;
}

void Meeting::setStartDate(Date startTime) {
    startDate_.setYear(startTime.getYear());
    startDate_.setMonth(startTime.getMonth());
    startDate_.setDay(startTime.getDay());
    startDate_.setHour(startTime.getHour());
    startDate_.setMinute(startTime.getMinute());
}

Date Meeting::getEndDate(void) const {
    return endDate_;
}

void Meeting::setEndDate(Date endTime) {
    endDate_.setYear(endTime.getYear());
    endDate_.setMonth(endTime.getMonth());
    endDate_.setDay(endTime.getDay());
    endDate_.setHour(endTime.getHour());
    endDate_.setMinute(endTime.getMinute());
}

std::string Meeting::getTitle(void) const {
    return title_;
}

void Meeting::setTitle(std::string title) {
    title_ = title;
}

