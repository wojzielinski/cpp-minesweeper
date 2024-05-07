#include <iostream>

#include "MSTextController.h"

//PRIVATE
//===============

//Gets user input - player choose action (reveal, flag, display)
Action MSTextController::choose_action() {
    char choice[2];
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1. Flag field" << std::endl;
    std::cout << "2. Reveal field" << std:: endl;
    std::cout << "3. Display board" << std:: endl;
    std::cout << "Your choice (F/R/D): ";
    std::cin >> choice;
    switch (tolower(choice[0])) {
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

//Text controller constructor
MSTextController::MSTextController(MinesweeperBoard & boardRef, MSBoardTextView & viewRef) : board(boardRef), view(viewRef)
{
    //Sets board and view reference
}

//Runs game as long as game is running
void MSTextController::play() {
    while(board.getGameState() == GameState::RUNNING){
        view.display();
        Action action = choose_action();
        int row, col;

        switch (action){                                    //Get user input
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
    print_gamestate();
}

//Prints game state
void MSTextController::print_gamestate() const {
    GameState state = board.getGameState();
    switch (state) {
        case GameState::RUNNING:
            std::cout << "Game is currently running." << std::endl;
            break;
        case GameState::FINISHED_LOSS:
            std::cout << "Game over :c" << std::endl;
            break;
        case GameState::FINISHED_WIN:
            std::cout << "You won!" << std::endl;
            break;
        default:
            std::cout << "Couldn't fetch current game state" << std::endl;
    }
}