#include <set>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cctype>
#include <tuple>
#include <forward_list>
#include <array>
#include <cstdlib>
#include <string>
#include <sstream>
#include <random>
#include <regex>

using Field = std::vector<std::vector<bool>>; // Grid field representing the game state

/**
 * Class representing the state of the game.
 */
class GameState
{
private:
    std::string game_version;   // Version of the game
    std::string universe_name;  // Name of the universe
    int size;                   // Size of the grid
    int count_of_iterations;    // Number of iterations to simulate
    std::set<int> B_conditions; // Birth conditions
    std::set<int> S_conditions; // Survival conditions
    Field field;                // The grid representing the current state of the game

public:
    /**
     * Default constructor for initializing the game state with default values.
     */
    GameState();

    /**
     * Destructor for cleaning up any resources when the GameState object is destroyed.
     */
    ~GameState();

    /**
     * Retrieves the current game version.
     *
     * @return The version of the game as a string.
     */
    std::string get_game_version() const;

    /**
     * Retrieves the name of the universe.
     *
     * @return The name of the universe as a string.
     */
    std::string get_universe_name() const;

    /**
     * Retrieves the size of the grid.
     *
     * @return The size of the grid as an integer.
     */
    int get_size() const;

    /**
     * Retrieves the number of iterations to simulate.
     *
     * @return The number of iterations as an integer.
     */
    int get_count_of_iterations() const;

    /**
     * Retrieves the birth conditions set for the game.
     *
     * @return A set of integers representing birth conditions.
     */
    std::set<int> get_B_conditions() const;

    /**
     * Retrieves the survival conditions set for the game.
     *
     * @return A set of integers representing survival conditions.
     */
    std::set<int> get_S_conditions() const;

    /**
     * Retrieves the current field (game state) as a 2D vector.
     *
     * @return A 2D vector representing the grid (game state).
     */
    std::vector<std::vector<bool>> get_field() const;

    /**
     * Sets the game version to the specified value.
     *
     * @param version The new version string to set.
     */
    void set_game_version(const std::string &version);

    /**
     * Sets the universe name to the specified value.
     *
     * @param name The new universe name to set.
     */
    void set_universe_name(const std::string &name);

    /**
     * Sets the grid size to the specified value.
     *
     * @param new_size The new size of the grid.
     */
    void set_size(int new_size);

    /**
     * Sets the number of iterations for the game.
     *
     * @param iterations The number of iterations to simulate.
     */
    void set_count_of_iterations(int iterations);

    /**
     * Sets the birth conditions to the specified set.
     *
     * @param conditions A set of integers representing the birth conditions.
     */
    void set_B_conditions(const std::set<int> &conditions);

    /**
     * Sets the survival conditions to the specified set.
     *
     * @param conditions A set of integers representing the survival conditions.
     */
    void set_S_conditions(const std::set<int> &conditions);

    /**
     * Sets the game state field to the specified grid.
     *
     * @param new_field A 2D vector representing the new grid (game state).
     */
    void set_field(const Field &new_field);
};

/**
 * Class for simulating and updating the game state.
 */
class GameEngine
{
public:
    /**
     * Constructor for initializing the GameEngine with the provided GameState and number of iterations.
     *
     * @param ReceivedGameState A reference to the GameState object.
     * @param iterations The number of iterations to simulate.
     */
    GameEngine(GameState &ReceivedGameState, int iterations);

    /**
     * Updates the game state by computing the next state of the field based on the current state.
     */
    void UpdateGameState();

    /**
     * Counts the number of live neighbors around a given cell.
     *
     * @param field The current field (grid).
     * @param x The x-coordinate of the cell.
     * @param y The y-coordinate of the cell.
     * @return The count of live neighbors around the specified cell.
     */
    int countNeighbors(const Field &field, int x, int y);

private:
    GameState &CurrentGameState;       // Reference to GameState object
    int received_number_of_iterations; // Number of iterations to simulate
};

/**
 * Class for parsing command-line arguments.
 */
class ParserCommandLine
{
public:
    /**
     * Constructor for parsing the command-line arguments.
     *
     * @param argc The argument count.
     * @param argv The argument vector.
     */
    ParserCommandLine(int argc, char **argv);

    /**
     * Prints out the help message with usage instructions and available options.
     */
    void print_help();

    /**
     * Parses the provided command-line arguments.
     *
     * @param argc The argument count.
     * @param argv The argument vector.
     */
    void parse(int argc, char **argv);

    /**
     * Retrieves the current mode of the program.
     *
     * @return The mode as a character (1, 2, or 3).
     */
    char get_mode() const;

    /**
     * Retrieves the input file name.
     *
     * @return The input file name as a string.
     */
    std::string get_input_file() const;

    /**
     * Retrieves the output file name.
     *
     * @return The output file name as a string.
     */
    std::string get_output_file() const;

    /**
     * Retrieves the number of iterations specified for the game.
     *
     * @return The number of iterations as an integer.
     */
    int get_iterations() const;

private:
    char mode;               // Mode of the program (1, 2, or 3)
    std::string input_file;  // Input file name
    std::string output_file; // Output file name
    int iterations;          // Number of iterations

    /**
     * Checks if the given file name has a .live extension.
     *
     * @param filename The file name to check.
     * @return True if the file has a .live extension, false otherwise.
     */
    bool has_live_extension(const std::string &filename);

