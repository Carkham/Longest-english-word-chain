//
// Created by AORUS on 2023/3/11.
//
#include <ArgParser.h>
#include <Core.h>
#include <IOUtil.h>

#include <string>
#include <vector>
#include <iostream>
#define maxWordsNum 10000
#define maxResultsNum 20000

void release(char **words, int word_num, char **results, int result_num) {
    for (int i = 0; i < word_num; ++i) {
        if (results[i] != nullptr) {
            delete[] words[i];
        }
    }
    delete[] words;
    for (int i = 0; i < result_num; ++i) {
        if (results[i] != nullptr) {
            delete[] results[i];
        }
    }
    delete[] results;
}

int main(int argc, char *argv[]) {
    ArgParser parser(argc, argv, "nwch:t:j:r");
    char head = 0, tail = 0, disallowed_head = 0, function = 0;
    bool enable_loop = false;
    int word_num = 0, result_num = 0;
    std::string input_file_name;


    char **words = new char *[maxWordsNum]();
    char **results = new char *[maxResultsNum]();
    try {
        ArgParser::parse_arg(parser, head, tail, disallowed_head, enable_loop, function, input_file_name);
        word_num = IOUtil::get_word_from_file(input_file_name.c_str(), words);
    } catch (std::exception &e) {
        fprintf(stderr, "%s", e.what());
        release(words, word_num, results, result_num);
        return -1;
    }
    try {
        switch (function) {
            case 'n':
                result_num = Core::gen_chains_all(words, word_num, results);
                break;
            case 'w':
                result_num = Core::gen_chain_word(words, word_num, results, head, tail, disallowed_head, enable_loop);
                break;
            case 'c':
                result_num = Core::gen_chain_char(words, word_num, results, head, tail, disallowed_head, enable_loop);
                break;
            default:
                throw std::invalid_argument("Invalid function option");
        }
        if (function == 'n') {
            std::cout << result_num << std::endl;
            for (int i = 0; i < result_num; ++i) {
                std::cout << std::string(results[i]) << std::endl;
            }
        } else {
            IOUtil::output_word_chain_to_file("solution.txt", results, result_num, function == 'n');
        }
    } catch (std::exception &e) {
        fprintf(stderr, "%s\n", e.what());
        release(words, word_num, results, result_num);
        return -1;
    }
    release(words, word_num, results, result_num);
    return 0;
}