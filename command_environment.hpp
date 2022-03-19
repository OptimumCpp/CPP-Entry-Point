/// This header file changes the entry point of a C++ program from conventional 'main' to safer the function 'cmain'
/// The header file is supposed to be included only in the main module of an executable application, or linkage fails.
/// it tags the including CPP file as the main module.
/// mailto:farid.mehrabi@gmail.com

#ifndef		CMAIN_HPP
#define		CMAIN_HPP
#include	"main_arguments.hpp"

/// <summary>
/// This is the safe substitute entry point for the C++ program. Must be defined.
/// </summary>
/// <param name="command_arguments">A more-or-less safer veiw into the array of command line arguments</param>
/// <returns>
/// an integer returned to system or spawning process upon current program termination:
/// 'EXIT_SUCCESS' means proper termination of program with no errors or exceptions.
/// other values can define the error/exception number
/// </returns>
inline static std::int32_t cmain(lib_fm::main_arguments, lib_fm::environment);

int main(int count, char* args[], char* env_args[]);

namespace lib_fm
{
	//inline namespace {
		class main_forwarder {
			friend int ::main(int count, char* args[], char* env_args[]);
			inline int static forward_arguments(int count, char* args[], char* env_args[]);
		};// !main_forwarder
	//};// !namespace
};// !lib_fm

int main(int count, char* args[], char* env_args[]) {
	return 	lib_fm::main_forwarder::forward_arguments(count,args,env_args);
};

int lib_fm::main_forwarder::forward_arguments(int count, char* args[], char* env_args[])
{
	return ::cmain({ count,args }, { env_args });
};// !forward_arguments

#endif //!	CMAIN_HPP
