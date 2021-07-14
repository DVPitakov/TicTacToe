#include "board.h"
#include <QList>
#include <QDebug>

Board::Side Board::winner() const
{
    const int R = 3;
    const std::vector<std::vector<int>> rows = {
        {0,   1,     2},    //XXX
        {R,   1+R,   2+R},  //000
        {2*R, 1+2*R, 2+2*R},//000

        {0, R, 2*R},     //0X0
        {1, 1+R, 1+2*R}, //0X0
        {2, 2+R, 2+2*R}, //0X0

        {0, 1+R, 2+2*R}, //X00
        {2, 1+R, 2*R}    //0X0
                         //00X

    };

    qDebug() << cells_[0] << " " << cells_[1] << " " << cells_[2];
    qDebug() << cells_[3] << " " << cells_[4] << " " << cells_[5];
    qDebug() << cells_[6] << " " << cells_[7] << " " << cells_[8];


    for(std::vector<int> row: rows) {
        if((cells_[row[0]] == cells_[row[1]]) && (cells_[row[0]]) == cells_[row[2]]) {
            if(cells_[row[0]] == Side::X)
                return Side::X;
            if(cells_[row[0]] == Side::Y)
                return Side::Y;
        }
    }


    return Side::none;
}

Board::Side Board::curSide() const
{
    if(curStep_ % 2)
        return Y;
    else
        return X;
}

bool Board::finished() const
{
    if(winner() != none)
        return true;

    for(int i = 0; i < 9; i++) {
        if(cells_[i] == none)
            return false;
    }

    return true;
}

Board::Side Board::side(int pos) const
{
    if((pos >= 9) || (pos < 0))
        return Board::none;

    return cells_[pos];
}

bool Board::mkStep(int step)
{
    if(!stepIsValid(step))
        return false;

    cells_[step] = curSide();
    curStep_++;

    return true;

}

bool Board::stepIsValid(int step) const
{
    if(step >=9 || step < 0)
        return false;

    if(cells_[step] != none)
        return false;

    return true;
}

Board::Board()
{

}
