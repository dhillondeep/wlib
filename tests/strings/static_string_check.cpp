/**
 * @file static_string_check.cpp
 * @brief Unit Testing for StaticString class present in Wlib library
 *
 * @author Deep Dhillon
 * @date November 11, 2017
 * @bug No known bugs
 */

#include <gtest/gtest.h>
#include <wlib/strings/String.h>

using namespace wlp;

TEST(static_string_test, ctor_test) {
    String8 string1{"helloooo"};    // text given
    String8 string2;                // no text
    String8 string3{string1};       // string object give

    ASSERT_EQ(8u, string1.capacity());
    ASSERT_EQ(8u, string2.capacity());
    ASSERT_EQ(8u, string3.capacity());

    ASSERT_EQ(8u, string1.length());
    ASSERT_EQ(0u, string2.length());
    ASSERT_EQ(8u, string3.length());

    ASSERT_STREQ("helloooo", string1.c_str());
    ASSERT_STREQ("", string2.c_str());
    ASSERT_STREQ("helloooo", string3.c_str());
}

TEST(static_string_test, add_operators) {
    String16 string1{"deep"};
    String16 string2{"bye"};
    String16 string3{"hi"};
    String16 string4{"yo"};
    String16 string5{"yooooooooooooooo"};
    char char1 = '7';
    char array1[] = "hell";
    char array2[] = "123456789";

    // object to object addition
    ASSERT_STREQ("deepbye", (string1 + string2).c_str());
    ASSERT_STREQ("deepbyeyoooooooo", (string1 + string2 + string5).c_str());

    // object plus character array addition
    ASSERT_STREQ( "hibrooooooo", (string3 + "brooooooo").c_str());
    ASSERT_STREQ("123456789000045b", ("123456789000045" + string2).c_str());
    ASSERT_STREQ("helldeep", (array1 + string1).c_str());
    ASSERT_STREQ("deep123456789hel", (string1 + array2 + array1).c_str());

    // individual char
    ASSERT_STREQ("7deep", (char1 + string1).c_str());
    ASSERT_STREQ("deep77", (string1 + char1 + char1).c_str());
    ASSERT_STREQ(string5.c_str(), (string5 + char1).c_str());
}

TEST(static_string_test, concat_operator) {
    String16 string1{"deep"};
    String16 string2{"bye"};
    String16 string3{"hi"};
    String16 string4{"yo"};
    String16 string5{"yooooooooooooooo"};
    char char1 = '7';
    char array[] = "hell";

    // object to object append
    ASSERT_STREQ("deepbye", (string1 += string2).c_str());
    ASSERT_STREQ("deepbyebyeyo", (string1 += string2 += string4).c_str());
    ASSERT_STREQ(string5.c_str(), (string5 += string1).c_str());

    // object plus character str
    ASSERT_STREQ("hibrooooooooooo", (string3 += "brooooooooooo").c_str());
    ASSERT_STREQ("yo1234567890000", (string4 += "1234567890000").c_str());
    ASSERT_STREQ("byeyohell", (string2 += array).c_str());
    ASSERT_STREQ(string5.c_str(), (string5 += "hhjsdjhs").c_str());

    // individual char
    ASSERT_STREQ("hibrooooooooooo7", (string3 += char1).c_str());
    ASSERT_STREQ(string3.c_str(), (string3 += 'd').c_str());
}

TEST(static_string_test, concat_append_push_back) {
    String16 string1{"deep"};
    String16 string2{"bye"};
    String16 string3{"hi"};
    String16 string4{"yo"};
    String16 string5{"yooooooooooooooo"};
    char char1 = '7';
    char array[] = "hell";

    // object to object append
    ASSERT_STREQ("deepbye", (string1.append(string2)).c_str());
    ASSERT_STREQ("deepbyebyeyo", (string1.append(string2).append(string4)).c_str());
    ASSERT_STREQ(string5.c_str(), (string5.append(string1)).c_str());

    // object plus character str
    ASSERT_STREQ("hibrooooooooooo", (string3.append("brooooooooooo")).c_str());
    ASSERT_STREQ("yo1234567890000", (string4.append("1234567890000")).c_str());
    ASSERT_STREQ("byehell", (string2.append(array)).c_str());
    ASSERT_STREQ(string5.c_str(), (string5.append("hhjsdjhs")).c_str());

    // individual char
    string3.push_back(char1);
    ASSERT_STREQ("hibrooooooooooo7", string3.c_str());
    String16 string6{string3};
    string6.push_back('d');
    ASSERT_STREQ(string3.c_str(), string6.c_str());
}

TEST(static_string_test, equal_to_operator) {
    String16 string1{"deep"};
    String16 string2{"bye"};
    String16 string3{"hi"};
    String16 string4{"y"};

    ASSERT_FALSE(string1 == string2);
    ASSERT_TRUE(string1 == string1);
    ASSERT_TRUE(string1 == "deep");
    ASSERT_TRUE(string4 == 'y');
    ASSERT_TRUE("deep" == string1);
    ASSERT_TRUE('y' == string4);
}

