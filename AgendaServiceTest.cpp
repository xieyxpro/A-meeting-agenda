/*************************************************************************
	> File Name: AgendaServiceTest.cpp
	> Author: LY
	> Mail: ly.franky@gmail.com
	> Created Time: Wednesday, July 02, 2014 PM04:25:54 HKT
 ************************************************************************/

#include <gtest/gtest.h>
#include "AgendaService.h"
#include "Storage.h"
#include <list>
#include <iostream>
#include <string>

TEST(AgendaServiceTest, lyly) {
    AgendaService agen;
    std::string d1 = "2014-07-7/0:0";
    std::string d2 = "2014-06-5/0:0";
    std::string d3 = "2014-06-4/0:0";
    EXPECT_FALSE(agen.userLogIn("ly", "ly"));
    EXPECT_FALSE(agen.deleteUser("ly", "233"));
    EXPECT_TRUE(agen.userRegister("ly", "233", "233", "233"));
    EXPECT_TRUE(agen.userLogIn("ly", "233"));
    //EXPECT_TRUE(agen.listAllUsers().size() == 7);
    EXPECT_TRUE(agen.deleteUser("ly", "233"));
    //EXPECT_TRUE(agen.listAllUsers().size() == 6);

    EXPECT_TRUE(agen.userRegister("ly", "233", "233", "233"));
    EXPECT_TRUE(agen.createMeeting("ly", "t", "ly", d2, d1));
    EXPECT_TRUE(agen.meetingQuery("ly", "t").size() == 1);
    EXPECT_TRUE(agen.meetingQuery("ly", d2, d1).size() == 1);
    EXPECT_TRUE(agen.listAllMeetings("ly").size() == 1);
    EXPECT_TRUE(agen.deleteAllMeetings("ly"));

}

