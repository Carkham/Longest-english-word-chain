//
// Created by AORUS on 2023/3/8.
//

#include "ArgParser.h"
#include "iostream"

using std::vector;
using std::string;

ArgParser::ArgParser(int argc, char **argv, const char *pattern):
options(vector<int>(128, -1)), argv_index(0), argc(argc) {
    for (int i = 0; i < argc; i++) {
        this->argv.push_back(argv[i]);
    }
    for (const char *c = pattern; *c; c++) {
        if (std::isalpha(*c)) {
            options[*c] = 0; // 无需向后读入
            if (*(c + 1) == ':') { // 后一位为参数
                options[*c] = 1;
                c++;
            }
        } else {
            char msg[100] = {0};
            sprintf(msg, "Wrong option pattern.\n");
            throw std::invalid_argument(msg);
            // FIXME: throw exception
        }
    }
}

int ArgParser::next_arg() {
    argv_index++;

    // end
    if (argv_index == argc) {
        return 0;
    }

    // 参数
    if (argv[argv_index][0] == '-') {
        char c = argv[argv_index][1];
        if (std::isalpha(c)) {
            if (options[c] == 0) {
                param = ""; // 无参数
            }
            if (options[c] == 1) {
                argv_index++;
                if (argv_index == argc) {
                    char msg[100] = {0};
                    sprintf(msg, "Miss option for -%c.\n", c);
                    throw std::invalid_argument(msg);
                }
                param = string(argv[argv_index]);
            }
            if (options[c] == -1) {
                char msg[100] = {0};
                sprintf(msg, "Unknown argument -%c", c);
                throw std::invalid_argument(msg);
            }
            return c;
        }
    }

    // 单词
    param = string(argv[argv_index]);
    return 1;
}

bool check_duplicate(char data) {
    return data == 0;
}

void ArgParser::parse_arg(ArgParser &parser, char &head, char &tail, char &disallowed_head, bool &enable_loop,
                          char &function, string &input_file) {
    int arg;
    while ((arg = parser.next_arg()) != 0) {
        if (arg == -1) {
            break; // FIXME: throw exception
        } else if (arg == 1) { // 读文件名
            input_file = parser.param;
        } else {
            switch (arg) {
                case 'n':
                case 'w':
                case 'c':
                    if (!check_duplicate(function)) {
                        char msg[100] = {0};
                        sprintf(msg, "Duplicate main function for %c %c", arg, function);
                        throw std::invalid_argument(msg);
                    }
                    function = (char) arg;
                    break;
                case 'h':
                    if (!check_duplicate(head)) {
                        char msg[100] = {0};
                        sprintf(msg, "Duplicate value of -%c ,new: %s old %c", arg, parser.param.c_str(), head);
                        throw std::invalid_argument(msg);
                    }
                    head = parser.param[0];
                    if (!std::isalpha(head)) {
                        char msg[100] = {0};
                        sprintf(msg, "Error value of -%c, should be alpha got %c", arg, head);
                        throw std::invalid_argument(msg);
                    }
                    head = std::tolower(head);
                    break;
                case 't':
                    if (!check_duplicate(tail)) {
                        char msg[100] = {0};
                        sprintf(msg, "Duplicate value of -%c ,new: %s old %c", arg, parser.param.c_str(), tail);
                        throw std::invalid_argument(msg);
                    }
                    tail = parser.param[0];
                    if (!std::isalpha(tail)) {
                        char msg[100] = {0};
                        sprintf(msg, "Error value of -%c, should be alpha got %c", arg, tail);
                        throw std::invalid_argument(msg);
                    }
                    tail = std::tolower(tail);
                    break;
                case 'j':
                    if (!check_duplicate(disallowed_head)) {
                        char msg[100] = {0};
                        sprintf(msg, "Duplicate value of -%c ,new: %s old %c", arg, parser.param.c_str(), disallowed_head);
                        throw std::invalid_argument(msg);
                    }
                    disallowed_head = parser.param[0];
                    if (!std::isalpha(disallowed_head)) {
                        char msg[100] = {0};
                        sprintf(msg, "Error value of -%c, should be alpha got %c", arg, disallowed_head);
                        throw std::invalid_argument(msg);
                    }
                    disallowed_head = std::tolower(disallowed_head);
                    break;
                case 'r':
                    if (!enable_loop) {
                        enable_loop = true;
                    } else {
                        char msg[100] = {0};
                        sprintf(msg, "Duplicate value of -%c ,new: %s old %d", arg, parser.param.c_str(), enable_loop);
                        throw std::invalid_argument(msg);
                    }
                    break;
                default:
                    break;
            }
        }
    }

    // check conflict
    switch (function) {
        case 'n':
            if (head != 0 || tail != 0 || disallowed_head != 0 || enable_loop) {
                char msg[100] = {0};
                sprintf(msg, "argument -%c is not compatible with other argument\n while -h=%c -t=%c -j=%c -r=%d",
                        function, head, tail, disallowed_head, enable_loop);
            }
            break;
        case 'w':
        case 'c':
            break;
        default:
            char msg[100] = {0};
            sprintf(msg, "You must specify a function");
            throw std::invalid_argument(msg);
    }

    // check input_file
    if (input_file.empty()) {
        char msg[100] = {0};
        sprintf(msg, "You must specify a file");
        throw std::invalid_argument(msg);
    }
}