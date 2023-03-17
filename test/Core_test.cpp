//
// Created by 13021 on 2023/3/16.
//

#include "gtest/gtest.h"
#include "Core.h"
#include "algorithm"

#define testWordSize 100
#define testResultSize 1000

using namespace std;

void results_cmp(const char **expected_results, char **actual_results, int n) {
    vector<string> expected, actual;
    for (int i = 0; i < n; ++i) {
        expected.emplace_back(expected_results[i]);
        actual.emplace_back(actual_results[i]);
    }
    sort(expected.begin(), expected.end());
    sort(actual.begin(), actual.end());
    for (int i = 0; i < n; ++i) {
        EXPECT_EQ(expected[i], actual[i]);
    }
}

TEST(CoreTest, gen_chains_all_example1) {
    int result_num;
    char **results = new char *[testResultSize];
    // sample 1
    int len = 4;
    const char *words[] = {"woo", "oom", "moon", "noox"};
    int expected_result_num = 6;
    const char *expected_results[] = {
            "woo oom",
            "moon noox",
            "oom moon",
            "woo oom moon",
            "oom moon noox",
            "woo oom moon noox",
    };
    result_num = Core::gen_chains_all(const_cast<char **>(words), len, results);
    EXPECT_EQ(expected_result_num, result_num);
    results_cmp(expected_results, results, result_num);
    for (int i = 0; i < result_num; ++i) {
        delete[] results[i];
    }
    delete[] results;
}

TEST(CoreTest, gen_chains_all_example2) {
    // sample 2 no input
    char **results = new char *[testResultSize];
    int len = 0;
    const char *words[] = {};
    int result_num = Core::gen_chains_all(const_cast<char **>(words), len, results);
    EXPECT_EQ(result_num, len);
    delete[] results;
}

TEST(CoreTest, gen_chains_all_example3) {
    // sample 3 loop exception
    char **results = new char *[testResultSize];
    int len = 2;
    const char *words[] = {"ab", "ba"};
    EXPECT_ANY_THROW(Core::gen_chains_all(const_cast<char **>(words), len, results));
    delete[] results;
}

TEST(CoreTest, gen_chain_word_example1) {
    // sample 1
    char **results = new char *[testResultSize];
    int len = 11;
    const char *words[] = {
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
    const char *expected_results[] = {
            "algebra",
            "apple",
            "elephant",
            "trick"
    };
    int result_num = Core::gen_chain_word(const_cast<char **>(words), len, results, 0, 0, 0, false);
    EXPECT_EQ(expected_result_num, result_num);
    results_cmp(expected_results, results, result_num);

    for (int i = 0; i < result_num; ++i) {
        delete[] results[i];
    }
    delete[] results;
}

TEST(CoreTest, gen_chain_word_example2) {
    // sample 2 head tail
    char **results = new char *[testResultSize];
    int len = 11;
    const char *words[] = {
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
    int expected_result_num = 3;
    const char *expected_results[] = {
            "algebra",
            "apple",
            "elephant"
    };
    int result_num = Core::gen_chain_word(const_cast<char **>(words), len, results, 'a', 't', 't', false);
    EXPECT_EQ(expected_result_num, result_num);
    results_cmp(expected_results, results, result_num);

    for (int i = 0; i < result_num; ++i) {
        delete[] results[i];
    }
    delete[] results;
}

TEST(CoreTest, gen_chain_word_example3) {
    // sample 3 enable loop
    char **results = new char *[testResultSize];
    int len = 2;
    const char *words[] = {"ab", "ba"};
    int expected_result_num = 2;
    const char *expected_results[] = {"ab", "ba"};
    int result_num = Core::gen_chain_word(const_cast<char **>(words), len, results, 'a', 'a', 0, true);

    EXPECT_EQ(expected_result_num, result_num);
    results_cmp(expected_results, results, result_num);

    for (int i = 0; i < result_num; ++i) {
        delete[] results[i];
    }
    delete[] results;
}

TEST(CoreTest, gen_chain_char_example1) {
    int result_num;
    char **results = new char *[testResultSize];
    // sample 1
    int len = 11;
    const char *words[] = {
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
    const char *expected_results[] = {
            "pseudopseudohypoparathyroidism",
            "moon"
    };

    result_num = Core::gen_chain_char(const_cast<char **>(words), len, results, 0, 0, 0, false);
    EXPECT_EQ(expected_result_num, result_num);
    results_cmp(expected_results, results, result_num);

    for (int i = 0; i < result_num; ++i) {
        delete[] results[i];
    }
    delete[] results;
}

TEST(CoreTest, gen_chain_char_example2) {
    // sample 2
    int result_num;
    char **results = new char *[testResultSize];
    // sample 1
    int len = 11;
    const char *words[] = {
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
    int expected_result_num = 3;
    const char *expected_results[] = {
            "algebra",
            "apple",
            "elephant"
    };

    result_num = Core::gen_chain_char(const_cast<char **>(words), len, results, 'a', 't', 't', false);
    EXPECT_EQ(expected_result_num, result_num);
    results_cmp(expected_results, results, result_num);

    for (int i = 0; i < result_num; ++i) {
        delete[] results[i];
    }
    delete[] results;
}

TEST(CoreTest, gen_chain_char_example3) {
    // sample 3 enable loop
    int result_num;
    char **results = new char *[testResultSize];
    // sample 1
    int len = 4;
    const char *words[] = {"ab", "ba", "ab", "bdefghizk"};
    int expected_result_num = 3;
    const char *expected_results[] = {"ab", "ba", "bdefghizk"};

    result_num = Core::gen_chain_char(const_cast<char **>(words), len, results, 0, 0, 0, true);
    EXPECT_EQ(expected_result_num, result_num);
    results_cmp(expected_results, results, result_num);

    for (int i = 0; i < result_num; ++i) {
        delete[] results[i];
    }
    delete[] results;
}