#include <QApplication>

#include "window.h"
#include "game.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    game_classic g(500,750, false);

    window win(&g);
    win.show();
    app.exec();

    return 0;
}
