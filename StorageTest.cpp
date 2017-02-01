/*************************************************************************
	> File Name: StorageTest.cpp
	> Author: LY
	> Mail: ly.franky@gmail.com
	> Created Time: Tuesday, July 01, 2014 PM04:14:00 HKT
 ************************************************************************/

#include <gtest/gtest.h>
#include <iostream>
#include "Storage.h"
#include "Date.h"
#include "Meeting.h"
#include "User.h"

TEST(StorageTest, CRUD) {
    Storage* i = Storage::getInstance();
    User user("ly", "ly", "ly", "ly");
    i->createUser(user);
    i->createUser(user);
    i->createUser(user);
    i->createUser(user);
    Date date1(1999, 2, 2, 2, 2);
    Meeting mt("ly", "ly", date1, date1, "ly");
    i->createMeeting(mt);
    i->createMeeting(mt);
    i->createMeeting(mt);
    i->createMeeting(mt);
    EXPECT_TRUE(i->queryUser([](const User& u){
        return u.getName() == "ly";
    }).size() == 5);
    EXPECT_TRUE(i->updateUser([](const User& u){
        return u.getName() == "ly";
    }, [](User& pp){
        pp.setName("2333");
    }) == 5);
    EXPECT_TRUE(i->deleteUser([](const User& u){
        return u.getName() == "2333";
    }) == 5);
    EXPECT_TRUE(i->deleteMeeting([](const Meeting& m){
        return m.getTitle() == "ly"; 
    }) == 4);
    delete i;
}

