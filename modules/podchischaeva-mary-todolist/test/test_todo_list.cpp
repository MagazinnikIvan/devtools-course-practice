// Copyright 2016 Podchischaeva Mary

#include <gtest/gtest.h>
#include <vector>
#include <stdexcept>

#include "TODOlist.h"

using std::vector;
using std::out_of_range;
using std::runtime_error;

TEST(TODOlist, Can_Create) {
    // Arrange
    TODOlist* list;

    // Act
    list = new TODOlist();

    // Assert
    EXPECT_NE(nullptr, list);

    // Free Memory
    delete list;
}

TEST(TODOlist, Can_Add_By_Item) {
    // Arrange
    TODOitem item;
    TODOlist list;

    item.setTitle("abc");

    // Act
    list.addItem(item);

    // Assert
    EXPECT_NE(-1, list.search("abc"));
}

TEST(TODOlist, Throw_When_Add_Existing_Title_By_Item) {
    // Arrange
    TODOitem item1;
    TODOitem item2;
    TODOlist list;

    item1.setTitle("abc");
    item2.setTitle("abc");

    // Act
    list.addItem(item1);

    // Assert
    EXPECT_THROW(list.addItem(item2), runtime_error);
}

TEST(TODOlist, Can_Add_By_Parameters) {
    // Arrange
    TODOlist list;

    // Act
    list.addItem("abc", 2);

    // Assert
    EXPECT_NE(-1, list.search("abc"));
}

TEST(TODOlist, Throw_When_Add_Existing_Title_By_Parameters) {
    // Arrange
    TODOlist list;

    // Act
    list.addItem("abc");

    // Assert
    EXPECT_THROW(list.addItem("abc"), runtime_error);
}

TEST(TODOlist, Can_Get_Size) {
    // Arrange
    TODOlist list;
    unsigned int expected = 1;

    // Act
    list.addItem("abc");

    // Assert
    EXPECT_EQ(expected, list.size());
}

TEST(TODOlist, Can_Get_Item) {
    // Arrange
    TODOlist list;

    // Act
    list.addItem("abc");
    list.addItem("defg");
    list.addItem("higk");

    // Assert
    EXPECT_EQ(list.getItem(1).getTitle(), "defg");
}

TEST(TODOlist, Throws_When_Get_By_Invalid_Pos) {
    // Arrange
    TODOlist list;

    // Act & Assert
    EXPECT_THROW(list.getItem(100500), out_of_range);
}

TEST(TODOlist, Can_Get_All) {
    // Arrange
    TODOlist list;
    vector<TODOitem> v;
    TODOitem temp;

    // Act
    temp.setTitle("abc");
    list.addItem(temp);
    v.push_back(temp);

    temp.setTitle("def");
    list.addItem(temp);
    v.push_back(temp);

    temp.setTitle("gik");
    list.addItem(temp);
    v.push_back(temp);

    // Assert
    EXPECT_EQ(list.getAll(), v);
}

TEST(TODOlist, Can_Get_By_Priority) {
    // Arrange
    TODOlist list;
    vector<TODOitem> v;
    TODOitem temp;

    // Act
    temp.setTitle("abc");
    temp.setPriority(1);
    list.addItem(temp);
    v.push_back(temp);

    temp.setTitle("def");
    temp.setPriority(2);
    list.addItem(temp);

    temp.setTitle("gik");
    temp.setPriority(1);
    list.addItem(temp);
    v.push_back(temp);

    // Assert
    EXPECT_EQ(list.getByPriority(1), v);
}

TEST(TODOlist, Can_Save_Load) {
    // Arrange
    TODOlist listForSave, listForLoad;
    vector<TODOitem> v;
    TODOitem temp;

    // Act
    temp.setTitle("abc");
    temp.setPriority(1);
    listForSave.addItem(temp);
    v.push_back(temp);

    temp.setTitle("def");
    temp.setPriority(2);
    listForSave.addItem(temp);
    v.push_back(temp);

    temp.setTitle("gik");
    temp.setPriority(1);
    listForSave.addItem(temp);
    v.push_back(temp);

    listForSave.save("todo.list");
    listForLoad.load("todo.list");

    // Assert
    EXPECT_EQ(listForLoad.getAll(), v);
}

TEST(TODOlist, Can_Delete_By_Pos) {
    // Arrange
    TODOlist list;
    vector<TODOitem> v;
    TODOitem temp;

    // Act
    temp.setTitle("abc");
    temp.setPriority(1);
    list.addItem(temp);
    v.push_back(temp);

    temp.setTitle("def");
    temp.setPriority(2);
    list.addItem(temp);

    temp.setTitle("gik");
    temp.setPriority(1);
    list.addItem(temp);
    v.push_back(temp);

    list.deleteItem(1);

    // Assert
    EXPECT_EQ(list.getAll(), v);
}

TEST(TODOlist, Throws_When_Delete_By_Invalid_Pos) {
    // Arrange
    TODOlist list;

    // Act
    list.addItem("abc");

    // Act & Assert
    EXPECT_THROW(list.deleteItem(100500), out_of_range);
}

TEST(TODOlist, Can_Sort_By_Priority) {
    // Arrange
    TODOlist list;
    TODOitem temp1;
    TODOitem temp2;
    vector<TODOitem> v;

    // Act
    temp1.setTitle("abc");
    temp1.setPriority(0);

    temp2.setTitle("def");
    temp2.setPriority(5);

    list.addItem(temp2);
    list.addItem(temp1);
    v.push_back(temp1);
    v.push_back(temp2);

    // Assert
    EXPECT_EQ(list.sortByPriority(), v);
}
