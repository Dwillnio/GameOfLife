#include <QApplication>

#include "window.h"
#include "game.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    game_classic g(500,750, false);
    g.enable_multithreading(true,4);

    //rule_lifelike rl({1,2,5},{3,6});
    rule_lifelike rl({},{2});
    game gll(500, 750, &rl);
    gll.enable_multithreading(true,4);

    window win(&g);
    win.show();
    app.exec();

    return 0;
}
