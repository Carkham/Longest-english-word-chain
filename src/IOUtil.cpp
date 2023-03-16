//
// Created by 13021 on 2023/3/16.
//
#include <IOUtil.h>

#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#define bufferSize 1024
#define myIsalpha(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
#define myTolower(c) (c <= 'Z' ? (c + 0x20) : (c))

int IOUtil::get_word_from_file(const char *input_file_name, char *words[]) {
    FILE *input_file = fopen(input_file_name, "r");
    if (input_file == nullptr) {
        fprintf(stderr, "No such file %s\n", input_file_name);
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

void IOUtil::output_word_chain_to_file(const char *output_file_name, char *result[], int word_num, bool output_num) {
    FILE *output_file = fopen(output_file_name, "w");
    if (output_file == nullptr) {
        fprintf(stderr, "Cannot open file %s\n", output_file_name);
    }
    if (output_num) {
        fprintf(output_file, "%d\n", word_num);
    }
    for (int i = 0; i < word_num; ++i) {
        fprintf(output_file, "%s\n", result[word_num]);
    }
    fclose(output_file);
}