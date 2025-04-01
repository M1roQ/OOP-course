#include "../lib/GameOfLife.hpp"
#include <gtest/gtest.h>

// Test for valid arguments in single mode (no iterations and no output file)
TEST(CommandLineParserTest, ValidArgumentsInSingleMode)
{
    const char *argv[] = {"program_name", "example.live"};
    int argc = 2;

    ParserCommandLine command_line_parser(argc, const_cast<char **>(argv));

    EXPECT_EQ(command_line_parser.get_mode(), '1');  // Mode should be '1'
    EXPECT_EQ(command_line_parser.get_input_file(), "example.live");  // Input file should be "example.live"
    EXPECT_THROW(command_line_parser.get_output_file(), std::logic_error);  // Output file should throw exception
    EXPECT_THROW(command_line_parser.get_iterations(), std::logic_error);  // Iterations should throw exception
}

// Test for invalid file extension in single mode
TEST(CommandLineParserTest, InvalidArgumentsInSingleMode)
{
    const char *argv[] = {"program_name", "example.liv"};
    int argc = 2;

    EXPECT_THROW(ParserCommandLine command_line_parser(argc, const_cast<char **>(argv)), std::invalid_argument);  // Should throw exception for invalid file format
}

// Test for valid arguments in mode with iterations and output file
TEST(CommandLineParserTest, ValidArgumentsInModeWithIterations)
{
    const char *argv[] = {"program_name", "example.live", "-i", "10", "-o", "output.live"};
    int argc = 6;

    ParserCommandLine command_line_parser(argc, const_cast<char **>(argv));

    EXPECT_EQ(command_line_parser.get_mode(), '3');  // Mode should be '3'
    EXPECT_EQ(command_line_parser.get_input_file(), "example.live");  // Input file should be "example.live"
    EXPECT_EQ(command_line_parser.get_output_file(), "output.live");  // Output file should be "output.live"
    EXPECT_EQ(command_line_parser.get_iterations(), 10);  // Iterations should be 10
}

// Test for valid arguments with different order of parameters
TEST(CommandLineParserTest, ValidArgumentsInModeWithDifferentOrder)
{
    const char *argv[] = {"program_name", "example.live", "-o", "output.live", "-i", "10"};
    int argc = 6;

    ParserCommandLine command_line_parser(argc, const_cast<char **>(argv));

    EXPECT_EQ(command_line_parser.get_mode(), '3');  // Mode should be '3'
    EXPECT_EQ(command_line_parser.get_input_file(), "example.live");  // Input file should be "example.live"
    EXPECT_EQ(command_line_parser.get_output_file(), "output.live");  // Output file should be "output.live"
    EXPECT_EQ(command_line_parser.get_iterations(), 10);  // Iterations should be 10
}

// Test for invalid iterations format (non-numeric value)
TEST(CommandLineParserTest, InvalidIterationsFormat)
{
    const char *argv[] = {"program_name", "example.live", "-i", "10kf", "-o", "output.live"};
    int argc = 6;

    EXPECT_THROW(ParserCommandLine command_line_parser(argc, const_cast<char **>(argv)), std::invalid_argument);  // Should throw exception for invalid iteration format
}

// Test for valid "dump" command
TEST(CommandParserTest, CorrectDumpCommand)
{
    std::string command = "dump example.live";

    ParserCommands command_parser;
    command_parser.parse_command(command);

    EXPECT_EQ(command_parser.get_command(), '1');  // Command should be '1' (dump)
    EXPECT_EQ(command_parser.get_filename(), "example.live");  // Filename should be "example.live"
    EXPECT_THROW(command_parser.get_iterations(), std::runtime_error);  // Iterations should throw exception
}

