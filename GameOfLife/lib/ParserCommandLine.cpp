#include "GameOfLife.hpp"

// Prints the help message for using the command-line program
void ParserCommandLine::print_help()
{
    std::cout << "Usage: ./game <input_file> --iterations=<n> --output=<output_file>\n"
          << "You can specify the input file and the number of iterations at the start:\n"
          << "./game <input_file> -i <iterations> -o <output_file>\n\n"
          << "Example:\n"
          << "./build/game game1.live --iterations=2 --output=out3.live\n\n"
          << "Commands for interactive play:\n"
          << " - dump <output_file>: Saves the current game state to the specified file.\n"
          << "   By default, the file is saved as 'out.live'.\n"
          << " - tick <n>: Advances the game by <n> steps (1 step by default).\n"
          << " - exit: Ends the game and closes the program.\n\n"
          << "Additional Notes:\n"
          << " - The game field is updated and displayed in real-time after each step.\n"
          << " - Use the dump command to save your progress and resume later.\n";
}

// Constructor that initializes mode and iterations, and parses command-line arguments
ParserCommandLine::ParserCommandLine(int argc, char **argv)
    : mode('0'), iterations(0)
{
    parse(argc, argv);  // Parse the arguments passed to the constructor
}

// Checks if the file name has a '.live' extension
bool ParserCommandLine::has_live_extension(const std::string &filename)
{
    const std::string extension = ".live";
    return filename.size() >= extension.size() &&
           filename.compare(filename.size() - extension.size(), extension.size(), extension) == 0;
}

// Parses command-line arguments and sets the appropriate mode and parameters
void ParserCommandLine::parse(int argc, char **argv)
{
    try
    {
        if (argc == 2 && std::string(argv[1]) == "--help")
        {
            print_help();  // Печать справки
            return;        // Возврат из функции без завершения программы
        }

        if (argc == 2)
        {
            input_file = argv[1];  // Устанавливаем входной файл
            if (!has_live_extension(input_file))
            {
                throw std::invalid_argument("Invalid file extension: Input file must have .live extension.");
            }
            mode = '1';  // Устанавливаем режим '1' для валидного входного файла
        }
        else if (argc == 1)
        {
            mode = '2';  // Устанавливаем режим '2', если аргументы не переданы
        }
        else if (argc >= 4)
        {
            input_file = argv[1];  // Устанавливаем входной файл, если передано больше 3-х аргументов

            if (parse_args_iterations(argc, argv) || parse_args_output(argc, argv))
            {
                throw std::invalid_argument("Error parsing arguments!");  // Ошибка при разборе аргументов
            }
            mode = '3';  // Устанавливаем режим '3' при успешном разборе
        }
        else
        {
            throw std::invalid_argument("Invalid arguments: Unexpected number of parameters.");  // Ошибка при неверном числе аргументов
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;  // Печать сообщения об ошибке
        print_help();  // Вывод справки при ошибке
        mode = '0';    // Сброс режима в безопасное состояние
    }
}



// Parses the iterations argument from the command line
bool ParserCommandLine::parse_args_iterations(int argc, char **argv)
{
    int ind_iter = 0;
    std::string iterations_arg;

    // Search for '-i' or '--iterations=' argument
    while ((ind_iter < (argc - 1)) &&
           !((std::string(argv[ind_iter]) == "-i") || (std::string(argv[ind_iter]).substr(0, 13) == "--iterations=")))
    {
        ++ind_iter;
    }

    // If '-i' argument is found, set iterations
    if (std::string(argv[ind_iter]) == "-i" && (ind_iter < (argc - 1)))
    {
        iterations_arg = argv[ind_iter + 1];
    }
    else if (std::string(argv[ind_iter]).substr(0, 13) == "--iterations=")
    {
        iterations_arg = std::string(argv[ind_iter]).substr(13);
    }
    else
    {
        return true;  // Return true if iterations argument is not found
    }

    std::regex number_regex("^[0-9]+$");  // Regex for matching positive integers
    if (!std::regex_match(iterations_arg, number_regex))
    {
        throw std::invalid_argument("Invalid iterations value: Must be a positive integer.");
    }

    try
    {
        iterations = std::stoi(iterations_arg);  // Convert iterations_arg to integer
    }
    catch (const std::exception &)
    {
        throw std::invalid_argument("Invalid iterations value: Must be an integer.");
    }

    if (iterations <= 0)
    {
        throw std::invalid_argument("Iterations must be a positive integer.");
    }

    return false;
}

// Parses the output file argument from the command line
bool ParserCommandLine::parse_args_output(int argc, char **argv)
{
    int ind_iter = 0;
    std::string output_arg;

    // Search for '-o' or '--output=' argument
    while ((ind_iter < (argc - 1)) &&
           !((std::string(argv[ind_iter]) == "-o") || (std::string(argv[ind_iter]).substr(0, 9) == "--output=")))
    {
        ++ind_iter;
    }

    // If '-o' argument is found, set output file
    if (std::string(argv[ind_iter]) == "-o" && (ind_iter < (argc - 1)))
    {
        output_arg = argv[ind_iter + 1];
    }

    else if (std::string(argv[ind_iter]).substr(0, 9) == "--output=")
    {
        output_arg = std::string(argv[ind_iter]).substr(9);
    }
    else
    {
        return true;  // Return true if output argument is not found
    }

    if (!has_live_extension(output_arg))
    {
        throw std::invalid_argument("Invalid file extension: Output file must have .live extension.");
    }

    output_file = output_arg;  // Set output file
    return false;
}

// Returns the mode in which the program is running
char ParserCommandLine::get_mode() const
{
    return mode;
}

// Returns the input file path, if applicable based on the current mode
std::string ParserCommandLine::get_input_file() const
{
    if (mode == '1' || mode == '3')
    {
        return input_file;
    }
    throw std::logic_error("Input file not available in this mode.");  // Throw error if not available in this mode
}

// Returns the output file path, if applicable based on the current mode
std::string ParserCommandLine::get_output_file() const
{
    if (mode == '3')
    {
        return output_file;
    }
    throw std::logic_error("Output file not available in this mode.");  // Throw error if not available in this mode
}

// Returns the number of iterations, if applicable based on the current mode
int ParserCommandLine::get_iterations() const
{
    if (mode == '3')
    {
        return iterations;
    }
    throw std::logic_error("Iterations not available in this mode.");  // Throw error if not available in this mode
}
