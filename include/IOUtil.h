//
// Created by 13021 on 2023/3/16.
//

#ifndef WORDLIST_IOUTIL_H
#define WORDLIST_IOUTIL_H

class IOUtil {
public:
    static int get_word_from_file(const char *input_file_name, char *words[]);
    static void output_word_chain_to_file(const char *output_file_name, char *result[], int word_num, bool output_num);

    // int get_word_from_file_v2(std::string input_file_name, char *words[]);
};

#endif //WORDLIST_IOUTIL_H
