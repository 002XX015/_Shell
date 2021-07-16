#include "shell.hpp"

int main()
{
    Shell object;

    std::vector<std::string> arguments_for_InternalCommand;
    std::vector<std::string> arguments_for_DefaultShell;
    std::string buf;

    while (true)
    {
        arguments_for_InternalCommand = object.ReadLine();

        arguments_for_DefaultShell = arguments_for_InternalCommand;
        buf = arguments_for_DefaultShell[0];
        arguments_for_DefaultShell[0] = "/bin/";
        arguments_for_DefaultShell[0] += buf;

        if (object.StartInternalCommand(arguments_for_InternalCommand) == false)
            object.StartDefaultShell(arguments_for_DefaultShell);
    }

    return 0;
}
