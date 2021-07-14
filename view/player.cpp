#include "player.h"
#include "logic/board.h"

Player::Player(const Board *board, Board::Side side, QObject *parent) : QObject(parent),
    board_(board),
    side_(side)
{

}

UserPlayer::UserPlayer(const Board *board, Board::Side side, QObject *parent):
    Player(board, side, parent)
{

}

void UserPlayer::waitStep()
{

}

void UserPlayer::mkStep(int step)
{
    emit this->step(this, step);
}

BotPlayer::BotPlayer(const Board *board, Board::Side side, QObject *parent):
    Player(board, side, parent)
{

}

void BotPlayer::waitStep()
{
    for(int i = 0; i < 9; i++) {
        if(board_->stepIsValid(i)) {
            emit step(this, i);
            return;
        }
    }
}