// Test for invalid "dump" command (incorrect file or missing file)
TEST(CommandParserTest, IncorrectDumpCommand)
{
    std::string command1 = "dump example.liv";
    std::string command2 = "dump";

    ParserCommands command_parser;

    EXPECT_THROW(command_parser.parse_command(command1), std::runtime_error);  // Should throw exception for invalid file extension
    EXPECT_THROW(command_parser.parse_command(command2), std::runtime_error);  // Should throw exception for missing filename
}

// Test for correct "tick" command with iterations
TEST(CommandParserTest, CorrectTickCommand)
{
    std::string command1 = "tick 20";
    std::string command2 = "t 20";
    std::string command3 = "tick";
    std::string command4 = "t";

    ParserCommands command_parser;

    command_parser.parse_command(command1);
    EXPECT_EQ(command_parser.get_command(), '2');  // Command should be '2' (tick)
    EXPECT_THROW(command_parser.get_filename(), std::runtime_error);  // Filename should throw exception
    EXPECT_EQ(command_parser.get_iterations(), 20);  // Iterations should be 20

    command_parser.parse_command(command2);
    EXPECT_EQ(command_parser.get_command(), '2');  // Command should be '2' (tick)
    EXPECT_THROW(command_parser.get_filename(), std::runtime_error);  // Filename should throw exception
    EXPECT_EQ(command_parser.get_iterations(), 20);  // Iterations should be 20

    command_parser.parse_command(command3);
    EXPECT_EQ(command_parser.get_command(), '2');  // Command should be '2' (tick)
    EXPECT_THROW(command_parser.get_filename(), std::runtime_error);  // Filename should throw exception
    EXPECT_EQ(command_parser.get_iterations(), 1);  // Default iterations should be 1

    command_parser.parse_command(command4);
    EXPECT_EQ(command_parser.get_command(), '2');  // Command should be '2' (tick)
    EXPECT_THROW(command_parser.get_filename(), std::runtime_error);  // Filename should throw exception
    EXPECT_EQ(command_parser.get_iterations(), 1);  // Default iterations should be 1
}

// Test for invalid "tick" command (wrong format or invalid arguments)
TEST(CommandParserTest, InvalidTickCommand)
{
    std::string command1 = "tik";
    std::string command2 = "52 tick";
    std::string command3 = "tick 0";
    std::string command4 = "tick 2df";

    ParserCommands command_parser;
    EXPECT_THROW(command_parser.parse_command(command1), std::runtime_error);  // Invalid command format
    EXPECT_THROW(command_parser.parse_command(command2), std::runtime_error);  // Invalid command format
    EXPECT_THROW(command_parser.parse_command(command3), std::runtime_error);  // Iterations cannot be 0
    EXPECT_THROW(command_parser.parse_command(command4), std::runtime_error);  // Invalid iteration format
}

// Test for valid "exit" command
TEST(CommandParserTest, CorrectExitCommand)
{
    std::string command1 = "exit";

    ParserCommands command_parser;
    command_parser.parse_command(command1);

    EXPECT_EQ(command_parser.get_command(), '3');  // Command should be '3' (exit)
    EXPECT_THROW(command_parser.get_filename(), std::runtime_error);  // Filename should throw exception
    EXPECT_THROW(command_parser.get_iterations(), std::runtime_error);  // Iterations should throw exception
}

// Test for invalid "exit" command (extra arguments)
TEST(CommandParserTest, InvalidExitCommand)
{
    std::string command1 = "exit  ";

    ParserCommands command_parser;
    EXPECT_THROW(command_parser.parse_command(command1), std::runtime_error);  // Should throw exception for extra space
    EXPECT_THROW(command_parser.get_iterations(), std::runtime_error);  // Iterations should throw exception
    EXPECT_THROW(command_parser.get_filename(), std::runtime_error);  // Filename should throw exception
}

