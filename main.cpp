#include <iostream>
#define MAX_SIZE 100
struct Field {
    bool hasMine;
    bool hasFlag;
    bool isRevealed;
};

class MinesweeperBoard {
    private:
        int cols;
        int rows;
        Field data[MAX_SIZE][MAX_SIZE];
        void set_fields();
        void display_field(int, int) const;
    public:
        MinesweeperBoard();
        void debug_display() const;
};

void MinesweeperBoard::set_fields() {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            data[row][col].hasFlag = false;
            data[row][col].hasMine = false;
            data[row][col].isRevealed = false;
        }
    };
    data[0][0].hasMine = true;
    data[0][0].hasFlag = false;
    data[1][1].isRevealed = true;
    data[0][2].hasMine = true;
    data[0][2].hasFlag = true;
    data[3][4].hasFlag = true;
    data[3][4].hasMine = true;
    data[3][4].isRevealed = true;
}

void MinesweeperBoard::display_field(int row, int col) const{
    std::cout << "[" << (data[row][col].hasMine?"M":".");
    std::cout << (data[row][col].isRevealed?"o":".");
    std::cout << (data[row][col].hasFlag?"f":".");
    std::cout << "] ";
}

MinesweeperBoard::MinesweeperBoard(){
    cols = 7;
    rows = 6;
    if(rows <= MAX_SIZE && cols <= MAX_SIZE){
        set_fields();
    }
}

void MinesweeperBoard::debug_display() const {
    std::cout << "      ";
    for(int a=0; a<cols;a++){
        std::cout << a << "     ";
    }
    std::cout << std::endl;

    for (int row = 0; row < rows; row++) {
        std::cout << row <<"\t";
        for (int col=0; col < cols; col++) {
            this->display_field(row,col);
        }
        std::cout << std::endl;
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    MinesweeperBoard board;
    board.debug_display();
    return 0;
}
