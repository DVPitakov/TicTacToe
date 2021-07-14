#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "logic/board.h"

class Player : public QObject
{
    Q_OBJECT
public:
    Player(const Board* board, Board::Side side, QObject *parent = nullptr);

signals:
    void step(Player* player, int step);

public slots:
    virtual void waitStep() = 0;

protected:
    const Board* board_;
    Board::Side side_;
};

class UserPlayer: public Player {
    Q_OBJECT
public:
    UserPlayer(const Board* board, Board::Side side, QObject *parent = nullptr);
public slots:
    void waitStep() override;
    void mkStep(int step);
};

class BotPlayer: public Player {
    Q_OBJECT
public:
    BotPlayer(const Board* board, Board::Side side, QObject *parent = nullptr);
public slots:
    void waitStep() override;
};

#endif // PLAYER_H