// Test for valid "help" command
TEST(CommandParserTest, CorrectHelpCommand)
{
    std::string command1 = "help";

    ParserCommands command_parser;
    command_parser.parse_command(command1);

    EXPECT_EQ(command_parser.get_command(), '4');  // Command should be '4' (help)
    EXPECT_THROW(command_parser.get_filename(), std::runtime_error);  // Filename should throw exception
    EXPECT_THROW(command_parser.get_iterations(), std::runtime_error);  // Iterations should throw exception
}

// Test for invalid "help" command (extra spaces)
TEST(CommandParserTest, InvalidHelpCommand)
{
    std::string command1 = "  help  ";

    ParserCommands command_parser;
    EXPECT_THROW(command_parser.parse_command(command1), std::runtime_error);  // Should throw exception for extra spaces
    EXPECT_THROW(command_parser.get_iterations(), std::runtime_error);  // Iterations should throw exception
    EXPECT_THROW(command_parser.get_filename(), std::runtime_error);  // Filename should throw exception
}

// Test for correct file parsing
TEST(FileParserTest, CorrectFileParsing)
{
    std::string file = "../../games/test_universe.live";

    std::ifstream test_file(file);
    ASSERT_TRUE(test_file.is_open()) << "File not found: " << file;

    GameState game;
    ParserFile file_parser(file);

    std::string expected_version = "1.06";
    std::string expected_universe = "test_universe";
    int expected_size = 30;
    std::set<int> expected_B = {2};
    std::set<int> expected_S = {1, 2};

    EXPECT_NO_THROW(file_parser.parse(game));  // Parsing should succeed

    EXPECT_EQ(game.get_game_version(), expected_version);  // Game version should be correct
    EXPECT_EQ(game.get_universe_name(), expected_universe);  // Universe name should be correct
    EXPECT_EQ(game.get_size(), expected_size);  // Size should be correct
    EXPECT_EQ(game.get_B_conditions(), expected_B);  // B condition should match
    EXPECT_EQ(game.get_S_conditions(), expected_S);  // S condition should match
}

// Test for incorrect file parsing (invalid format)
TEST(FileParserTest, IncorrectFileParsing)
{
    std::string file = "../../games/incorrect_file.live";

    std::ifstream test_file(file);
    ASSERT_TRUE(test_file.is_open()) << "File not found: " << file;

    GameState game;
    ParserFile file_parser(file);

    EXPECT_THROW(file_parser.parse(game), std::invalid_argument);  // Should throw exception for incorrect file format
}

// Test for GameEngine constructor
TEST(GameEngineTest, ConstructorTest)
{
    GameState gameState;
    GameEngine engine(gameState, 5);

    EXPECT_EQ(gameState.get_count_of_iterations(), 0);  // Iterations should initially be 0
}

// Test for counting neighbors around a cell
TEST(GameEngineTest, CountNeighborsTest)
{
    GameState gameState;
    GameEngine engine(gameState, 1);

    Field testField = {
        {false, false, false},
        {false, true, false},
        {false, false, false}
    };

    int count = engine.countNeighbors(testField, 1, 1);
    EXPECT_EQ(count, 0);  // Center cell has no neighbors

    testField[0][0] = true;
    testField[0][1] = true;
    testField[1][0] = true;
    count = engine.countNeighbors(testField, 0, 0);  // Top-left corner cell
    EXPECT_EQ(count, 3);  // 3 live neighbors
}

// Test for updating the game state with one iteration
TEST(GameEngineTest, UpdateGameStateOneIteration)
{
    GameState gameState;

    Field initialField = {
        {false, false, false},
        {false, true, false},
        {false, false, false}
    };
    gameState.set_field(initialField);
    gameState.set_B_conditions({3});
    gameState.set_S_conditions({2, 3});

    GameEngine engine(gameState, 1);

    engine.UpdateGameState();

    Field updatedField = gameState.get_field();
    EXPECT_TRUE(updatedField[1][1]);  // The center cell should still be alive
}

