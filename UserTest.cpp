/*************************************************************************
	> File Name: UserTest.cpp
	> Author: LY
	> Mail: ly.franky@gmail.com
	> Created Time: Tuesday, July 01, 2014 PM03:38:58 HKT
 ************************************************************************/

#include <gtest/gtest.h>
#include <string>
#include "User.h"

TEST(UserTest, getName) {
    User user1("233", "asdasd", "weqwe,", "156456451");
    EXPECT_TRUE(user1.getName() == "233");
    user1.setName("ly");
    EXPECT_TRUE(user1.getName() == "ly");
    user1.setPassword("11");
    EXPECT_TRUE(user1.getPassword() == "11");
    user1.setEmail("222");
    EXPECT_TRUE(user1.getEmail() == "222");
    user1.setPhone("13333");
    EXPECT_TRUE(user1.getPhone() == "13333");
}

