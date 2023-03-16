//
// Created by 13021 on 2023/3/16.
//

#include "gtest/gtest.h"
#include "Core.h"
#define testWordSize 100
#define testResultSize 10000

using namespace std;
TEST(CoreTest, gen_chains_all) {
    int result_num;
    char **results = new char * [testResultSize];
    // sample 1
    int len = 4;
    char **words = new char *[]{"woo", "oom", "moon", "noox"};
    int expected_result_num = 6;
    char **expected_results = new char *[]{
            "woo oom",
            "moon noox",
            "oom moon",
            "woo oom moon",
            "oom moon noox",
            "woo oom moon noox",
    };
    result_num = Core::gen_chains_all(words, len, results);
    EXPECT_EQ(expected_result_num, result_num);
    for (int i = 0; i < result_num; ++i) {
        EXPECT_STREQ(expected_results[i], results[i]);
    }
    for (int i = 0; i < result_num; ++i) {
        delete results[i];
    }
    delete[] words;
    delete[] expected_results;

    // sample 2 no input
    len = 0;
    words = nullptr;
    result_num = Core::gen_chains_all(words, len, results);
    EXPECT_EQ(result_num, len);

    // sample 3 loop exception
    len = 2;
    words = new char *[]{"ab", "ba"};
    EXPECT_ANY_THROW(Core::gen_chains_all(words, len, results));
    delete[] words;

    delete[] results;
}

TEST(CoreTest, gen_chain_word) {
    int result_num;
    char **results = new char * [testResultSize];
    // sample 1
    int len = 11;
    char **words = new char * []{
            "algebra",
            "apple",
            "zoo",
            "elephant",
            "under",
            "fox",
            "dog",
            "moon",
            "leaf",
            "trick",
            "pseudopseudohypoparathyroidism"};
    int expected_result_num = 4;
    char **expected_results = new char * []{
            "algebra",
            "apple",
            "elephant",
            "trick"
    };
    result_num = Core::gen_chain_word(words, len, results, 0, 0, 0, false);
    EXPECT_EQ(expected_result_num, result_num);
    for (int i = 0; i < result_num; ++i) {
        EXPECT_STREQ(expected_results[i], results[i]);
    }

    for (int i = 0; i < result_num; ++i) {
        delete results[i];
    }
    delete[] expected_results;


    // sample 2 param test
    expected_result_num = 3;
    expected_results = new char * []{
            "algebra",
            "apple",
            "elephant"
    };
    result_num = Core::gen_chain_word(words, len, results, 'a', 't', 't', false);

    EXPECT_EQ(expected_result_num, result_num);
    for (int i = 0; i < result_num; ++i) {
        EXPECT_STREQ(expected_results[i], results[i]);
    }

    for (int i = 0; i < result_num; ++i) {
        delete results[i];
    }
    delete[] expected_results;
    delete[] words;


    // sample 3 enable loop
    len = 2;
    words = new char * []{"ab", "ba"};
    expected_result_num = 2;
    expected_results = new char * []{"ab", "ba"};
    result_num = Core::gen_chain_word(words, len, results, 'a', 'a', 0, true);

    EXPECT_EQ(expected_result_num, result_num);
    for (int i = 0; i < result_num; ++i) {
        EXPECT_STREQ(expected_results[i], results[i]);
    }

    for (int i = 0; i < result_num; ++i) {
        delete results[i];
    }
    delete[] expected_results;


    // sample 4

    delete[] results;
}

TEST(CoreTest, gen_chain_char) {
    int result_num;
    char **results = new char * [testResultSize];
    // sample 1
    int len = 11;
    char **words = new char * []{
            "algebra",
            "apple",
            "zoo",
            "elephant",
            "under",
            "fox",
            "dog",
            "moon",
            "leaf",
            "trick",
            "pseudopseudohypoparathyroidism"};
    int expected_result_num = 2;
    char **expected_results = new char * []{
            "pseudopseudohypoparathyroidism",
            "moon"
    };

    result_num = Core::gen_chain_char(words, len, results, 0, 0, 0, false);
    ASSERT_EQ(expected_result_num, result_num);
    for (int i = 0; i < result_num; ++i) {
        EXPECT_STREQ(expected_results[i], results[i]);
    }

    for (int i = 0; i < result_num; ++i) {
        delete results[i];
    }
    delete[] expected_results;


    // sample 2
    expected_result_num = 3;
    expected_results = new char * []{
            "algebra",
            "apple",
            "elephant"
    };
    result_num = Core::gen_chain_word(words, len, results, 'a', 't', 't', false);

    EXPECT_EQ(expected_result_num, result_num);
    for (int i = 0; i < result_num; ++i) {
        EXPECT_STREQ(expected_results[i], results[i]);
    }

    for (int i = 0; i < result_num; ++i) {
        delete results[i];
    }
    delete[] expected_results;
    delete[] words;


    // sample 3 enable loop
    len = 2;
    words = new char * []{"ab", "ba", "ab", "bdefghizk"};
    expected_result_num = 2;
    expected_results = new char * []{"ab", "ba"};
    result_num = Core::gen_chain_word(words, len, results, 0, 0, 0, true);

    EXPECT_EQ(expected_result_num, result_num);
    for (int i = 0; i < result_num; ++i) {
        EXPECT_STREQ(expected_results[i], results[i]);
    }

    for (int i = 0; i < result_num; ++i) {
        delete results[i];
    }
    delete[] expected_results;
    delete[] words;

    delete[] results;
}