// Test for edge wrapping behavior
TEST(GameEngineTest, EdgeWrappingTest)
{
    GameState gameState;

    Field testField = {
        {true, false, true},
        {false, false, false},
        {true, false, true}
    };
    gameState.set_field(testField);
    gameState.set_B_conditions({3});
    gameState.set_S_conditions({2, 3});

    GameEngine engine(gameState, 1);

    engine.UpdateGameState();

    Field updatedField = gameState.get_field();
    EXPECT_TRUE(updatedField[0][0]);  // Top-left corner should remain alive
    EXPECT_TRUE(updatedField[0][2]);  // Top-right corner should remain alive
    EXPECT_TRUE(updatedField[2][0]);  // Bottom-left corner should remain alive
    EXPECT_TRUE(updatedField[2][2]);  // Bottom-right corner should remain alive
}

// Test for no live cells scenario
TEST(GameEngineTest, NoLiveCellsTest)
{
    GameState gameState;

    Field testField = {
        {false, false, false},
        {false, false, false},
        {false, false, false}
    };
    gameState.set_field(testField);
    gameState.set_B_conditions({3});
    gameState.set_S_conditions({2, 3});

    GameEngine engine(gameState, 1);

    engine.UpdateGameState();

    Field updatedField = gameState.get_field();
    for (const auto &row : updatedField)
    {
        for (bool cell : row)
        {
            EXPECT_FALSE(cell);  // All cells should remain dead
        }
    }
}

// Full game test to verify evolution of cell states
TEST(GameEngineTest, GameTest) {
    std::vector<std::vector<bool>> initialState(20, std::vector<bool>(20, false));

    initialState[2][4] = true;
    initialState[3][5] = true;
    initialState[3][6] = true;
    initialState[4][3] = true;
    initialState[4][4] = true;
    initialState[5][5] = true;
    initialState[5][13] = true;
    initialState[6][13] = true;
    initialState[7][13] = true;
    initialState[9][9] = true;
    initialState[9][10] = true;
    initialState[9][11] = true;
    initialState[9][15] = true;
    initialState[9][16] = true;
    initialState[9][17] = true;
    initialState[11][13] = true;
    initialState[12][13] = true;
    initialState[13][13] = true;
    initialState[16][4] = true;
    initialState[16][5] = true;
    initialState[17][5] = true;
    initialState[18][2] = true;
    initialState[19][2] = true;
    initialState[19][3] = true;

    std::set<int> B_conditions = {3};
    std::set<int> S_conditions = {2, 3};

    GameState gameState;
    gameState.set_size(20);
    gameState.set_field(initialState);
    gameState.set_B_conditions(B_conditions);
    gameState.set_S_conditions(S_conditions);
    gameState.set_count_of_iterations(0);

    GameEngine engine(gameState, 1);

    auto initialGameState = gameState.get_field();

    engine.UpdateGameState();

    std::vector<std::vector<bool>> expectedState(20, std::vector<bool>(20, false));

    expectedState[2][5] = true;
    expectedState[3][3] = true;
    expectedState[3][5] = true;
    expectedState[4][4] = true;
    expectedState[4][6] = true;
    expectedState[5][4] = true;
    expectedState[6][12] = true;
    expectedState[6][13] = true;
    expectedState[6][14] = true;
    expectedState[8][10] = true;
    expectedState[8][16] = true;
    expectedState[9][10] = true;
    expectedState[9][16] = true;
    expectedState[10][10] = true;
    expectedState[10][16] = true;
    expectedState[12][12] = true;
    expectedState[12][13] = true;
    expectedState[12][14] = true;
    expectedState[16][4] = true;
    expectedState[16][5] = true;
    expectedState[17][4] = true;
    expectedState[17][5] = true;
    expectedState[18][2] = true;
    expectedState[18][3] = true;
    expectedState[19][2] = true;
    expectedState[19][3] = true;

    EXPECT_EQ(gameState.get_field(), expectedState);  // Compare game state after update with expected state
}
