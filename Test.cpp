/// Test.cpp : This file contains the 'cmain' function. Program execution begins and ends there.
/// This file is an example how 'cmain.hpp' and 'lib_fm::command_line' can be used to safely and elegantly
/// accept and store command line arguments inside the program.
#include <iostream>
#include <utility>
#include "cmain.hpp"

std::int32_t cmain(lib_fm::command_line cmd)
{
    if (cmd.size() == 1) {
        endl(endl(std::cerr) << "Usage: " << cmd.front() << "\targ1 arg_2 A3 4 ...");
        return EXIT_FAILURE;
    };

    endl(endl(std::cout) << "wellcome to:\t" << cmd[0].size() << ":" << cmd[0]);

    endl(endl(std::cout) << "reversed");
    for (auto it = cmd.rbegin(); it != cmd.rend(); ++it)
        endl(std::cout << "\t" << it->size() << ":" << *it);

    endl(endl(std::cout) << "reversed sub(2)");
    auto drop_first_2= cmd.subspan(2);
    for (auto it = drop_first_2.rbegin(); it != drop_first_2.rend(); ++it)
        endl(std::cout << "\t" << it->size() << ":" << *it);

    endl(endl(std::cout) << "sub<1>");
    for (auto arg : cmd.subspan<1>())
        endl(std::cout << "\t" << arg.size() << ":" << arg);

    endl(endl(std::cout) << "first<1>");
    for (auto arg : cmd.first<1>())
        endl(std::cout << "\t" << arg.size() << ":" << arg);

    endl(endl(std::cout) << "first(2)");
    for (auto arg : cmd.first(2))
        endl(std::cout << "\t" << arg.size() << ":" << arg);

    endl(std::cout << "last<1>");
    for (auto arg : cmd.last<1>())
        endl(std::cout << "\t" << arg.size() << ":" << arg);

    endl(endl(std::cout) << "last(2)");
    for (auto arg : cmd.last(2))
        endl(std::cout << "\t" << arg.size() << ":" << arg);

    return EXIT_SUCCESS;
};
