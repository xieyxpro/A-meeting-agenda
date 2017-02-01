/*************************************************************************
	> File Name: MeetingTest.cpp
	> Author: LY
	> Mail: ly.franky@gmail.com
	> Created Time: Tuesday, July 01, 2014 PM04:04:55 HKT
 ************************************************************************/

#include <gtest/gtest.h>
#include <string>
#include "Meeting.h"
#include "Date.h"

TEST(MeetingTest, getEndDate) {
    Date date1(2014, 7, 1, 22, 11);
    Date date2(2014, 5, 3, 1, 1);
    Meeting meeting("ly", "lyly", date1, date2, "tt");
    meeting.setSponsor("tq");
    EXPECT_TRUE(meeting.getSponsor() == "tq");
    meeting.setParticipator("233");
    EXPECT_TRUE("233" == meeting.getParticipator());
    EXPECT_TRUE(meeting.getStartDate() == date1);
    EXPECT_TRUE(meeting.getEndDate() == date2);
}

