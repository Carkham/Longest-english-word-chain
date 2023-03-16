//
// Created by 13021 on 2023/3/16.
//
#include "gtest/gtest.h"
#include "IOUtil.h"

TEST(IOUtil, output_test) {
    std::string file_name("outfile_1.txt");
    char **results = new char *[]{
        "This_Is4TeSt_h?h"
    };
    int result_num = 1;
    IOUtil::output_word_chain_to_file(file_name.c_str(), results, result_num, false);
    IOUtil::output_word_chain_to_file(file_name.c_str(), results, result_num, true);
    delete[] results;

    char **words = new char * [100];
    int word_num;
    char **expected_words = new char * []{
        "this",
        "is",
        "test",
        "h",
        "h"
    };
    int expected_num = 5;
    word_num = IOUtil::get_word_from_file(file_name.c_str(), words);
    EXPECT_EQ(expected_num, word_num);
    for (int i = 0; i < word_num; ++i) {
        EXPECT_STREQ(expected_words[i], words[i]);
    }
    for (int i = 0; i < word_num; ++i) {
        delete[] words[i];
    }
    delete[] words;
    delete[] expected_words;
}

TEST(IOUtil, input_test) {
    // no such file
    int ret = IOUtil::get_word_from_file("", nullptr);
    EXPECT_EQ(0, ret);
}