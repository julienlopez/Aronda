#include <QApplication>
#include <iostream>

#include "board.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    auto* b = new Aronda::Board;
    b->show();

    return app.exec();
}