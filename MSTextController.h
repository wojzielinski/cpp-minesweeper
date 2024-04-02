#ifndef SAPER_MSTEXTCONTROLLER_H
#define SAPER_MSTEXTCONTROLLER_H
#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"

enum Action { FLAG , REVEAL , DISPLAY };

class MSTextController {
        MinesweeperBoard & board;
        MSBoardTextView & view;
        Action choose_action();

    public:
        MSTextController( MinesweeperBoard & boardRef, MSBoardTextView & viewRef );
        void play();
        void print_gamestate() const;
};


#endif //SAPER_MSTEXTCONTROLLER_H
