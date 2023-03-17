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

TEST(CoreTest, gen_chain_word_4) {
    char **results = new char *[testResultSize];
    const char *words[] = {
            "aa",
            "cd",
            "bf",
            "word",
            "chain",
            "na",
            "acd",
    };
    const char *expected_results[] = {
            "chain", "na", "aa", "acd"
    };
    int result_num = Core::gen_chain_word(const_cast<char **>(words), 7, results, 0, 0, 0, false);
    EXPECT_EQ(result_num, 4);
    results_cmp(expected_results, results, result_num);
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

TEST(CoreTest, gen_chain_char_example4) {
    // sample 4 loop exception
    char **results = new char *[testResultSize];
    // sample 1
    int len = 4;
    const char *words[] = {"ab", "ba", "ab", "bdefghizk"};

    EXPECT_ANY_THROW(Core::gen_chain_char(const_cast<char **>(words), len, results, 0, 0, 0, false));
    delete[] results;
}


TEST(CoreTest, gen_chain_char_example5) {
    // sample 5 fully connected
    char **results = new char *[testResultSize];
    int len = 325;
    const char *words[] = {
            "aJuozLb","byttLVc","cPDdfHd","dNpjzse","exsDfuf","fJRHpFg","gFcwqAh","hkalThi","iTZflZj","jTzlPNk","khHCpol","lVukyJm","mXCuCwn","nZGnnmo","oGfffGp","pmlUYNq","qTStsxr","rxvGuPs","sWkdBHt","ttufpiu","uWzNNjv","vfOwraw","wrAaYEx","xoQzqPy","yatxhvz","bJGtrkc","cGqdsbd","dVGOXWe","eqVFRzf","fOVToig","ggxZluh","hcKzWHi","ifsXizj","jpcvjfk","keIlIRl","lClVuZm","mGWreon","nKFlRVo","oqJfjcp","pGTtMCq","qssMxar","rmljxls","sKVgxNt","tEFbJbu","usqAVzv","vxwIJTw","wwJVLSx","xUFbrdy","yuIJgez","cAMBwRd","dMNJGYe","eszRBIf","fQZjmsg","gPXpzbh","hbkyFbi","ioHuKRj","jaimfBk","kBMnGTl","lcHtkPm","mGqUSEn","nApMovo","oBoZEep","pTgwBrq","qUhQZYr","rXOcGus","sLkeWit","tCochFu","urqmuwv","vJHatww","wmdoDSx","xCwouUy","yVJIJQz","dYftEhe","eiMpLMf","fFeeqXg","gqqByVh","hTCwoKi","intXwdj","jbEhXhk","ksdhpel","lVkULmm","mwAXHTn","nfbgoXo","oGJOqRp","pyMqHIq","qelaoqr","rLzDeps","sJfDKRt","tchGSdu","uYpYrwv","vIpYMaw","wBDvMtx","xtZRDzy","yXYXqVz","eyhLzyf","fYuiRMg","gxQVrMh","hAuQoGi","iSroFLj","jEjCIqk","kiBiVil","lpgicPm","mRpoujn","nhZxlgo","oPIeoyp","pFEyYVq","qyemgdr","rheCqos","sbcukZt","tMHmZHu","uPXdAMv","vWalyIw","wbiqVdx","xmCwgFy","yCypBFz","fZGkMzg","gYasNNh","hoqNsxi","ivDYkrj","jfkWTvk","kiYuFbl","lwAvBBm","mycMzdn","nVpqzLo","oMSixHp","poLaAcq","quYisTr","rYsCnOs","sWSXyPt","tGzjKDu","uwxjMuv","vUSeIKw","wBiLxBx","xbCNMKy","yvCAFSz","gmHMMOh","hlrVtBi","iBjRywj","jkThPdk","kfcFdWl","lRScUim","mFxMxZn","nohcwio","oIGbTap","pWJXQLq","qKBLFJr","rtCITWs","svSNfGt","tBdCoVu","uSylcov","vemFoJw","wkQBptx","xiAfcQy","yrBWadz","hLWdiZi","iZsJscj","jlgwKNk","kNzxgCl","lAlqsJm","mYYorTn","nHvzRUo","okbGYXp","poLvGLq","qkOuxNr","rJwhSQs","shNXDIt","tKMghju","uCTFgQv","venoVFw","wFWgNEx","xtdcWay","yDmqWzz","iQhZPXj","jAQToYk","klmYnHl","lTRvhPm","meeImWn","nSXOkYo","oQwYbqp","pVlZrLq","qAbNthr","rMMVgWs","sCmkWFt","tABQmQu","uPCLFlv","vHehcqw","wuDIvIx","xBStBPy","yRjMNgz","jEwVTrk","kwlGvxl","lraFmRm","mCSNxyn","nyusFEo","osJOQcp","pmQnGUq","qtGGRVr","rwChrFs","sAwBpZt","tbkSEtu","uiLkIbv","vwCQGkw","wLyjtQx","xDgwUPy","yIoIMLz","kRgjePl","lOAUDWm","mDcQecn","nbhtlWo","oIrMaFp","pktAfpq","qDgcUEr","rVTjIbs","sEihoct","tXCkSau","uBDAHcv","vIGyPyw","wCZDpMx","xLXUIyy","yVNWmSz","lQewKnm","mCkhKIn","nMbiZHo","oymyrYp","pMrfupq","qXzpSfr","rRaFBHs","srMiLwt","tzWYmgu","ueirexv","vwQbqIw","wkToYgx","xGZOCdy","yafxwMz","mSGbWNn","nAPcheo","oBLzsrp","pNLgkGq","qEktitr","rEYvsvs","sRUrXpt","tzHBGOu","uUjSKRv","vWBrnEw","wASKbex","xRZxXUy","yGKfzGz","nIdkdjo","oZCRbLp","pUropwq","quCxeQr","rwBUUCs","smCYZot","tHQgzlu","ulZcWHv","vtefgXw","wCMWEJx","xkQBLEy","yQTihVz","oRMvadp","pIYuqaq","qntxyar","rcIuYus","srkIdtt","tUESawu","uXrjnCv","vgLvYEw","wTAcbcx","xQtpxxy","yZasttz","pWLwIVq","qySOgor","rmWpzqs","sgNxwxt","tcIyuku","uDkIJPv","vqwlfvw","wqdpIix","xcKERLy","yeLWpBz","qmBtHTr","rkVIurs","syLdLSt","tXzJcuu","uaPTLBv","vaMMTYw","wmkJUgx","xqbGzky","yzEdFfz","rlQaYts","shEHCVt","tWPAmru","unxsuSv","vyFSMow","wTjvLMx","xzXXAQy","yZULeAz","sezwJCt","tRGZwKu","uERcmEv","vrTxzaw","wJAbVtx","xMHiuKy","yzcfbxz","tJFXqBu","udIambv","vspFpbw","wAynyxx","xKtEday","yFawrpz","ujfOKlv","vhiYBiw","wqRKMCx","xgpZZLy","yGMfvbz","vwvnUSw","wrtEzZx","xyrzSYy","yfXAMXz","wigfeex","xYmEXpy","yUYcFVz","xVtRhBy","yrElhfz","ymquKcz"
    };

    int result_num = Core::gen_chain_char(const_cast<char **>(words), len, results, 0, 0, 0, false);
    EXPECT_EQ(result_num, 25);
}