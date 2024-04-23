#ifndef MINESWEEPERBOARD_H
#define MINESWEEPERBOARD_H

#define MAX_SIZE 100
struct Field {
    bool hasMine;
    bool hasFlag;
    bool isRevealed;
};

enum GameMode { DEBUG, EASY, NORMAL, HARD };
enum GameState { RUNNING, FINISHED_WIN, FINISHED_LOSS };

class MinesweeperBoard {
        int cols;
        int rows;
        bool firstMove;
        GameMode mode;
        GameState state;
        Field data[MAX_SIZE][MAX_SIZE]{};
        int flagsRemaining;
        void change_location(int row, int col);
        void display_field(int row, int col) const;
        bool field_on_board(int row, int col) const;
        void gen_debug();
        void gen_rand_mines(int nMines);
        void gen_random_fields(int nMines);
        void generate_mines(GameMode mode);
        bool hasMine(int row, int col) const;
        bool isFinishedWin() const;
        void recursiveRevealField( int row, int col);
        void set_empty(int width, int height);
        void set_fields();

    public:
        MinesweeperBoard();
        MinesweeperBoard(int width, int height, GameMode mode);
        void restart();
        void debug_display() const;
        // simple getters - return appropriate values (passed to or calculated in constructor)
        int getBoardWidth() const;
        int getBoardHeight() const;
        int getMineCount() const;
        int getFlagsRemaining() const;

        // count mines around (row,col) position
        // if the field at (row,col) was not revealed - return -1
        // if either row or col is outside board      - return -1
        // otherwise - return mine count around this field
        // Examples for DEBUG layout on 10x10 board (assuming the field is already revealed)
        // - countMines(1,0) should return 4
        // - countMines(2,9) should return 0
        // - countMines(2,1) should return 3
        // - countMines(6,7) should return 2
        int countMines(int row, int col) const;

        // return true if the field at (row,col) position was marked with flag
        // return false if any of the following is true:
        // - row or col is outside board
        // - there is no flag on the field
        // - field was already revealed
        bool hasFlag(int row, int col) const;

        // if the field at (row,col) was not revealed - change flag status for this field
        // Do // try to reveal the field at (row,col)
        //        // Do nothing if any of the following is true
        //        // - field was already revealed
        //        // - either row or col is outside board
        //        // - game is already finished
        //        // - there is a flag on the field
        //        //
        //        // If the field was not revealed and there is no mine on it - reveal it
        //        // If the field was not revealed and there is a mine on it:
        //        // - if it's the first player action - move mine to another location, reveal field (not in DEBUG mode!)
        //        // - reveal it and finish game, nothing if any of the following is true
        // - field was already revealed
        // - either row or col is outside board
        // - game is already finished
        void toggleFlag(int row, int col);


        void revealField(int row, int col);

        // return true if the field was revealed
        // return false if the field is not revealed or if it is outside the board
        bool isRevealed(int row, int col) const;

        // return current game state:
        // - FINISHED_LOSS - if the player revealed field with mine
        // - FINISHED_WIN  - if the player won the game (all unrevealed fields have mines)
        // - RUNNING       - if the game is not yet finished
        GameState getGameState() const;

        // convenience function - returns useful information about field in one function call
        // if row or col is outside board                         - return '#' character
        // if the field is not revealed and has a flag            - return 'F' character
        // if the field is not revealed and does not have a flag  - return '_' (underscore) character
        // if the field is revealed and has mine                  - return 'x' character
        // if the field is revealed and has 0 mines around        - return ' ' (space) character
        // if the field is revealed and has some mines around     - return '1' ... '8' (number of mines as a digit)
        char getFieldInfo(int row, int col) const;
};

#endif //MINESWEEPERBOARD_H
