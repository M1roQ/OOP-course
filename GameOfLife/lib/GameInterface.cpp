#include "GameOfLife.hpp"

// Constructor: Initializes the game interface with the given command-line arguments and starts the game
GameInterface::GameInterface(int argc, char **argv)
{
    start_game(argc, argv);
    is_it_exit = 1;  // Flag to track if the game should continue running
}

// Prints information about the current game state, including universe name, rules, and iteration count
void GameInterface::print_info(const GameState &game)
{
    // Retrieve the universe name, birth and survival conditions, and current iteration
    std::string universe_name = game.get_universe_name();
    std::set<int> B_conditions = game.get_B_conditions();
    std::set<int> S_conditions = game.get_S_conditions();
    int current_iteration = game.get_count_of_iterations();

    // Clear the last 3 lines on the console and display updated information
    clear_lines(3);
    std::cout << "\033[34m" << "Universe Name: " << universe_name << std::endl;

    std::cout << "Transition Rule: B";
    for (int condition : B_conditions)
    {
        std::cout << condition;
    }
    std::cout << " / S";
    for (int condition : S_conditions)
    {
        std::cout << condition;
    }
    std::cout << std::endl;

    std::cout << "Current Iteration: " << current_iteration << "\033[34m" << std::endl;
}

// Starts the game by processing command-line arguments and determining the mode of operation
void GameInterface::start_game(int argc, char **argv)
{
    GameState game;

    // Check if help is requested and display help information
    if (argc > 1 && std::string(argv[1]) == "--help")
    {
        print_help();
        exit(0);
    }

    // Parse command-line arguments to determine the mode of operation
    ParserCommandLine parser_command_line(argc, argv);
    char mode = parser_command_line.get_mode();

    if (mode == '1')
    {
        // Load the game data from a specified file
        ParserFile parser_file(parser_command_line.get_input_file());
        parser_file.parse(game);

        std::cerr << "The game is ready! Press ENTER to start!";
        std::string input2;
        std::getline(std::cin, input2);

        // Print game information once, before displaying the field
        print_info(game);  // Display info only once at the start
        print_field(game, game.get_field());

        // Main game loop
        while (is_it_exit)
        {
            try
            {
                // Wait for user input and process the command
                std::string input = manage_input();

                ParserCommands parser_command;
                parser_command.parse_command(input);
                game_process(game, parser_command_line, parser_command);
            }
            catch (const InvalidCommandException &e)
            {
                // Handle invalid commands and display error message
                std::cerr << "\033[31m" << "Error: " << "\033[0m" << e.what() << "\n";
                std::cerr << "Press ENTER to continue...";

                std::string input2;
                std::getline(std::cin, input2);
                clear_lines(3);
            }
        }
    }
    else if (mode == '2')
    {
        // Define a list of predefined game files
        const std::string filenames[] = {"../games/glider.live", "../games/game2.live", "../games/game3.live", "../games/buterfly.live", "../games/game5.live"};

        // Initialize random number generator
        std::random_device rd;
        std::mt19937 gen(rd());  // Mersenne Twister generator
        std::uniform_int_distribution<> distrib(0, 4); // Uniform distribution between 0 and 4
        int random_number = distrib(gen); // Generate random number

        // Select a random file from the list
        std::string generated_file = filenames[random_number];

        // Load the selected file into the game state
        ParserFile parser_file(generated_file);
        parser_file.parse(game);

        std::cerr << "The game is ready! Press ENTER to start!";
        std::string input2;
        std::getline(std::cin, input2);

        print_field(game, game.get_field());

        // After generating the random field, continue processing commands
        while (is_it_exit)
        {
            try
            {
                std::string input = manage_input();

                ParserCommands parser_command;
                parser_command.parse_command(input);
                game_process(game, parser_command_line, parser_command);
            }
            catch (const InvalidCommandException &e)
            {
                std::cerr << "\033[31m" << "Error: " << "\033[0m" << e.what() << "\n";
                std::cerr << "Press ENTER to continue...";

                std::string input2;
                std::getline(std::cin, input2);
                clear_lines(3);
            }
        }
    }
    else if (mode == '3')
    {
        // Load the game state from the specified input file
        ParserFile parser_file(parser_command_line.get_input_file());

        parser_file.parse(game);

        print_field(game, game.get_field());

        // Initialize the game engine with the given number of iterations and update the game state
        GameEngine engine(game, parser_command_line.get_iterations());

        engine.UpdateGameState();

        std::cout << "The field after " << parser_command_line.get_iterations() << " iterations:\n";
        print_field(game, game.get_field());
        
        // Save the updated state to the specified output file
        save_to_file(game, parser_command_line.get_output_file());
        is_it_exit = 0;  // End the game loop
    }
}

