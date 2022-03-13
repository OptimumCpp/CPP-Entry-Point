/// This header file changes the entry point of a C++ program from conventional 'main' to safer the function 'cmain'
/// The header file is supposed to be included only in the main module of an executable application, or linkage fails.
/// it tags the including CPP file as the main module.
/// mailto:farid.mehrabi@gmail.com

#ifndef		CMAIN_HPP
#define		CMAIN_HPP
#include	"command_line.hpp"

/// <summary>
/// This is the safe substitute entry point for the C++ program. Must be defined.
/// </summary>
/// <param name="command_arguments">A more-or-less safer veiw into the array of command line arguments</param>
/// <returns>
/// an integer returned to system or spawning process upon current program termination:
/// 'EXIT_SUCCESS' means proper termination of program with no errors or exceptions.
/// other values can define the error/exception number
/// </returns>
inline static std::int32_t cmain(lib_fm::command_line);

int main(int count, char* args[]) { return cmain({count,args}); };

#endif //!	CMAIN_HPP