TEST(static_string_test, compare_methods) {
    String16 string1{"deep"};
    String16 string2{"bye"};
    String16 string3{"hi"};
    String16 string4{"y"};
    String16 string5{"ye"};

    ASSERT_LT(string1.compare(string4), 0);
    ASSERT_GT(string3.compare(string2), 0);
    ASSERT_LT(string4.compare(string5), 0);
    ASSERT_EQ(string1.compare(string1), 0);
    ASSERT_GT(string1.compare("dee"), 0);
    ASSERT_GT(string2.compare('a'), 0);
}

TEST(static_string_test, access_chars) {
    const String16 string1{"deep"};
    const String16 string2{"bye"};
    String16 string3{"hi"};
    String16 string4{"y"};

    ASSERT_TRUE(string1[0] == 'd');
    ASSERT_TRUE(string1[4] == 'p');
    ASSERT_TRUE(string3[1] == 'i');
    ASSERT_TRUE(string3[3] == 'i');
    ASSERT_TRUE(string2[2] == 'e');

    ASSERT_TRUE(string1.at(0) == 'd');
    ASSERT_TRUE(string1.at(7) == 'p');
    ASSERT_TRUE(string4.at(6) == 'y');
    ASSERT_FALSE(string3.at(1) == 'd');

    ASSERT_TRUE(string1.front() == 'd');
    ASSERT_TRUE(string2.front() == 'b');
    ASSERT_TRUE(string3.front() == 'h');
    ASSERT_TRUE(string4.front() == 'y');

    ASSERT_TRUE(string1.back() == 'p');
    ASSERT_TRUE(string2.back() == 'e');
    ASSERT_TRUE(string3.back() == 'i');
    ASSERT_TRUE(string4.back() == 'y');
}

TEST(static_string_test, clear_string) {
    String8 string1{"deep"};
    String8 string2{"bye"};
    String8 string3{"hi"};
    String8 string4{"y"};

    string1.clear();
    string2.clear();
    string3.clear();
    string4.clear();

    ASSERT_EQ(0u, string1.length());
    ASSERT_EQ(0u, string2.length());
    ASSERT_EQ(0u, string3.length());
    ASSERT_EQ(0u, string4.length());

    ASSERT_EQ(8u, string1.capacity());
    ASSERT_EQ(8u, string2.capacity());
    ASSERT_EQ(8u, string3.capacity());
    ASSERT_EQ(8u, string4.capacity());

    ASSERT_STREQ("", string1.c_str());
    ASSERT_STREQ("", string2.c_str());
    ASSERT_STREQ("", string3.c_str());
    ASSERT_STREQ("", string4.c_str());
}

TEST(static_string_test, assign_operator) {
    String16 string1{"deep"};
    String16 string2{"bye"};
    String16 string3{"hi"};
    String16 string4{"y"};

    string1 = string4;
    string2 = "deep2";
    string3 = 'c';

    ASSERT_STREQ(string4.c_str(), string1.c_str());
    ASSERT_STREQ("deep2", string2.c_str());
    ASSERT_STREQ("c", string3.c_str());
    ASSERT_STRNE("d", string4.c_str());
}

TEST(static_string_test, erase_popBack){
    String16 string1{"deep"};
    String16 string2{"bye"};
    String16 string3{"hi"};
    String16 string4{"y"};

    string1.erase(2);
    ASSERT_EQ(3u, string1.length());
    ASSERT_EQ(16u, string1.capacity());
    ASSERT_STREQ("dep", string1.c_str());

    string1.erase();
    ASSERT_EQ(2u, string1.length());
    ASSERT_STREQ("ep", string1.c_str());

    string2.erase(0);
    string2.erase(1);
    ASSERT_EQ(1u, string2.length());
    ASSERT_STREQ("y", string2.c_str());

    string2.erase(5);
    ASSERT_EQ(1u, string2.length());
    ASSERT_STREQ("y", string2.c_str());

    string2.erase();
    string2.erase();
    ASSERT_EQ(0u, string2.length());
    ASSERT_STREQ("", string2.c_str());

    string3.pop_back();
    string4.pop_back();
    ASSERT_EQ(1u, string3.length());
    ASSERT_STREQ("h", string3.c_str());
    ASSERT_EQ(0u, string4.length());
    ASSERT_STREQ("", string4.c_str());

    string4.pop_back();
    ASSERT_EQ(0u, string4.length());
    ASSERT_STREQ("", string4.c_str());
}

TEST(static_string_test, substring) {
    String16 string1{"deep"};
    String16 string2;

    ASSERT_STREQ("de", string1.substr(0, 2).c_str());
    ASSERT_STREQ("deep", string1.substr(0, 4).c_str());
    ASSERT_STREQ("e", string1.substr(2, 1).c_str());
    ASSERT_STREQ("", string2.substr(0, 5).c_str());
    ASSERT_STREQ("deep", string1.substr(15, 2).c_str());
    ASSERT_STREQ("ep", string1.substr(2, 8).c_str());
}
