#include <cstdlib>

const int Height = 27, Width = 21;  // The default Height and the Width of the map

const char Save_Map[Height + 2][Width + 2] = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '#'},
    {'#', '#', '.', '#', '#', '#', '.', '#', '#', '#', '.', '#', '.', '#', '#', '#', '.', '#', '#', '#', '.', '#', '#'},
    {'#', '#', '@', '#', ' ', '#', '.', '#', ' ', '#', '.', '#', '.', '#', ' ', '#', '.', '#', ' ', '#', '@', '#', '#'},
    {'#', '#', '.', '#', '#', '#', '.', '#', '#', '#', '.', '#', '.', '#', '#', '#', '.', '#', '#', '#', '.', '#', '#'},
    {'#', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '#'},
    {'#', '#', '.', '#', '#', '#', '.', '#', '.', '#', '#', '#', '#', '#', '.', '#', '.', '#', '#', '#', '.', '#', '#'},
    {'#', '#', '.', '#', '#', '#', '.', '#', '.', '#', '#', '#', '#', '#', '.', '#', '.', '#', '#', '#', '.', '#', '#'},
    {'#', '#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '#', '#'},
    {'#', '#', '#', '#', '#', '#', '.', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '.', '#', '#', '#', '#', '#', '#'},
    {'#', ' ', ' ', ' ', ' ', '#', '.', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '.', '#', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', '#', '.', '#', ' ', '#', '#', ' ', '#', '#', ' ', '#', '.', '#', ' ', ' ', ' ', ' ', '#'},
    {'#', '#', '#', '#', '#', '#', '.', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', '.', '#', '#', '#', '#', '#', '#'},
    {' ', ' ', ' ', ' ', ' ', ' ', '.', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '.', ' ', ' ', ' ', ' ', ' ', ' '},
    {'#', '#', '#', '#', '#', '#', '.', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', '.', '#', '#', '#', '#', '#', '#'},
    {'#', ' ', ' ', ' ', ' ', '#', '.', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '.', '#', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', '#', '.', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', '.', '#', ' ', ' ', ' ', ' ', '#'},
    {'#', '#', '#', '#', '#', '#', '.', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', '.', '#', '#', '#', '#', '#', '#'},
    {'#', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '#'},
    {'#', '#', '.', '#', '#', '#', '.', '#', '#', '#', '.', '#', '.', '#', '#', '#', '.', '#', '#', '#', '.', '#', '#'},
    {'#', '#', '@', '.', '.', '#', '.', '.', '.', '.', '.', ' ', '.', '.', '.', '.', '.', '#', '.', '.', '@', '#', '#'},
    {'#', '#', '#', '#', '.', '#', '.', '#', '.', '#', '#', '#', '#', '#', '.', '#', '.', '#', '.', '#', '#', '#', '#'},
    {'#', '#', '#', '#', '.', '#', '.', '#', '.', '#', '#', '#', '#', '#', '.', '#', '.', '#', '.', '#', '#', '#', '#'},
    {'#', '#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '#', '#'},
    {'#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '.', '#', '.', '#', '#', '#', '#', '#', '#', '#', '.', '#', '#'},
    {'#', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
     '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}};
// The main map of the Pac-man

const int Pic[5] = {' ', '^', 'v', '<', '>'};  // The icon of the cursor

const int Move[5][2] = {{0, 0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};  // Direction of the movements

int Score;

int Map[Height + 2][Width + 2];  // Use it when the game restart

struct COORD {
    int X, Y;
};

struct Character {
    int X, Y, Direction, locked, Color, Timer;
} PacMan, Ghost[5], Save_Ghost[5];

bool Turnings[Height + 1][Width + 1];  // Save Turnings

int Strong_Time, life, beans, level;

inline bool Check_Turning(int x, int y, int a, int b) {
    return Map[x][y] ^ '#' && Map[a][b] ^ '#';
}  // Check whether it's a turning

inline void Load_Data(void) {
    Save_Ghost[1] = Character{13, 11, 1, 0, 31, 0};
    Save_Ghost[2] = Character{14, 10, 1, 3, 36, 0};
    Save_Ghost[3] = Character{14, 11, 2, 10, 33, 0};
    Save_Ghost[4] = Character{14, 12, 1, 15, 35, 0};
    // Process the Ghost

    Score = 0, life = 3, level = 1;  // Reset the Score, life and the level

    for (int i = 1; i <= Height; i++)
        for (int j = 1; j <= Width; j++) {
            bool sum = false;  // Check it's or not turning

            if (Check_Turning(i - 1, j, i, j - 1)) sum = true;
            if (Check_Turning(i - 1, j, i, j + 1)) sum = true;
            if (Check_Turning(i + 1, j, i, j - 1)) sum = true;
            if (Check_Turning(i + 1, j, i, j + 1)) sum = true;
            // Rules to check turning

            Turnings[i][j] = sum;
        }
    // Search the Turnings
}

inline void Data_Processing(int temp) {
    PacMan = Character{21, 11, 1, PacMan.locked, 33, 0};

    for (int i = 1; i < 5; i++) Ghost[i] = Save_Ghost[i];
    Ghost[1].X = 11, Ghost[3].X = 13;

    if (!temp) {
        PacMan.locked = 5;
        return;
    }

    beans = 188;  // Reset the number of the bean

    for (int i = 0; i <= Height + 1; i++)
        for (int j = 0; j <= Width + 1; j++) Map[i][j] = Save_Map[i][j];
    // Give "Save" to "Map" (Restore data)
}  // Process the base data