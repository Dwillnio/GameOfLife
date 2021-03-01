#include "window.h"

window::window(game* gm_, QWidget* parent) : QWidget(parent), t(this), gm(gm_)
{
    setFixedSize(gm->width()*CELL_WIDTH,gm->height()*CELL_WIDTH);
    t.start(TIMER_LENGTH);
    connect(&t, SIGNAL(timeout()), this, SLOT(timerupdate()));
    gm->generate();
    timer_len = TIMER_LENGTH;
}




void window::keyPressEvent(QKeyEvent* event)
{
    switch(event->key()){
    case Qt::Key_Space:
        if(t.isActive()) t.stop();
        else t.start(timer_len);
        break;
    case Qt::Key_Comma:
        timer_len *= TIMER_ADJUST;
        t.start(timer_len);
        break;
    case Qt::Key_Period:
        timer_len /= TIMER_ADJUST;
        t.start(timer_len);
        break;
    case Qt::Key_Slash:
        if(t.isActive()) t.stop();
        (*gm)++;
        update();
        break;
    }

}

void window::mousePressEvent(QMouseEvent* event)
{
    if(event->button() != Qt::LeftButton) return;
    int x,y;
    x = event->localPos().x()/CELL_WIDTH;
    y = event->localPos().y()/CELL_WIDTH;
    if(x<0 || x>=gm->width() || y<0 || y>=gm->height()) return;

    gm->cells[y][x] = !((*gm)(y,x));
    update();
}

void window::timerupdate()
{
    update();
    (*gm)++;
}

void window::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    for(int i=0; i<gm->height(); i++){
        for(int j=0; j<gm->width(); j++){
            if((*gm)(i,j)){
                painter.fillRect(j*CELL_WIDTH,i*CELL_WIDTH,CELL_WIDTH,CELL_WIDTH, QColor(1,1,1));
            }
        }
    }
}
