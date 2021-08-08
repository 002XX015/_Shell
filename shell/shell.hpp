#pragma once // fix

#include <iostream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

class Shell
{
private:
    typedef int (Shell::*list_of_functions)(std::vector<std::string>&); // wtf!!!!!!!!!

    short quantity_commands;
    std::string* list_of_command;
    std::vector<list_of_functions> reference_func;

    int help(std::vector<std::string>&);
    int cd(std::vector<std::string>&);
public:
    Shell();

    std::vector<std::string> ReadLine(); // hmmmmm

    bool StartInternalCommand(std::vector<std::string>&);

    int StartDefaultShell(std::vector<std::string>&);

    ~Shell();
};

// this code is not cross platform!!!
