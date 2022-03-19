/// Test.cpp : This file contains the 'cmain' function. Program execution begins and ends there.
/// This file is an example how 'cmain.hpp' and 'lib_fm::command_line' can be used to safely and elegantly
/// accept and store command line arguments inside the program.
#include <utility>
#include <iostream>
#include <algorithm>
#include "../command_environment.hpp"

std::int32_t cmain(lib_fm::main_arguments cmd, lib_fm::environment env)
{
    if (cmd.size() == 1) {
        endl(endl(std::cerr) << "Usage: " << cmd.front() << "\targ1 arg_2 A3 ...");
        return EXIT_FAILURE;
    };

    endl(endl(std::cout) << "wellcome to:\t" << cmd[0].size() << ":" << cmd[0]);

    endl(endl(std::cout) << "environment:");
    std::ranges::copy(env|std::views::keys, std::ostream_iterator<lib_fm::environment::value_type>(std::cout, "\n"));
    endl(endl(std::cout) << "path:");
    std::ranges::copy(env["path"].front() | std::views::split(';') | std::views::transform([](auto const&& entry) {
        		return lib_fm::environment::value_type{entry};
        	}), std::ostream_iterator<lib_fm::environment::value_type>(std::cout, "\n"));
 
    endl(endl(std::cout) << "arguments reversed");
    for (auto arg : std::views::reverse(cmd))
        endl(std::cout << "\t" << arg.size() << ":" << arg);

    endl(endl(std::cout) << "arguments reversed drop(2)");
    auto drop_first_2 = std::views::drop(cmd, 2);
    for (auto arg : drop_first_2)
        endl(std::cout << "\t" << arg.size() << ":" << arg);

    endl(endl(std::cout) << "arguments drop(1)");
    for (auto arg : std::views::drop(cmd, 1))
        endl(std::cout << "\t" << arg.size() << ":" << arg);

    return EXIT_SUCCESS;
};
