#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QWidget>

#include "player.h"

class Board;
class BoardView : public QWidget
{
    Q_OBJECT
public:
    explicit BoardView(QWidget *parent = nullptr);
    ~BoardView();

    Player* curPlayer();

protected:
    void paintEvent(QPaintEvent* pe) override;
    void mousePressEvent(QMouseEvent* me) override;

private:
    void drawX(QPaintEvent *pe, QPainter &p, int pos);
    void drawY(QPaintEvent *pe, QPainter& p, int pos);

    Board* board_{Q_NULLPTR};
    Player* playerX_{Q_NULLPTR};
    Player* playerY_{Q_NULLPTR};

signals:
    void cellSelected(int cellNumber);
    void finished(Board::Side winner);

public slots:
    void start(bool playerXIsBot = false, bool playerYIsBot = false);

private slots:
    void onStep(Player *player, int step);
};

#endif // BOARDVIEW_H