// Displays the current game field in a human-readable format
void GameInterface::print_field(const GameState &game_state, const Field &field) const
{
    for (const auto& row : field) {
        for (bool cell : row) {
            if (cell) {
                std::cout << "\033[32m" << "\u25A0" << "\033[0m" << " ";  // Alive cell (green)
            } else {
                std::cout << "\033[35m" << "\u25A1" << "\033[0m" << " ";  // Dead cell (purple)
            }
        }
        std::cout << '\n';
    }
}

// Processes the user command and performs the corresponding game action
void GameInterface::game_process(GameState &game, ParserCommandLine &parser_command_line, ParserCommands &parser_command)
{
    char command = parser_command.get_command();

    if (command == '1') // Save the current game state to a file
    {
        save_to_file(game, parser_command.get_filename());
    }
    else if (command == '2') // Execute a game step (advance the game by one or more iterations)
    {
        GameEngine engine(game, parser_command.get_iterations());
        engine.UpdateGameState();

        int tmp = game.get_size() + 1;

        clear_lines(tmp);

        // Display updated information after game step
        print_info(game);  // Print updated information after state change
        print_field(game, game.get_field());
    }
    else if (command == '3') // Exit the game
    {
        std::cout << "Ending the Game...\n";
        is_it_exit = 0;
    }
    else if (command == '4') // Show help information
    {
        print_help();
    }
}

// Displays help information for the game, describing commands and usage
void GameInterface::print_help()
{
    std::cout << "Game of Life - Help\n"
              << "============================\n\n"
              << "You can start the game by specifying an input file and the number of steps to run:\n"
              << "./game <input file> -i <step count> -o <output file>\n\n"
              << "For example:\n"
              << "./build/game game1.live --iterations=2 --output=out3.live\n\n"
              << "Alternatively, you can play step by step. At the start, you may provide a file\n"
              << "that describes the initial field in the Life 1.06 format. If no file is provided,\n"
              << "a default field will be loaded.\n\n"
              << "Commands for step-by-step play:\n"
              << " - dump <output file>: Saves the current state of the field to the specified file.\n"
              << "   By default, the file is saved as 'out.live'.\n"
              << " - tick <n>: Advances the game by 'n' steps (default is 1 step).\n"
              << " - exit: Exits the game.\n\n"
              << "Additional Information:\n"
              << " - The field will be displayed in real-time after each tick.\n"
              << " - You can save your progress using the dump command, allowing you to continue later.\n\n"
              << "Press ENTER to continue...";

    std::string input2;
    std::getline(std::cin, input2);
    clear_lines(25);
}

// Clears a specified number of lines in the terminal to update the display
void GameInterface::clear_lines(int count_lines)
{
    for (int i = 0; i < count_lines; ++i)
        std::cout << "\033[F\033[K";  // Move cursor up and clear line
}

// Saves the current game state to a file in the appropriate format
void GameInterface::save_to_file(const GameState &game, const std::string &output_file)
{
    // Path to the "saved games" folder
    std::filesystem::path save_directory = "../saved games";
    
    // Check if the folder exists, and if not, create it
    if (!std::filesystem::exists(save_directory))
    {
        std::filesystem::create_directory(save_directory);
    }

    // Form the full file path to save the game state
    std::filesystem::path full_file_path = save_directory / output_file;

    std::ofstream file(full_file_path);
    if (!file.is_open())
    {
        throw std::runtime_error("It couldn't open file for writing: " + full_file_path.string());
    }

    // Write the game state to the file
    file << "#Life " << game.get_game_version() << "\n";
    file << "#N " << game.get_universe_name() << "\n";
    file << "#Size " << game.get_size() << "\n";

    file << "#R B";
    for (int condition : game.get_B_conditions())
    {
        file << condition;
    }
    file << "/S";
    for (int condition : game.get_S_conditions())
    {
        file << condition;
    }
    file << "\n";

    const auto &field = game.get_field();
    for (int row = 0; row < field.size(); ++row)
    {
        for (int col = 0; col < field[row].size(); ++col)
        {
            if (field[row][col])
            {
                file << row + 1 << " " << col + 1 << "\n";
            }
        }
    }

    file.close();
    std::cout << "The file was saved to: ../saved games/" << output_file << ". Press ENTER to continue..." << "\n";

    std::string input2;
    std::getline(std::cin, input2);
    clear_lines(3);
}

// Reads and sanitizes user input from the console
std::string GameInterface::manage_input()
{
    std::string input;
    std::getline(std::cin, input);

    // Remove trailing whitespace characters
    size_t end_pos = input.find_last_not_of(" \t\n\r");
    if (end_pos != std::string::npos)
    {
        input.erase(end_pos + 1);
    }
    else
    {
        input.clear();
    }
    return input;
}
