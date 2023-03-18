//
// Created by 13021 on 2023/3/16.
//
#include "gtest/gtest.h"
#include "ArgParser.h"

void reset(char &head, char &tail, char &d_head, bool &enable_loop,
           char &function, std::string &input_file) {
    head = 0, tail = 0, d_head = 0, function = 0;
    input_file = "";
    enable_loop = false;
}

TEST(ArgParser, parse_arg) {
    int argc;
    bool enable_loop;
    char head = 0, tail = 0, d_head = 0, function = 0;
    const char **argv;
    std::string input_file_name;
    ArgParser *parser;
    // sample 1
    argc = 3;
    argv = new const char *[]{"", "-n", "test.txt"};
    parser = new ArgParser(argc, const_cast<char**>(argv), "nwch:t:j:r");
    ArgParser::parse_arg(*parser, head, tail, d_head, enable_loop, function, input_file_name);
    EXPECT_EQ(0, head);
    EXPECT_EQ(0, tail);
    EXPECT_EQ(0, d_head);
    EXPECT_EQ(false, enable_loop);
    EXPECT_EQ('n', function);
    EXPECT_EQ("test.txt", input_file_name);
    delete parser;
    delete[] argv;
    reset(head, tail, d_head, enable_loop, function, input_file_name);

    // sample 2
    argc = 10;
    argv = new const char *[]{"", "-w", "-h", "a", "-t", "b", "-j", "c", "-r", "test.txt"};
    parser = new ArgParser(argc, const_cast<char**>(argv), "nwch:t:j:r");
    ArgParser::parse_arg(*parser, head, tail, d_head, enable_loop, function, input_file_name);
    EXPECT_EQ('a', head);
    EXPECT_EQ('b', tail);
    EXPECT_EQ('c', d_head);
    EXPECT_EQ(true, enable_loop);
    EXPECT_EQ('w', function);
    EXPECT_EQ("test.txt", input_file_name);
    delete parser;
    delete[] argv;

    // sample 3 duplicate error
    argc = 9;
    argv = new const char *[]{"", "-c", "-h", "a", "-t", "b", "-j", "c", "-r"};
    parser = new ArgParser(argc, const_cast<char**>(argv), "nwch:t:j:r");
    EXPECT_ANY_THROW(ArgParser::parse_arg(*parser, head, tail, d_head, enable_loop, function, input_file_name));
    reset(head, tail, d_head, enable_loop, function, input_file_name);
    delete parser;
    delete[] argv;

    argc = 3;
    argv = new const char *[]{"", "-c", "-n"};
    parser = new ArgParser(argc, const_cast<char**>(argv), "nwch:t:j:r");
    EXPECT_ANY_THROW(ArgParser::parse_arg(*parser, head, tail, d_head, enable_loop, function, input_file_name));
    reset(head, tail, d_head, enable_loop, function, input_file_name);
    delete parser;
    delete[] argv;

    // sample 4 illegal format error
    argc = 3;
    argv = new const char *[]{"", "-h", "?"};
    parser = new ArgParser(argc, const_cast<char**>(argv), "nwch:t:j:r");
    // FIXME: EXPECT_THROW
    EXPECT_ANY_THROW(ArgParser::parse_arg(*parser, head, tail, d_head, enable_loop, function, input_file_name));
    reset(head, tail, d_head, enable_loop, function, input_file_name);
    delete parser;
    delete[] argv;

    argc = 3;
    argv = new const char *[]{"", "-t", "?"};
    parser = new ArgParser(argc, const_cast<char**>(argv), "nwch:t:j:r");
    // FIXME: EXPECT_THROW
    EXPECT_ANY_THROW(ArgParser::parse_arg(*parser, head, tail, d_head, enable_loop, function, input_file_name));
    reset(head, tail, d_head, enable_loop, function, input_file_name);
    delete parser;
    delete[] argv;

    argc = 3;
    argv = new const char *[]{"", "-j", "?"};
    parser = new ArgParser(argc, const_cast<char**>(argv), "nwch:t:j:r");
    // FIXME: EXPECT_THROW
    EXPECT_ANY_THROW(ArgParser::parse_arg(*parser, head, tail, d_head, enable_loop, function, input_file_name));
    reset(head, tail, d_head, enable_loop, function, input_file_name);
    delete parser;
    delete[] argv;

    // sample 5 unknown arg
    argc = 2;
    argv = new const char *[]{"", "-p"};
    parser = new ArgParser(argc, const_cast<char**>(argv), "nwch:t:j:r");
    // FIXME: EXPECT_THROW
    EXPECT_ANY_THROW(ArgParser::parse_arg(*parser, head, tail, d_head, enable_loop, function, input_file_name));
    reset(head, tail, d_head, enable_loop, function, input_file_name);
    delete parser;
    delete[] argv;


    // sample 6 -n with -h, -t, -j, -r
    argc = 10;
    argv = new const char *[]{"", "-n", "-h", "a", "-t", "c", "-j", "a", "-r", "test.txt"};
    parser = new ArgParser(argc, const_cast<char**>(argv), "nwch:t:j:r");
    ArgParser::parse_arg(*parser, head, tail, d_head, enable_loop, function, input_file_name);
    reset(head, tail, d_head, enable_loop, function, input_file_name);
    delete parser;
    delete[] argv;

    // sample 7 missing option error
    argc = 2;
    argv = new const char *[]{"", "-h"};
    parser = new ArgParser(argc, const_cast<char**>(argv), "nwch:t:j:r");
    // FIXME: EXPECT_THROW
    EXPECT_ANY_THROW(ArgParser::parse_arg(*parser, head, tail, d_head, enable_loop, function, input_file_name));
    reset(head, tail, d_head, enable_loop, function, input_file_name);
    delete parser;
    delete[] argv;

    // sample 8 wrong option pattern
    EXPECT_ANY_THROW(new ArgParser(0, nullptr, "_1_3"));
}