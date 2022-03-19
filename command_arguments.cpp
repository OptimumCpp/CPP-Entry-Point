/// Test.cpp : This file contains the 'cmain' function. Program execution begins and ends there.
/// This file is an example how 'cmain.hpp' and 'lib_fm::command_line' can be used to safely and elegantly
/// accept and store command line arguments inside the program.
#include <utility>
#include <iostream>
#include <algorithm>
//#include "cmain.hpp"
#include "../command_arguments.hpp"

std::int32_t cmain(lib_fm::main_arguments cmd)
//std::int32_t cmain(lib_fm::command_line cmd)
{
    if (cmd.size() == 1) {
        endl(endl(std::cerr) << "Usage: " << cmd.front() << "\targ1 arg_2 A3 ...");
        return EXIT_FAILURE;
    };

    endl(endl(std::cout) << "wellcome to:\t" << cmd[0].size() << ":" << cmd[0]);

    endl(endl(std::cout) << "reversed");
    for (auto arg : std::views::reverse(cmd))
        endl(std::cout << "\t" << arg.size() << ":" << arg);

    endl(endl(std::cout) << "reversed drop(2)");
    auto drop_first_2= std::views::drop(cmd,2);
    for (auto arg : drop_first_2)
        endl(std::cout << "\t" << arg.size() << ":" << arg);

    endl(endl(std::cout) << "drop(1)");
    for (auto arg : std::views::drop(cmd, 1))
        endl(std::cout << "\t" << arg.size() << ":" << arg);

    return EXIT_SUCCESS;
};
