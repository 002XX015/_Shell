#include "shell.hpp"

Shell::Shell()
{
    quantity_commands = 2;

    list_of_command = new std::string[quantity_commands];
    list_of_command[0] = "help";
    list_of_command[1] = "cd";

    reference_func.push_back(&Shell::help);
    reference_func.push_back(&Shell::cd);
}

int Shell::help(std::vector<std::string>& arg)
{
    std::cout << "Shell v0.9" << std::endl;

    for (short i = 0; i != quantity_commands; i++)
    {
        if (list_of_command[i] == "help")
            std::cout << "help: Command help: show you list of command";
        else if (list_of_command[i] == "cd")
            std::cout << "cd: Command cd: moves your location";

        std::cout << std::endl;
    }

    return 0;
}

int Shell::cd(std::vector<std::string>& arg)
{
    if (arg.size() == 1)
        std::cerr << "Zero arguments" << std::endl;
    else
    {
        std::string buf_str = arg[1];
        char buf_char[buf_str.size()];
        for (short i = 0; i != short(buf_str.size()); i++)
            buf_char[i] = buf_str[i];

        if (chdir(buf_char) != 0)
            std::cerr << "Wrong path" << std::endl;
    }

    return 0;
}

std::vector<std::string> Shell::ReadLine()
{
    std::cout << "> ";

    char symbol;

    std::string buf_string;
    std::vector<std::string> input_string;

    short string_counter = 0;
    while (true)
    {
        if (std::cin.peek() != ' ' && std::cin.peek() != '\n')
        {
            std::cin >> symbol;

            buf_string.insert(string_counter, 1, symbol);
            string_counter++;
        }
        else if (std::cin.peek() == ' ')
        {
            std::cin.get();

            input_string.push_back(buf_string);

            buf_string.clear();
            string_counter = 0;
        }
        else
        {
            input_string.push_back(buf_string);
            break;
        }
    }
    std::cin.get();

    return input_string;
}

bool Shell::StartInternalCommand(std::vector<std::string>& vec)
{
    bool _status = false;
    for (short i = 0; i != quantity_commands; i++)
    {
        if (vec[0] == list_of_command[i])
        {
            _status = true;
            (this->*reference_func[i])(vec);
        }
    }

    return _status;
}

int Shell::StartDefaultShell(std::vector<std::string>& vec)
{
    std::vector<const char*> arguments;

    for (long unsigned int i = 0; i != vec.size(); i++)
        arguments.push_back(vec[i].data());
    arguments.push_back(NULL); // execvp dont understand how many arguments we send

    pid_t pid;
    int status;
    switch( pid = fork() )
    {
        case -1: // Error create process
            std::cerr << "Error create process" << std::endl;
            exit(1);
        case 0: //Child Process
            if (execvp(arguments[0], const_cast<char* const*>(arguments.data())) == -1) //hate execvp very old func
                std::cerr << "Unknown command" << std::endl;
            exit(1);
        default: //Parrent process
            do
            {
                waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 0;
}

Shell::~Shell()
{
    delete[] list_of_command;
}
