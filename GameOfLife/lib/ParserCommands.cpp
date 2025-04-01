#include "GameOfLife.hpp"

// Constructor that initializes command and iterations to default values
ParserCommands::ParserCommands() : command(0), iterations(0) {}

// Checks if the given filename has a '.live' extension
bool ParserCommands::has_live_extension(const std::string &filename)
{
    const std::string extension = ".live";
    return filename.size() >= extension.size() &&
           filename.compare(filename.size() - extension.size(), extension.size(), extension) == 0;
}

// Parses the "dump" command and validates the associated filename
void ParserCommands::parse_dump(const std::string &input)
{
    std::istringstream stream(input);
    std::string command_part, filename_part;

    stream >> command_part >> filename_part;

    if (filename_part.empty())  // Check if filename is missing
    {
        throw InvalidCommandException("dump command requires a filename.");
    }

    if (!has_live_extension(filename_part))  // Check if file has a valid extension
    {
        throw InvalidCommandException("Invalid file extension: Output file must have .live extension.");
    }

    command = '1';  // Set the command type to '1' for dump
    filename = filename_part;  // Store the filename
}

// Parses the "tick" command and validates the iterations value
void ParserCommands::parse_tick(const std::string &input)
{
    std::istringstream stream(input);
    std::string command_part;
    stream >> command_part;

    if (command_part != "tick" && command_part != "t")  // Validate the command part
    {
        throw InvalidCommandException("Invalid command format for tick.");
    }

    command = '2';  // Set the command type to '2' for tick
    iterations = 1;  // Default number of iterations is 1

    // Check if there are additional iterations specified
    if (!stream.eof())
    {
        std::string iterations_part;
        stream >> iterations_part;

        try
        {
            size_t pos;
            iterations = std::stoi(iterations_part, &pos);  // Convert the iterations part to integer

            if (pos != iterations_part.length())  // Ensure no extra characters after the number
            {
                throw std::invalid_argument("Invalid characters after number.");
            }

            if (iterations <= 0)  // Validate that iterations is a positive number
            {
                throw std::invalid_argument("Iterations must be a positive integer.");
            }
        }
        catch (const std::invalid_argument &)
        {
            throw InvalidCommandException("tick command requires a valid positive integer without extra characters.");
        }
        catch (const std::out_of_range &)
        {
            throw InvalidCommandException("tick command requires an integer within a valid range.");
        }
    }

    if (!stream.eof())  // Check for unexpected characters after iterations
    {
        throw InvalidCommandException("Invalid input: Unexpected characters after iterations.");
    }
}

// Parses the "exit" command
void ParserCommands::parse_exit(const std::string &)
{
    command = '3';  // Set the command type to '3' for exit
}

// Parses the "help" command
void ParserCommands::parse_help(const std::string &)
{
    command = '4';  // Set the command type to '4' for help
}

// Main command parser that determines which command is being issued and processes it
void ParserCommands::parse_command(const std::string &input)
{
    if (input.empty())  // Default to "tick 1" if the input is empty
    {
        parse_tick("tick 1");
    }
    else if (input.find("dump") == 0)  // Check if the input starts with "dump"
    {
        if (input.size() > 4 && input[4] != ' ')  // Validate the command format for "dump"
        {
            throw InvalidCommandException("Unknown command!");
        }
        parse_dump(input);  // Parse the "dump" command
    }
    else if (input == "tick" || input == "t" || input.find("tick ") == 0 || input.find("t ") == 0)  // Check for "tick" or "t" commands
    {
        parse_tick(input);  // Parse the "tick" command
    }
    else if (input == "exit")  // Check for the "exit" command
    {
        parse_exit(input);  // Parse the "exit" command
    }
    else if (input == "help")  // Check for the "help" command
    {
        parse_help(input);  // Parse the "help" command
    }
    else  // If the command is unknown, throw an exception
    {
        throw InvalidCommandException("Unknown command!");
    }
}

// Returns the parsed command type
char ParserCommands::get_command() const
{
    return command;
}

// Returns the filename associated with the "dump" command
const std::string &ParserCommands::get_filename() const
{
    if (command != '1')  // Ensure the command is "dump" before returning the filename
    {
        throw InvalidCommandException("Filename not available for this command.");
    }
    return filename;  // Return the filename
}

// Returns the number of iterations associated with the "tick" command
int ParserCommands::get_iterations() const
{
    if (command != '2')  // Ensure the command is "tick" before returning the iterations
    {
        throw InvalidCommandException("Iterations not available for this command.");
    }
    return iterations;  // Return the number of iterations
}
