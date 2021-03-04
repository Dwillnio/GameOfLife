#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <chrono>

#include "game.h"

#define CELL_WIDTH 2
#define TIMER_LENGTH 30
#define TIMER_ADJUST 1.3

#define DEBUG_WINDOW

class window : public QWidget
{
    Q_OBJECT
public:
    explicit window(game* gm_, QWidget* parent = 0);

public slots:
    void timerupdate();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    QTimer t;
    game* gm;

#ifdef DEBUG_WINDOW
    std::chrono::steady_clock::time_point time;
#endif

    int timer_len;
};

#endif // WINDOW_H
