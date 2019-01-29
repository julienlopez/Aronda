#include <QApplication>
#include <iostream>

#include "boardwidget.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    auto* b = new Aronda::BoardWidget;
    b->show();

    return app.exec();
}