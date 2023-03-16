//
// Created by AORUS on 2023/3/11.
//
#include <ArgParser.h>
#include <Core.h>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#define bufferSize 1024
#define myIsalpha(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
#define myTolower(c) (c <= 'Z' ? (c + 0x20) : (c))
#define maxWordsNum 10000
#define maxResultsNum 20000

int get_word_from_file(std::string input_file_name, char *words[]) {
    FILE *input_file = fopen(input_file_name.c_str(), "r");
    if (input_file == nullptr) {
        fprintf(stderr, "No such file %s\n", input_file_name.c_str());
    }
    bool is_word_start = true;
    int word_length = 0;
    char word[bufferSize];
    char c;
    std::vector<std::string> words_vector;
    while ((c = (char) fgetc(input_file)) != EOF) {
        if (is_word_start) {
            if (myIsalpha(c)) {
                word[word_length++] = myTolower(c);
                is_word_start = false;
            }
        } else {
            if (myIsalpha(c)) {
                word[word_length++] = myTolower(c);
            } else {
                word[word_length] = '\0';
                words_vector.emplace_back(word); // 减少一次构造....
                is_word_start = true;
                word_length = 0;
            }
        }
    }

    for (int i = 0; i < words_vector.size(); i++) {
        words[i] = new char[words_vector[i].length() + 1];
        strcpy(words[i], words_vector[i].c_str());
    }
    fclose(input_file);

    return words_vector.size();
}

void output_word_chain_to_file(std::string output_file_name, char *result[], int word_num, bool output_num) {
    FILE *output_file = fopen(output_file_name.c_str(), "w");
    if (output_file == nullptr) {
        fprintf(stderr, "Cannot open file %s\n", output_file_name.c_str());
    }
    if (output_num) {
        fprintf(output_file, "%d\n", word_num);
    }
    for (int i = 0; i < word_num; ++i) {
        fprintf(output_file, "%s\n", result[word_num]);
    }
    fclose(output_file);
}

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

int get_word_from_file_v2(std::string input_file_name, char *words[]) {
    using namespace std;
    ifstream file(input_file_name);
    string line;
    vector<string> words_vector;

    while (getline(file, line)) {
        stringstream ss(line);

    }
    return 0;
}

int main(int argc, char *argv[]) {
    ArgParser parser(argc, argv, "nwch:t:j:r");
    char head = 0, tail = 0, disallowed_head = 0, function = 0;
    bool enable_loop;
    int word_num, result_num;
    std::string input_file_name;

    ArgParser::parse_arg(parser, head, tail, disallowed_head, enable_loop, function, input_file_name);
    std::cout << "-h " << head << std::endl;
    std::cout << "-t " << tail << std::endl;
    std::cout << "-j " << disallowed_head << std::endl;
    std::cout << "-r " << enable_loop << std::endl;
    std::cout << "function: " << function << std::endl;
    std::cout << "input_file_name: " << input_file_name << std::endl;
    char **words = new char *[maxWordsNum]();
    char **results = new char *[maxResultsNum]();
    word_num = get_word_from_file(input_file_name, words);
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
        output_word_chain_to_file("solution.txt", results, result_num, function == 'n');
    } catch (std::exception &e) {
        fprintf(stderr, "%s\n", e.what());
    }
    release(words, word_num, results, result_num);
    return 0;
}