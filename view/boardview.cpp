#include "boardview.h"

#include "logic/board.h"
#include "player.h"

#include <QPainter>
#include <QPaintEvent>

BoardView::BoardView(QWidget *parent) : QWidget(parent)
{
}

BoardView::~BoardView()
{
    delete playerX_;
    delete playerY_;
    delete board_;
}

Player *BoardView::curPlayer()
{
    if(board_->curSide() == Board::X)
        return playerX_;
    else
        return playerY_;
}

void BoardView::paintEvent(QPaintEvent *pe)
{
    QPainter painter;
    painter.begin(this);

    painter.fillRect(pe->rect(), Qt::white);

    int w = pe->rect().width();
    int h = pe->rect().height();

    painter.drawLine(0, h / 3, w, h / 3);
    painter.drawLine(0, h * 2 / 3, w, h * 2 / 3);

    painter.drawLine(w / 3, 0, w / 3, h);
    painter.drawLine(2 * w / 3, 0, 2 * w / 3, h);

    if(board_) {
        for(int i = 0; i < 9; i++) {
            if(board_->side(i) == Board::X)
                drawX(pe, painter, i);
            else if(board_->side(i) == Board::Y)
                drawY(pe, painter, i);
        }
    }

    painter.end();
}

void BoardView::mousePressEvent(QMouseEvent *me)
{
    QPoint pos = me->pos();
    int w = this->width();
    int h = this->height();

    int dx = w / 3;
    int dy = h / 3;

    int cell = 3* (pos.y() / dy) + pos.x() / dx;

    if(UserPlayer* user = dynamic_cast<UserPlayer*>(curPlayer())) {
        user->mkStep(cell);
    }
}

void BoardView::drawX(QPaintEvent *pe, QPainter &p, int pos)
{
    int dx = pe->rect().width() / 3;
    int dy = pe->rect().height() / 3;

    int x = (pos % 3) * dx;
    int y = (pos / 3) * dy;

    p.drawLine(x,y, x+dx, y+dy);
    p.drawLine(x,y+dy,x+dx,y);
}

void BoardView::drawY(QPaintEvent *pe, QPainter &p, int pos)
{
    int dx = pe->rect().width() / 3;
    int dy = pe->rect().height() / 3;

    int x = (pos % 3) * dx;
    int y = (pos / 3) * dy;

    p.drawEllipse(x, y, dx, dy);
}

void BoardView::start(bool playerXIsBot, bool playerYIsBot)
{
    delete playerX_;
    delete playerY_;
    delete board_;

    board_ = new Board();

    if(playerXIsBot) {
        playerX_ = new BotPlayer(board_, Board::X, this);
    } else {
        playerX_ = new UserPlayer(board_, Board::X, this);
    }

    if(playerYIsBot) {
        playerY_ = new BotPlayer(board_, Board::Y, this);
    } else {
        playerY_ = new UserPlayer(board_, Board::Y, this);

    }

    connect(playerX_, SIGNAL(step(Player*, int)), SLOT(onStep(Player*,int)));
    connect(playerY_, SIGNAL(step(Player*,int)), SLOT(onStep(Player*,int)));

    curPlayer()->waitStep();

}

void BoardView::onStep(Player* player, int step)
{
    if(curPlayer() != player)
        return;

    if(!board_->mkStep(step))
        return;

    repaint();

    if(board_->finished()) {
        emit finished(board_->winner());
        return;
    }

    curPlayer()->waitStep();
}
