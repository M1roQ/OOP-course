#include "GameOfLife.hpp"

// Constructor: Initializes the game engine using the provided GameState reference and number of iterations
GameEngine::GameEngine(GameState &ReceivedGameState, int iterations)
    : CurrentGameState(ReceivedGameState),
      received_number_of_iterations(iterations)
{
}

// Updates the game field based on the rules of the game for a set number of iterations
void GameEngine::UpdateGameState() {
    int rows = CurrentGameState.get_size();
    int cols = CurrentGameState.get_size();

    for (int i = 0; i < received_number_of_iterations; ++i) {
        Field currentField = CurrentGameState.get_field();
        Field newField = currentField;  // Copy the current field into a new one

        std::set<int> B_conditions = CurrentGameState.get_B_conditions();
        std::set<int> S_conditions = CurrentGameState.get_S_conditions();

        // Process the update of cells
        for (int x = 0; x < rows; ++x) {
            for (int y = 0; y < cols; ++y) {
                int neighbors = countNeighbors(currentField, x, y);

                if (currentField[x][y]) {  // If the cell is alive
                    newField[x][y] = S_conditions.count(neighbors) > 0;  // Alive cells remain alive if they have the correct number of neighbors
                } else {  // If the cell is dead
                    newField[x][y] = B_conditions.count(neighbors) > 0;  // Dead cells come to life if they have the correct number of neighbors
                }
            }
        }

        // Update the game state with the new field after all calculations
        CurrentGameState.set_field(newField);
    }

    // Update the number of iterations
    CurrentGameState.set_count_of_iterations(CurrentGameState.get_count_of_iterations() + received_number_of_iterations);
}

// Counts how many living neighbors the cell at position (x, y) has
int GameEngine::countNeighbors(const Field &field, int x, int y)
{
    int rows = field.size();
    int cols = field[0].size();
    int count = 0;

    // Define relative positions for all 8 possible neighboring cells
    std::vector<std::pair<int, int>> dir = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    // For each neighbor, calculate its position and check if it is within bounds
    for (const auto &[dx, dy] : dir)
    {
        int nx = (x + dx + rows) % rows; // Vertical wrap-around
        int ny = (y + dy + cols) % cols; // Horizontal wrap-around

        // If the neighbor is alive, increase the count of living neighbors
        if (field[nx][ny]) 
        {
            ++count;
        }
    }

    // Return the total number of living neighbors
    return count;
}
