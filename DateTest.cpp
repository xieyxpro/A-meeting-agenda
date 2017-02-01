/*************************************************************************
	> File Name: DateTest.cpp
	> Author: LY
	> Mail: ly.franky@gmail.com
	> Created Time: Tuesday, July 01, 2014 PM02:34:45 HKT
 ************************************************************************/

#include <gtest/gtest.h>
#include <string>
#include "Date.h"

TEST(DateTest, stringToDate) {
    Date date1(2013, 2, 30, 1, 1);
    EXPECT_FALSE(Date::isValid(date1));
    Date date2(2013, 2, 20, 1, 1);
    EXPECT_TRUE(Date::isValid(date2));
    Date date3(2013, 2, 30, 1, 1);
    EXPECT_TRUE(date1 == date3);
    EXPECT_TRUE(date1 > date2);
    EXPECT_TRUE(date1 >= date2);
    EXPECT_FALSE(date2 >= date1);
    Date date4 = date1;
    EXPECT_TRUE(date4 == date1);
    date2 = date1;
    EXPECT_TRUE(date2 == date3);
    std::string str = "2012-07-19/20:51";
    Date date6 = Date::stringToDate(str);
    Date date5(2012, 7, 19, 20, 51);
    EXPECT_TRUE(date6 == date5);
    std::string str2 = Date::dateToString(date5);
    EXPECT_TRUE(str2 == str);
    std::string str3 = "2013-03-3/1:0";
    Date date7(2013, 3, 3, 1, 0);
    EXPECT_TRUE(Date::stringToDate(str3) == date7);
    Date date8(1111, 11, 11, 11, 11);
    Date date9(1111, 11, 11, 12, 0);
    Date date10(1111, 11, 12, 11, 11);
    EXPECT_TRUE(date9 > date8 && date9 < date10);
    EXPECT_TRUE(date9 > date8);
    EXPECT_TRUE(date9 < date10);
}

