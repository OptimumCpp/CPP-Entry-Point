/// Test.cpp : This file contains the 'cmain' function. Program execution begins and ends there.
/// This file is an example how 'cmain.hpp' and 'lib_fm::command_line' can be used to safely and elegantly
/// accept and store command line arguments inside the program.
#include <iostream>
#include <utility>
#include "cmain.hpp"

std::int32_t cmain(lib_fm::command_line cmd)
{
    if (cmd.size() == 1) {
        endl(endl(std::cerr) << "Usage: " << cmd.front() << "\targ1 arg_2 A3 ...");
        return EXIT_FAILURE;
    };

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


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