    /**
     * Parses the iterations argument.
     *
     * @param argc The argument count.
     * @param argv The argument vector.
     * @return True if parsing was successful, false otherwise.
     */
    bool parse_args_iterations(int argc, char **argv);

    /**
     * Parses the output file argument.
     *
     * @param argc The argument count.
     * @param argv The argument vector.
     * @return True if parsing was successful, false otherwise.
     */
    bool parse_args_output(int argc, char **argv);
};

/**
 * Exception class for handling invalid commands.
 */
class InvalidCommandException : public std::runtime_error
{
public:
    /**
     * Constructor for the InvalidCommandException class with an error message.
     *
     * @param msg The error message to report.
     */
    explicit InvalidCommandException(const std::string &msg) : std::runtime_error(msg) {}
};

/**
 * Class for parsing user input commands.
 */
class ParserCommands
{
private:
    char command;         // Command character
    std::string filename; // File name for the dump command
    int iterations;       // Number of iterations

    /**
     * Checks if the given file name has a .live extension.
     *
     * @param filename The file name to check.
     * @return True if the file has a .live extension, false otherwise.
     */
    bool has_live_extension(const std::string &filename);

public:
    /**
     * Constructor for the ParserCommands class.
     */
    ParserCommands();

    /**
     * Parses a user input command string.
     *
     * @param input The command string input by the user.
     */
    void parse_command(const std::string &input);

    /**
     * Retrieves the parsed command character.
     *
     * @return The command as a character.
     */
    char get_command() const;

    /**
     * Retrieves the filename for the dump command.
     *
     * @return The filename as a string.
     * @throws InvalidCommandException If the command is not 'dump'.
     */
    const std::string &get_filename() const;

    /**
     * Retrieves the number of iterations for the tick command.
     *
     * @return The number of iterations as an integer.
     * @throws InvalidCommandException If the command is not 'tick'.
     */
    int get_iterations() const;

    /**
     * Parses the dump command from the input string.
     *
     * @param input The input string for the dump command.
     */
    void parse_dump(const std::string &input);

    /**
     * Parses the tick command from the input string.
     *
     * @param input The input string for the tick command.
     */
    void parse_tick(const std::string &input);

    /**
     * Parses the exit command from the input string.
     *
     * @param input The input string for the exit command.
     */
    void parse_exit(const std::string &input);

    /**
     * Parses the help command from the input string.
     *
     * @param input The input string for the help command.
     */
    void parse_help(const std::string &input);
};

/**
 * Class for parsing input from files.
 */
class ParserFile
{
private:
    std::string file_name; // Name of the file to parse

public:
    /**
     * Constructor for the ParserFile class.
     *
     * @param file_name The name of the file to parse.
     */
    ParserFile(const std::string &file_name);

    /**
     * Parses the contents of the file and updates the game state accordingly.
     *
     * @param game_state A reference to the GameState object to update.
     */
    void parse(GameState &game_state);
    std::string launch_random_file();
private:
    /**
     * Parses the B/S conditions from a line in the file.
     *
     * @param conditions The conditions string.
     * @param game_state A reference to the GameState object to update.
     */
    void parse_conditions(const std::string &conditions, GameState &game_state);

    /**
     * Parses a condition string (e.g., B3 or S23) and updates the given condition set.
     *
     * @param condition_str The condition string.
     * @param condition_set A set of integers to be updated.
     */
    void parse_condition_set(const std::string &condition_str, std::set<int> &condition_set);

    /**
     * Parses the coordinates from a line in the file and updates the game state.
     *
     * @param line The line containing the coordinates.
     * @param game_state A reference to the GameState object to update.
     */
    void parse_coordinates(const std::string &line, GameState &game_state);
};

/**
 * @class GameInterface
 * @brief Manages the interaction between the user and the Game of Life system.
 */
class GameInterface
{
private:
    /**
     * @brief Starts the game based on the provided command-line arguments.
     *
     * @param argc The number of command-line arguments.
     * @param argv The array of command-line arguments.
     */
    void start_game(int argc, char **argv);
    
    int is_it_exit; // The exit flag to terminate the game
    
public:
    /**
     * @brief Constructs the GameInterface and initializes the game.
     *
     * @param argc The number of command-line arguments.
     * @param argv The array of command-line arguments.
     */
    GameInterface(int argc, char **argv);

    /**
     * @brief Prints general information about the game.
     *
     * @param game The current game state to print information about.
     */
    void print_info(const GameState &game);

    /**
     * @brief Prints the current game field to the console.
     *
     * @param game_state The game state that holds the field to print.
     * @param field The field to display on the console.
     */
    void print_field(const GameState &game_state, const Field &field) const;

    /**
     * @brief Processes user commands to manipulate the game state.
     *
     * @param game The current game state.
     * @param parser_command_line Command-line argument parser.
     * @param parser_command Command parser for user input.
     */
    void game_process(GameState &game, ParserCommandLine &parser_command_line, ParserCommands &parser_command);

    /**
     * @brief Displays the help menu to the user with usage instructions.
     */
    void print_help();

    /**
     * @brief Clears the specified number of lines from the console screen.
     *
     * @param count_lines The number of lines to clear.
     */
    void clear_lines(int count_lines);

    /**
     * @brief Saves the current game state to a file.
     *
     * @param game The current game state to save.
     * @param output_file The name of the file to save the state.
     */
    void save_to_file(const GameState &game, const std::string &output_file);

    /**
     * @brief Manages user input by reading and sanitizing the command string.
     *
     * @return A sanitized string representing the user input.
     */
    std::string manage_input();
};
