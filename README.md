# CPP-Entry-Point
A simplistic implementation of a view class for command line arguments and associated substitute entry point
Regarding the discussion https://wg21.link/P0781 on IsoCPP standardization. IMHO The solution provided here has achieved the goal
without modifying the toolchain. A header-only library subjugating the two veiw classes 'std::span' and 'std::string_view' to reach the downto
zero runtime overhead as well as minimum exposure to bug. This short library is trying to solve the unsafety of using command line
arguments in main function once for good and all.

Description:

<command_line.hpp/>

Defines the 'command_line' class as a 'std::span<char * const>' that imposts itself as if it were 'std::span<std::string_view const>'. 
That is the value is actually initialized and stored as 'std::span<char * const>' but accessor member functions and itertors are 
decorated to return 'std::string_view' instead of raw null-terminated strings.

<comman_line::command_line(int argc, char** argv);/>

This constructor can directly capture the command line arguments function and provide a very safe and elegant view  object to the 'argv'

<cmain.hpp>

Defines the traditional entry point function 'main' as a forwarder to the safer substitue entry point function 'cmain'.
This header must only be included in the CPP file that traditionally used to define the 'main' function(AKA application's main module).
Once included, including CPP file must define the 'cmain' function.

<int cmain(command_line);/>

This function defines the substitute entry point in the main module, where <cmain.hpp> has been included.

<Test.cpp/>

This is an illustration of a main module using the substitue entry point function and command line encapsulating class provided by this repository.
Just put the 3 files in the same folder and build this cpp file to see the usage example in effect. After a successful build run the program in 
console terminal.
Usage: test.exe A1 arg2 args3 arguments4 A5 ...

Remarks:
'std::span' needs C++20 or later. You need to build with proper compiler switch.


