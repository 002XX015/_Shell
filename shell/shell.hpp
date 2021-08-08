#ifndef SHELL_H_
#define SHELL_H_

// c++
#include <iostream> // cout | cerr | endl
#include <cstring>

// stl
#include <vector>

// process
#include <unistd.h>
#include <sys/wait.h>

class Shell
{
private:
    typedef int (Shell::*list_of_functions)(std::vector<std::string>&);
    /*
            int help(std::vector<std::string>&);

            int = int
            help = (Shell::*list_of_functions)
            (std::vector<std::string>&) = (std::vector<std::string>&)
    */

    short quantity_commands;
    std::string* list_of_command;
    std::vector<list_of_functions> reference_func;

    int help(std::vector<std::string>&);
    int cd(std::vector<std::string>&);
public:
    Shell();

    ~Shell();

    std::vector<std::string> ReadLine();

    bool StartInternalCommand(std::vector<std::string>&);

    int StartDefaultShell(std::vector<std::string>&);
};

#endif /* SHELL_H_ */
