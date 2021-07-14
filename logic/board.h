#ifndef BOARD_H
#define BOARD_H

#include <QSharedPointer>

class Board
{
public:
    typedef QSharedPointer<Board> ptr;

    enum Side {
        none = '\0',
        X = 'w',
        Y = 'b',
    };

    Side winner() const;
    Side curSide() const;
    bool finished() const;
    Side side(int pos) const;

    Side const * cells() const;
    bool stepIsValid(int step) const;

    bool mkStep(int step);

    Board();

private:


    int curStep_{0};
    Side cells_[9] = {none,};

};

#endif // BOARD_H
