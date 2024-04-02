#include <iostream>

#include "MSTextController.h"

//PRIVATE
//===============
Action MSTextController::choose_action() {
    char choice;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1. Flag field" << std::endl;
    std::cout << "2. Reveal field" << std:: endl;
    std::cout << "3. Display board" << std:: endl;
    std::cout << "Your choice (F/R/D): ";
    std::cin >> choice;
    switch (tolower(choice)) {
        case 'f':
            return Action::FLAG;
        case 'r':
            return Action::REVEAL;
        case 'd':
            return Action::DISPLAY;
        default:
            std::cout << "Unrecognized option. Type F, R or D." << std::endl;
            return choose_action();
    }
}
//PUBLIC
//===============
MSTextController::MSTextController(MinesweeperBoard & boardRef, MSBoardTextView & viewRef) : board(boardRef), view(viewRef)
{

}

void MSTextController::play() {
    while(board.getGameState() == GameState::RUNNING){
        view.display();
        Action action = choose_action();
        int row, col;

        switch (action) {
            case Action::FLAG:
                std::cout << "Choose row and col: ";
                std::cin >> row;
                std::cin >> col;
                board.toggleFlag(row,col);
                break;
            case Action::REVEAL:
                std::cout << "Choose row and col: ";
                std::cin >> row;
                std::cin >> col;
                board.revealField(row,col);
                break;
            default:
                break;
        }

    }
}