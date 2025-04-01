#include "GameOfLife.hpp"

// Constructor that initializes the file name
ParserFile::ParserFile(const std::string &file_name) : file_name(file_name) {}

// Main method to parse the input file and update the game state
void ParserFile::parse(GameState &game_state)
{
    std::ifstream file(file_name);
    if (!file.is_open())
    {
        std::cerr << "\033[31m" << "Error: File could not be opened: " << file_name << "\033[0m" << std::endl;
        
        std::cout << "Opening a random file" << std::endl;
        std::cerr << "Press ENTER to continue...";
        std::string input2;
        std::getline(std::cin, input2);
        file.open(launch_random_file());
    }

    std::string line;
    int line_number = 0;
    while (std::getline(file, line))
    {
        line_number++;
        if (line.empty())  // Skip empty lines
            continue;

        try {
            if (line.rfind("#Life", 0) == 0)  // Parse the game version
            {
                if (line.size() < 6) {
                    throw std::invalid_argument("Invalid #Life line format");
                }
                std::string version = line.substr(6);
                game_state.set_game_version(version);
            }
            else if (line.rfind("#N", 0) == 0)  // Parse the universe name
            {
                if (line.size() < 4) {
                    std::cerr << "Warning: Invalid #N line format, using default universe name." << std::endl;
                    std::cerr << "Press ENTER to continue...";
                    std::string input2;
                    std::getline(std::cin, input2);
                    game_state.set_universe_name("Default Universe");
                } else {
                    std::string universe_name = line.substr(3);
                    game_state.set_universe_name(universe_name);
                }
            }
            else if (line.rfind("#Size", 0) == 0)  // Parse the size of the game field
            {
                if (line.size() < 6) {
                    std::cerr << "\033[31m" << "Error: Invalid #Size line format." << "\033[0m" << std::endl;
                    std::cout << "Opening a random file" << std::endl;
                    file.close(); 
                    file.open(launch_random_file());
                    parse(game_state);  
                    std::cerr << "Press ENTER to continue...";
                    std::string input2;
                    std::getline(std::cin, input2);
                    
                    return;
                } else {
                    int size = std::stoi(line.substr(6));
                    game_state.set_size(size);
                }
            }
            else if (line.rfind("#R", 0) == 0)  // Parse the game conditions
            {
                std::string conditions = line.substr(3);

                if (conditions.empty() || !std::regex_match(conditions, std::regex("^B[0-9]+/S[0-9]+$"))) {
                     std::cerr << "Warning: Invalid #R line format, using default conditions." << std::endl;
                    std::cerr << "Press ENTER to continue...";
                    std::string input2;
                    std::getline(std::cin, input2);
                    conditions = "B2/S23";
                }
                parse_conditions(conditions, game_state);
            }
            else  // Coordinates of live cells
            {
                parse_coordinates(line, game_state);
            }
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << " at line " << line_number << std::endl;
            file.close(); 
            file.open(launch_random_file()); 

            if (!file.is_open()) {
                std::cerr << "Failed to open the random file!" << std::endl;
                return;  
            }

            parse(game_state); 
            return; 
        }
    }
}

std::string ParserFile::launch_random_file()
{
    if (chdir("../games") != 0) {
        std::cerr << "Error: Could not change directory to ../games" << std::endl;
        return "";  // Return an empty string if the directory change fails
    }

    // Define a list of predefined game files
    const std::string filenames[] = {"glider.live", "game2.live", "game3.live", "buterfly.live", "game5.live"};

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());  // Mersenne Twister generator
    std::uniform_int_distribution<> distrib(0, 4); // Uniform distribution between 0 and 4
    int random_number = distrib(gen); // Generate random number

    // Select a random file from the list
    std::string generated_file = filenames[random_number];

    std::cout << "Open file :" << generated_file << std::endl;
    return generated_file;
}

// Parses the conditions string for Birth (B) and Survival (S) conditions
void ParserFile::parse_conditions(const std::string &conditions, GameState &game_state)
{
    std::set<int> B_conditions;
    std::set<int> S_conditions;

    size_t B_pos = conditions.find('B');  // Find the start of the Birth conditions
    size_t S_pos = conditions.find('S');  // Find the start of the Survival conditions

    if (B_pos == std::string::npos && S_pos == std::string::npos) {
        throw std::invalid_argument("Invalid format in conditions string: " + conditions);
    }

    if (B_pos != std::string::npos) {
        std::string B = conditions.substr(B_pos + 1, S_pos - B_pos - 1);  // Extract Birth conditions
        parse_condition_set(B, B_conditions);
    }

    if (S_pos != std::string::npos) {
        std::string S = conditions.substr(S_pos + 1);  // Extract Survival conditions
        parse_condition_set(S, S_conditions);
    }

    game_state.set_B_conditions(B_conditions);
    game_state.set_S_conditions(S_conditions);
}


// Parses a set of conditions (either Birth or Survival) and stores them in a set
void ParserFile::parse_condition_set(const std::string &condition_str, std::set<int> &condition_set)
{
    for (char ch : condition_str)
    {
        if (std::isdigit(ch))  // If the character is a digit, add it to the set
        {
            condition_set.insert(ch - '0');
        }
    }
}

// Parses the coordinates of live cells and updates the game state
void ParserFile::parse_coordinates(const std::string &line, GameState &game_state)
{
    std::istringstream stream(line);
    int row, col;

    Field field = game_state.get_field();
    int size = game_state.get_size();
    if (field.size() != size)  // If the field size doesn't match the specified size, resize it
    {
        field.resize(size, std::vector<bool>(size, false));
    }

    std::set<std::pair<int, int>> seen_coordinates;  // Track coordinates to avoid duplicates

    while (!stream.eof()) {
        if (!(stream >> row)) {
            std::cerr << "Warning: Missing or invalid row value in line:" << line << ". The value will be ignored." << std::endl;
            break; 
        }

        if (!(stream >> col)) {
            std::cerr << "Warning: Missing column value for row " << row << " in line:" << line << ". The value will be ignored." << std::endl;
            break; 
        }

        if (row <= 0 || col <= 0 || row > size || col > size) {
            std::cerr << "Warning: Coordinate values out of bounds (" 
                    << row << ", " << col << ") in line: " << line << std::endl;
            continue; 
        }

        std::pair<int, int> current_coord = {row, col};

        if (seen_coordinates.find(current_coord) == seen_coordinates.end()) {
            field[row - 1][col - 1] = true;
            seen_coordinates.insert(current_coord);
        } else {
        std::cerr << "Warning: Duplicate coordinates (" << row << ", " << col << ") ignored." << std::endl;
        }
    }

    game_state.set_field(field);  // Update the game state
}

